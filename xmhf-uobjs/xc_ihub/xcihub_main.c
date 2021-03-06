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
#include <xmhfgeec.h>
#include <xmhf-debug.h>

#include <xc.h>
#include <xc_ihub.h>
#include <uapi_gcpustate.h>

/*
 * xc_ihub main module
 * author: amit vasudevan (amitvasudevan@acm.org)
 */




//@ ghost bool xcihub_callhcbinvoke=false;
//@ ghost bool xcihub_callicptvmcall=false;
//@ ghost bool xcihub_callhalt=false;

/*@
	assigns xcihub_callhcbinvoke;
	assigns xcihub_callicptvmcall;
	assigns xcihub_callhalt;

	ensures   ( vmexit_reason == VMX_VMEXIT_RDMSR) ==> (xcihub_callhcbinvoke == true
		&& xcihub_callicptvmcall == false && xcihub_callhalt == false);
	ensures ( vmexit_reason == VMX_VMEXIT_VMCALL) ==> (xcihub_callhcbinvoke == false
		&& xcihub_callicptvmcall == true && xcihub_callhalt == false);
	ensures ( vmexit_reason == VMX_VMEXIT_CPUID) ==> (xcihub_callhcbinvoke == true
		&& xcihub_callicptvmcall == false && xcihub_callhalt == false);
	ensures ( vmexit_reason == VMX_VMEXIT_WRMSR) ==> (xcihub_callhcbinvoke == true
		&& xcihub_callicptvmcall == false && xcihub_callhalt == false);
	ensures ( vmexit_reason == VMX_VMEXIT_CRX_ACCESS) ==> (xcihub_callhcbinvoke == false
			&& xcihub_callicptvmcall == false && xcihub_callhalt == false);
	ensures ( vmexit_reason == VMX_VMEXIT_XSETBV) ==> (xcihub_callhcbinvoke == false
			&& xcihub_callicptvmcall == false && xcihub_callhalt == false);
	ensures ( vmexit_reason == VMX_VMEXIT_SIPI) ==> (xcihub_callhcbinvoke == false
			&& xcihub_callicptvmcall == false && xcihub_callhalt == false);
	ensures ( vmexit_reason == VMX_VMEXIT_EPT_VIOLATION) ==> (xcihub_callhcbinvoke == true
			&& xcihub_callicptvmcall == false && xcihub_callhalt == false);
	ensures ( vmexit_reason == VMX_VMEXIT_EXCEPTION) ==> (xcihub_callhcbinvoke == true
			&& xcihub_callicptvmcall == false && xcihub_callhalt == false);

	ensures !(
		( vmexit_reason == VMX_VMEXIT_RDMSR) 			||
		( vmexit_reason == VMX_VMEXIT_VMCALL) 			||
		( vmexit_reason == VMX_VMEXIT_CPUID) 			||
		( vmexit_reason == VMX_VMEXIT_WRMSR) 			||
		( vmexit_reason == VMX_VMEXIT_CRX_ACCESS)   	||
		( vmexit_reason == VMX_VMEXIT_XSETBV)       	||
		( vmexit_reason == VMX_VMEXIT_SIPI)	        	||
		( vmexit_reason == VMX_VMEXIT_EPT_VIOLATION)	||
        ( vmexit_reason == VMX_VMEXIT_EXCEPTION)
	) ==> (xcihub_callhcbinvoke == false
				&& xcihub_callicptvmcall == false && xcihub_callhalt == true);


@*/
static void slab_main_helper(u32 vmexit_reason, u32 src_slabid, u32 cpuid){
	u32 hcb_status;

	if (vmexit_reason == VMX_VMEXIT_RDMSR){
		hcb_status = xc_hcbinvoke(XMHFGEEC_SLAB_XC_IHUB, cpuid, XC_HYPAPPCB_TRAP_INSTRUCTION,
			    XC_HYPAPPCB_TRAP_INSTRUCTION_RDMSR, src_slabid);
		//@ghost xcihub_callhcbinvoke=true;
		//@ghost xcihub_callicptvmcall=false;
		//@ghost xcihub_callhalt=false;
		if(hcb_status == XC_HYPAPPCB_CHAIN) xcihub_icptrdmsr((u16)cpuid);

	}else if(vmexit_reason == VMX_VMEXIT_VMCALL){
		xcihub_icptvmcall((u16)cpuid, src_slabid);
		//@ghost xcihub_callicptvmcall=true;
		//@ghost xcihub_callhcbinvoke=false;
		//@ghost xcihub_callhalt=false;

	}else if (vmexit_reason == VMX_VMEXIT_CPUID){
		hcb_status = xc_hcbinvoke(XMHFGEEC_SLAB_XC_IHUB, cpuid, XC_HYPAPPCB_TRAP_INSTRUCTION,
			    XC_HYPAPPCB_TRAP_INSTRUCTION_CPUID, src_slabid);
		//@ghost xcihub_callhcbinvoke=true;
		//@ghost xcihub_callicptvmcall=false;
		//@ghost xcihub_callhalt=false;
		if(hcb_status == XC_HYPAPPCB_CHAIN) xcihub_icptcpuid((u16)cpuid);


	}else if (vmexit_reason == VMX_VMEXIT_WRMSR){
		hcb_status =  xc_hcbinvoke(XMHFGEEC_SLAB_XC_IHUB, cpuid,
			    XC_HYPAPPCB_TRAP_INSTRUCTION, XC_HYPAPPCB_TRAP_INSTRUCTION_WRMSR, src_slabid);
		//@ghost xcihub_callhcbinvoke=true;
		//@ghost xcihub_callicptvmcall=false;
		//@ghost xcihub_callhalt=false;
		if(hcb_status == XC_HYPAPPCB_CHAIN)	xcihub_icptwrmsr((u16)cpuid);

	}else if (vmexit_reason == VMX_VMEXIT_CRX_ACCESS){
		xcihub_icptcrx((u16)cpuid, src_slabid);
		//@ghost xcihub_callhcbinvoke=false;
		//@ghost xcihub_callicptvmcall=false;
		//@ghost xcihub_callhalt=false;

	}else if (vmexit_reason == VMX_VMEXIT_XSETBV){
		xcihub_icptxsetbv((u16)cpuid);
		//@ghost xcihub_callhcbinvoke=false;
		//@ghost xcihub_callicptvmcall=false;
		//@ghost xcihub_callhalt=false;

	}else if (vmexit_reason == VMX_VMEXIT_SIPI){
		xcihub_icptsipi((u16)cpuid);
		//@ghost xcihub_callhcbinvoke=false;
		//@ghost xcihub_callicptvmcall=false;
		//@ghost xcihub_callhalt=false;

	}else if (vmexit_reason == VMX_VMEXIT_EPT_VIOLATION){
		hcb_status = xc_hcbinvoke(XMHFGEEC_SLAB_XC_IHUB, cpuid, XC_HYPAPPCB_MEMORYFAULT, 0, src_slabid);
		//@ghost xcihub_callhcbinvoke=true;
		//@ghost xcihub_callicptvmcall=false;
		//@ghost xcihub_callhalt=false;
		if(hcb_status == XC_HYPAPPCB_CHAIN)	xcihub_halt((u16)cpuid, vmexit_reason);

	}else if (vmexit_reason == VMX_VMEXIT_EXCEPTION){
		hcb_status = xc_hcbinvoke(XMHFGEEC_SLAB_XC_IHUB, cpuid, XC_HYPAPPCB_TRAP_EXCEPTION, 0, src_slabid);
		//@ghost xcihub_callhcbinvoke=true;
		//@ghost xcihub_callicptvmcall=false;
		//@ghost xcihub_callhalt=false;

	}else {
		xcihub_halt((u16)cpuid, vmexit_reason);
		//@ghost xcihub_callhcbinvoke=false;
		//@ghost xcihub_callicptvmcall=false;
		//@ghost xcihub_callhalt=true;
	}

}


