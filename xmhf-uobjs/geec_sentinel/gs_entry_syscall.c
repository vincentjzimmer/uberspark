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
 * HIC trampoline and stubs
 *
 * author: amit vasudevan (amitvasudevan@acm.org)
 */

#include <xmhf.h>
#include <xmhf-debug.h>
#include <xmhfgeec.h>
#include <geec_sentinel.h>

////// sysenter

//in general sp->xxx is untrusted and must be sanity checked
void gs_entry_syscall(slab_params_t *sp, void *caller_stack_frame){

    //sanity check sp
    sp->cpuid = xmhf_baseplatform_arch_x86_getcpulapicid();

    if( !(sp->slab_ctype == XMHFGEEC_SENTINEL_RET_VfT_PROG_TO_uVT_uVU_PROG ||
          sp->slab_ctype == XMHFGEEC_SENTINEL_CALL_uVT_uVU_PROG_TO_VfT_PROG
          ) ){
        _XDPRINTF_("%s[ln:%u]: inconsistent sp->xxx (%x). halting!\n", __func__,
                   __LINE__, sp->slab_ctype);
        HALT();
    }


    sp->src_slabid =
        (CASM_FUNCCALL(read_cr3, CASM_NOPARAM) - xmhfgeec_slab_info_table[XMHFGEEC_UHSLAB_BASE_IDX].mempgtbl_cr3)/PAGE_SIZE_4K + XMHFGEEC_UHSLAB_BASE_IDX;


    _XDPRINTF_("%s: sp=%x, cpuid=%u, src=%u, dst=%u, ctype=%x\n", __func__,
               (u32)sp, (u16)sp->cpuid, sp->src_slabid, sp->dst_slabid, sp->slab_ctype);

    geec_sentinel_main(sp, caller_stack_frame);
}




