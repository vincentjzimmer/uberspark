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

/*
 * GEEC sentinel SISS stack pop operation
 *
 * author: amit vasudevan (amitvasudevan@acm.org)
 */

#include <xmhf.h>
#include <xmhf-debug.h>
#include <xmhfgeec.h>
#include <geec_sentinel.h>



//void gs_siss_pop(u32 cpuid, u32 *src_slabid, u32 *dst_slabid, u32 *hic_calltype,
//                       void **caller_stack_framep, slab_params_t **spp)
/*@
	requires sissValid (siss_id);
	requires \valid(elem);

	behavior not_empty:
		assumes !sissEmpty(siss_id);
		assigns gs_siss_indices[siss_id];
		assigns elem->src_slabid;
		assigns elem->dst_slabid;
		assigns elem->slab_ctype;
		assigns elem->caller_stack_frame;
		assigns elem->sp;

		ensures X:sissValid (siss_id);
		ensures Y:sissSize ( siss_id) == sissSize { Old }(siss_id) - 1;
		ensures A:!sissFull (siss_id);
		ensures sissStorage (siss_id ) == sissStorage {Old }( siss_id) ;
		ensures sissCapacity ( siss_id) == sissCapacity { Old }(siss_id) ;

	behavior empty:
		assumes sissEmpty (siss_id);

		assigns \nothing;

		ensures sissValid (siss_id);
		ensures sissEmpty (siss_id);
		ensures sissSize ( siss_id) == sissSize { Old }(siss_id) ;
		ensures sissStorage (siss_id ) == sissStorage {Old }( siss_id) ;
		ensures sissCapacity ( siss_id) == sissCapacity { Old }(siss_id) ;

	complete behaviors ;
	disjoint behaviors ;

*/
void gs_siss_pop(u32 siss_id, gs_siss_element_t *elem)
{
    u32 safestack_index = gs_siss_indices[siss_id];

    if(safestack_index >0 && safestack_index <= 512){
        safestack_index--;
        elem->src_slabid = gs_siss[siss_id][safestack_index].src_slabid;
        elem->dst_slabid = gs_siss[siss_id][safestack_index].dst_slabid;
        elem->slab_ctype = gs_siss[siss_id][safestack_index].slab_ctype;
        elem->caller_stack_frame = gs_siss[siss_id][safestack_index].caller_stack_frame;
        elem->sp = gs_siss[siss_id][safestack_index].sp;

        gs_siss_indices[siss_id] = safestack_index;
    }
}