#if defined (__XMHF_VERIFICATION__) && defined (__USPARK_FRAMAC_VA__)
u32 check_esp, check_eip = CASM_RET_EIP;
u32 cpuid = 0;	//cpu id

void main(void){
	//populate hardware model stack and program counter
	xmhfhwm_cpu_gprs_esp = _slab_tos[cpuid];
	xmhfhwm_cpu_gprs_eip = check_eip;
	check_esp = xmhfhwm_cpu_gprs_esp; // pointing to top-of-stack

	//setup main loop input parameters to non-det values
	slab_main_helper(framac_nondetu32(), framac_nondetu32(), cpuid);

	/*@assert ((xmhfhwm_cpu_state == CPU_STATE_RUNNING && xmhfhwm_cpu_gprs_esp == check_esp && xmhfhwm_cpu_gprs_eip == check_eip) ||
		(xmhfhwm_cpu_state == CPU_STATE_HALT));
	@*/
}
#endif



/*@
	requires \valid(sp);
	assigns sp->in_out_params[0];
	assigns sp->in_out_params[1];
	assigns sp->in_out_params[2];
	assigns sp->in_out_params[3];
	assigns sp->in_out_params[4];
	assigns sp->in_out_params[5];
	assigns sp->in_out_params[6];
	assigns sp->in_out_params[7];
	assigns xcihub_smplock;

	assigns xcihub_callhcbinvoke;
	assigns xcihub_callicptvmcall;
	assigns xcihub_callhalt;
@*/
void slab_main(slab_params_t *sp){
	u32 info_vmexit_reason;
	slab_params_t spl;
	xmhf_uapi_gcpustate_vmrw_params_t *gcpustate_vmrwp = (xmhf_uapi_gcpustate_vmrw_params_t *)&spl.in_out_params[0];

    //grab lock
    CASM_FUNCCALL(spin_lock,&xcihub_smplock);

	//_XDPRINTF_("XCIHUB[%u]: Got control: src=%u, dst=%u, esp=%08x, eflags=%08x\n",
	//	(u16)sp->cpuid, sp->src_slabid, sp->dst_slabid, CASM_FUNCCALL(read_esp,CASM_NOPARAM),
	//		CASM_FUNCCALL(read_eflags, CASM_NOPARAM));
	spl.cpuid = sp->cpuid;
	spl.src_slabid = XMHFGEEC_SLAB_XC_IHUB;

	//store GPRs
	spl.dst_slabid = XMHFGEEC_SLAB_UAPI_GCPUSTATE;
	spl.dst_uapifn = XMHF_HIC_UAPI_CPUSTATE_GUESTGPRSWRITE;
	spl.in_out_params[0] = sp->in_out_params[0];
	spl.in_out_params[1] = sp->in_out_params[1];
	spl.in_out_params[2] = sp->in_out_params[2];
	spl.in_out_params[3] = sp->in_out_params[3];
	spl.in_out_params[4] = sp->in_out_params[4];
	spl.in_out_params[5] = sp->in_out_params[5];
	spl.in_out_params[6] = sp->in_out_params[6];
	spl.in_out_params[7] = sp->in_out_params[7];
	XMHF_SLAB_CALLNEW(&spl);

	//grab exit reason
	spl.dst_slabid = XMHFGEEC_SLAB_UAPI_GCPUSTATE;
	spl.dst_uapifn = XMHF_HIC_UAPI_CPUSTATE_VMREAD;
	spl.in_out_params[0] = VMCS_INFO_VMEXIT_REASON;
	spl.in_out_params[1] = 0;
	XMHF_SLAB_CALLNEW(&spl);
	info_vmexit_reason = gcpustate_vmrwp->value;

	slab_main_helper(info_vmexit_reason, sp->src_slabid, (u16)sp->cpuid);

	//load GPRs
	spl.dst_slabid = XMHFGEEC_SLAB_UAPI_GCPUSTATE;
	spl.dst_uapifn = XMHF_HIC_UAPI_CPUSTATE_GUESTGPRSREAD;
	XMHF_SLAB_CALLNEW(&spl);
	sp->in_out_params[0] = spl.in_out_params[0];
	sp->in_out_params[1] = spl.in_out_params[1];
	sp->in_out_params[2] = spl.in_out_params[2];
	sp->in_out_params[3] = spl.in_out_params[3];
	sp->in_out_params[4] = spl.in_out_params[4];
	sp->in_out_params[5] = spl.in_out_params[5];
	sp->in_out_params[6] = spl.in_out_params[6];
	sp->in_out_params[7] = spl.in_out_params[7];

	//_XDPRINTF_("XCIHUB[%u]: Resuming guest, esp=%08x\n", (u16)sp->cpuid, CASM_FUNCCALL(read_esp,CASM_NOPARAM));

    //release lock
    CASM_FUNCCALL(spin_unlock,&xcihub_smplock);

	//resume guest slab
	return;
}





