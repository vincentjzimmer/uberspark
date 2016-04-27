/*
 * @XMHF_LICENSE_HEADER_START@
 *
 * eXtensible, Modular Hypervisor Framework (XMHF)
 * Copyright (c) 2009-2012 Carnegie Mellon University
 * Copyright (c) 2010-2012 VDG Inc.
 * All Rights Reserved.
 *
 * Developed by: XMHF Team
 *               Carnegie Mellon University / CyLab
 *               VDG Inc.
 *               http://xmhf.org
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in
 * the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the names of Carnegie Mellon or VDG Inc, nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * @XMHF_LICENSE_HEADER_END@
 */

#include <xmhf.h>
#include <xmhf-debug.h>

#include <xmhfgeec.h>

#include <geec_prime.h>

/*@
	requires 0 <= slabid < XMHFGEEC_TOTAL_SLABS;
@*/
void gp_s2_sdasetupdevpgtbl_rg(u32 slabid){
	u32 i,j;

	//initialize lvl1 page table (pml4t)
	/*@
		loop invariant a1: 0 <= i <= VTD_MAXPTRS_PER_PML4T;
		loop invariant a2: \forall integer x; 0 <= x < i ==> (
			(_slabdevpgtbl_pml4t[slabid][x] == 0)
			);
		loop assigns i;
		loop assigns _slabdevpgtbl_pml4t[slabid][0..(VTD_MAXPTRS_PER_PML4T-1)];
		loop variant VTD_MAXPTRS_PER_PML4T - i;
	@*/
	for(i=0; i < VTD_MAXPTRS_PER_PML4T; i++)
		_slabdevpgtbl_pml4t[slabid][i] = 0;


	_slabdevpgtbl_pml4t[slabid][0] =
		vtd_make_pml4te((u64)&_slabdevpgtbl_pdpt[slabid], (VTD_PAGE_READ | VTD_PAGE_WRITE));

	//initialize lvl2 page table (pdpt)
	/*@
		loop invariant a3: 0 <= i <= VTD_MAXPTRS_PER_PDPT;
		loop invariant a4: \forall integer x; 0 <= x < i ==> (
			(_slabdevpgtbl_pdpt[slabid][x] == 0)
			);
		loop assigns i;
		loop assigns _slabdevpgtbl_pdpt[slabid][0..(VTD_MAXPTRS_PER_PDPT-1)];
		loop variant VTD_MAXPTRS_PER_PDPT - i;
	@*/
	for(i=0; i < VTD_MAXPTRS_PER_PDPT; i++)
		_slabdevpgtbl_pdpt[slabid][i] = 0;


	/*@
		loop invariant a5: 0 <= i <= VTD_PTRS_PER_PDPT;
		loop invariant a6: \forall integer x; 0 <= x < i ==> (
			_slabdevpgtbl_pdpt[slabid][x] ==
			 (vtd_make_pdpte((u64)&_slabdevpgtbl_pdt[slabid][x*VTD_PTRS_PER_PDT], (VTD_PAGE_READ | VTD_PAGE_WRITE)))
			);
		loop assigns i;
		loop assigns _slabdevpgtbl_pdpt[slabid][0..(VTD_PTRS_PER_PDPT-1)];
		loop variant VTD_PTRS_PER_PDPT - i;
	@*/
	for(i=0; i < VTD_PTRS_PER_PDPT; i++){
		_slabdevpgtbl_pdpt[slabid][i] =
			vtd_make_pdpte((u64)&_slabdevpgtbl_pdt[slabid][i*VTD_PTRS_PER_PDT], (VTD_PAGE_READ | VTD_PAGE_WRITE));
	}


	//setup PDTs
	for(i=0; i < (VTD_PTRS_PER_PDPT * VTD_PTRS_PER_PDT); i++){
			_slabdevpgtbl_pdt[slabid][i] =
				vtd_make_pdte((u64)&_slabdevpgtbl_pt_rg[i], (VTD_PAGE_READ | VTD_PAGE_WRITE));
	}

}
