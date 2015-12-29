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


//setup PT entries for a 2M range

/*@
	requires 0 <= slabid < XMHFGEEC_TOTAL_SLABS;
	requires 0 <= pd_index < MAX_SLAB_DMADATA_PDT_ENTRIES;
	assigns _slabdevpgtbl_pdt[slabid][(startpaddr/PAGE_SIZE_2M)];
@*/
void gp_s2_sdasetupdevpgtbl_setptentries(u32 slabid, u32 pd_index, u32 startpaddr){
	u32 i;

	//stick a pt for the pdt entry
	_slabdevpgtbl_pdt[slabid][(startpaddr/PAGE_SIZE_2M)] =
	    vtd_make_pdte((u64)_slabdevpgtbl_pt[slabid][pd_index], (VTD_PAGE_READ | VTD_PAGE_WRITE));

	#if 0
	for(i=0; i < VTD_PTRS_PER_PT; i++){
	    _slabdevpgtbl_pt[slabid][(pd_index * VTD_PTRS_PER_PT)+i] =
		vtd_make_pte((startpaddr+(i * PAGE_SIZE_4K)), (VTD_PAGE_READ | VTD_PAGE_WRITE));
	}
	#endif
}

