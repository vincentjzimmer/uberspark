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


//setup unverified hypervisor (uh) slab memory page tables
/*@
	requires XMHFGEEC_UHSLAB_BASE_IDX <= slabid <= XMHFGEEC_UHSLAB_MAX_IDX;
	requires 0 <= xmhfgeec_slab_info_table[slabid].iotbl_base < (0xFFFFFFFFUL - (3*PAGE_SIZE_4K));

	assigns gp_rwdatahdr.gp_uhslabmempgtbl_lvl4t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][0..(PAE_MAXPTRS_PER_PDPT-1)];
	assigns gp_uhslabmempgtbl_lvl2t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][0..((PAE_PTRS_PER_PDPT * PAE_PTRS_PER_PDT)-1)];

	ensures \forall integer x; PAE_PTRS_PER_PDPT <= x < PAE_MAXPTRS_PER_PDPT ==> (
			gp_rwdatahdr.gp_uhslabmempgtbl_lvl4t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][x] == 0
			);

	ensures \forall integer x; 0 <= x < PAE_PTRS_PER_PDPT ==> (
			gp_rwdatahdr.gp_uhslabmempgtbl_lvl4t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][x] ==
			(pae_make_pdpe(&gp_uhslabmempgtbl_lvl2t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][x * PAE_PTRS_PER_PDT], (u64)(_PAGE_PRESENT)))
			);


	ensures \forall integer x; 0 <= x < PAE_PTRS_PER_PDT ==> (
			gp_uhslabmempgtbl_lvl2t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][x] ==
			(pae_make_pde(&gp_uhslabmempgtbl_lvl1t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][(x * PAE_PTRS_PER_PT)], (u64)(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER)))
			);
@*/
void gp_s2_setupmpgtbluh(u32 slabid){
	u64 flags;
	u32 spatype;
	u32 i, j;

	//zero out pdpt
	/*@
		loop invariant a1: 0 <= i <= PAE_MAXPTRS_PER_PDPT;
		loop invariant a11: \forall integer x; 0 <= x < i ==> (
			gp_rwdatahdr.gp_uhslabmempgtbl_lvl4t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][x] == 0
			);
		loop assigns gp_rwdatahdr.gp_uhslabmempgtbl_lvl4t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][0..(PAE_MAXPTRS_PER_PDPT-1)];
		loop assigns i;
		loop variant PAE_MAXPTRS_PER_PDPT - i;
	@*/
	for(i=0; i < PAE_MAXPTRS_PER_PDPT; i++){
		gp_rwdatahdr.gp_uhslabmempgtbl_lvl4t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][i] = 0;
	}


	/*@
		loop invariant a2: 0 <= i <= PAE_PTRS_PER_PDPT;
		loop invariant a3: \forall integer x; 0 <= x < i ==> (
			gp_rwdatahdr.gp_uhslabmempgtbl_lvl4t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][x] ==
			(pae_make_pdpe(&gp_uhslabmempgtbl_lvl2t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][x * PAE_PTRS_PER_PDT], (u64)(_PAGE_PRESENT)))
			);
		loop assigns gp_rwdatahdr.gp_uhslabmempgtbl_lvl4t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][0..(PAE_PTRS_PER_PDPT-1)];
		loop assigns i;
		loop variant PAE_PTRS_PER_PDPT - i;
	@*/
	//assign 4GB pdpt entries
	for(i=0; i < PAE_PTRS_PER_PDPT; i++){
		gp_rwdatahdr.gp_uhslabmempgtbl_lvl4t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][i] =
		    pae_make_pdpe(&gp_uhslabmempgtbl_lvl2t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][i * PAE_PTRS_PER_PDT], (u64)(_PAGE_PRESENT));
	}



	/*@
		loop invariant a4: 0 <= i <= (PAE_PTRS_PER_PDPT * PAE_PTRS_PER_PDT);
		loop invariant a5: \forall integer x; 0 <= x < i ==> (
			gp_uhslabmempgtbl_lvl2t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][x] ==
			(pae_make_pde(&gp_uhslabmempgtbl_lvl1t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][(x * PAE_PTRS_PER_PT)], (u64)(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER)))
			);
		loop assigns i;
		loop assigns gp_uhslabmempgtbl_lvl2t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][0..(PAE_PTRS_PER_PDPT * PAE_PTRS_PER_PDT)-1];
		loop variant (PAE_PTRS_PER_PDPT * PAE_PTRS_PER_PDT) - i;
	@*/
	//pdt setup
	for(i=0; i < PAE_PTRS_PER_PDPT * PAE_PTRS_PER_PDT; i++){
		gp_uhslabmempgtbl_lvl2t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][i] =
			pae_make_pde(&gp_uhslabmempgtbl_lvl1t[(slabid - XMHFGEEC_UHSLAB_BASE_IDX)][(i * PAE_PTRS_PER_PT)], (u64)(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER));
	}



	//pts
	/*@
		loop invariant a6: 0 <= i <= ((PAE_PTRS_PER_PDPT * PAE_PTRS_PER_PDT * PAE_PTRS_PER_PT)+0x2);
		loop assigns i;
		loop assigns spatype;
		loop assigns flags;
		loop variant ((PAE_PTRS_PER_PDPT * PAE_PTRS_PER_PDT * PAE_PTRS_PER_PT)+0x2) - i;
	@*/
	for(i=0; i < (PAE_PTRS_PER_PDPT * PAE_PTRS_PER_PDT * PAE_PTRS_PER_PT); i++){
		spatype =  gp_s2_setupmpgtbl_getspatype(slabid, (u32)(i*PAGE_SIZE_4K));
		flags = gp_s2_setupmpgtbluh_getflags(slabid, (u32)(i*PAGE_SIZE_4K), spatype);

		if(!gp_s2_setupmpgtbluh_setentry(slabid, (slabid - XMHFGEEC_UHSLAB_BASE_IDX), spatype, i, flags))
			i+=2;
	}
}
