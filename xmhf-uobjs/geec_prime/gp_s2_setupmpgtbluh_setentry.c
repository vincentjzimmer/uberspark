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

//returns true if entry was mapped unchanged
//returns false if entry belonged to iotbl and was mapped with uobj specific iotbl
//@ghost bool gp_s2_setupmpgtbluh_setentry_halted = false;
/*@
	requires 0 <= slabid < XMHFGEEC_TOTAL_SLABS;
	requires 0 <= uhslabmempgtbl_idx < XMHFGEEC_TOTAL_UHSLABS;
	requires 0 <= ptindex < (1024*1024);
	requires 0 <= xmhfgeec_slab_info_table[slabid].iotbl_base < (0xFFFFFFFFUL - (3*PAGE_SIZE_4K));

	behavior mapiotbl:
		assumes (
			 ((spatype & 0x0000000FUL) == _SLAB_SPATYPE_GEEC_PRIME_IOTBL &&
	                  xmhfgeec_slab_info_table[slabid].slabtype != XMHFGEEC_SLABTYPE_VfT_PROG &&
 	                  xmhfgeec_slab_info_table[slabid].slabtype != XMHFGEEC_SLABTYPE_VfT_SENTINEL
 	                 ) &&
		        (ptindex < ((1024*1024)-3))
			);
		ensures (gp_uhslabmempgtbl_lvl1t[uhslabmempgtbl_idx][ptindex] ==
			(pae_make_pte(xmhfgeec_slab_info_table[slabid].iotbl_base, flags)));
		ensures (gp_uhslabmempgtbl_lvl1t[uhslabmempgtbl_idx][ptindex+1] ==
			(pae_make_pte(xmhfgeec_slab_info_table[slabid].iotbl_base+PAGE_SIZE_4K, flags)));
		ensures (gp_uhslabmempgtbl_lvl1t[uhslabmempgtbl_idx][ptindex+2] ==
			(pae_make_pte(xmhfgeec_slab_info_table[slabid].iotbl_base+(2*PAGE_SIZE_4K), flags)));
		ensures (gp_s2_setupmpgtbluh_setentry_halted == false);
		ensures (\result == false);

	behavior mapentry:
		assumes (
			 !((spatype & 0x0000000FUL) == _SLAB_SPATYPE_GEEC_PRIME_IOTBL &&
	                  xmhfgeec_slab_info_table[slabid].slabtype != XMHFGEEC_SLABTYPE_VfT_PROG &&
 	                  xmhfgeec_slab_info_table[slabid].slabtype != XMHFGEEC_SLABTYPE_VfT_SENTINEL
 	                 )
			);
		ensures ( gp_uhslabmempgtbl_lvl1t[uhslabmempgtbl_idx][ptindex] ==
			(pae_make_pte((ptindex*PAGE_SIZE_4K), flags)) );
		ensures (gp_s2_setupmpgtbluh_setentry_halted == false);
		ensures (\result == true);

	behavior invalid:
		assumes (
			 ((spatype & 0x0000000FUL) == _SLAB_SPATYPE_GEEC_PRIME_IOTBL &&
	                  xmhfgeec_slab_info_table[slabid].slabtype != XMHFGEEC_SLABTYPE_VfT_PROG &&
 	                  xmhfgeec_slab_info_table[slabid].slabtype != XMHFGEEC_SLABTYPE_VfT_SENTINEL
 	                 ) &&
		        !(ptindex < ((1024*1024)-3))
			);
		ensures (gp_s2_setupmpgtbluh_setentry_halted == true);
		ensures (\result == false);

	complete behaviors;
	disjoint behaviors;

@*/
bool gp_s2_setupmpgtbluh_setentry(u32 slabid, u32 uhslabmempgtbl_idx, u32 spatype, u32 ptindex, u64 flags){

	if((spatype & 0x0000000FUL) == _SLAB_SPATYPE_GEEC_PRIME_IOTBL &&
	   xmhfgeec_slab_info_table[slabid].slabtype != XMHFGEEC_SLABTYPE_VfT_PROG &&
	   xmhfgeec_slab_info_table[slabid].slabtype != XMHFGEEC_SLABTYPE_VfT_SENTINEL){
		if(ptindex < ((1024*1024)-3)){
			//map unverified slab iotbl instead (12K)
			gp_uhslabmempgtbl_lvl1t[uhslabmempgtbl_idx][ptindex] =
				pae_make_pte(xmhfgeec_slab_info_table[slabid].iotbl_base, flags);

			gp_uhslabmempgtbl_lvl1t[uhslabmempgtbl_idx][ptindex+1] =
				pae_make_pte(xmhfgeec_slab_info_table[slabid].iotbl_base+PAGE_SIZE_4K, flags);

			gp_uhslabmempgtbl_lvl1t[uhslabmempgtbl_idx][ptindex+2] =
				pae_make_pte(xmhfgeec_slab_info_table[slabid].iotbl_base+(2*PAGE_SIZE_4K), flags);

			//@ghost gp_s2_setupmpgtbluh_setentry_halted = false;
			return false;
		}else{
			_XDPRINTF_("%s:%u Invalid IOTBL mapping index. Halting!\n", __func__, __LINE__);
			CASM_FUNCCALL(xmhfhw_cpu_hlt, CASM_NOPARAM);
			//@ghost gp_s2_setupmpgtbluh_setentry_halted = true;
			return false;
		}
	}else{
		gp_uhslabmempgtbl_lvl1t[uhslabmempgtbl_idx][ptindex] =
			pae_make_pte((ptindex*PAGE_SIZE_4K), flags);

		//@ghost gp_s2_setupmpgtbluh_setentry_halted = false;
		return true;
	}
}

