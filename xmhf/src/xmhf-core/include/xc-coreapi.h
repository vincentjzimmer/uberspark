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
 * 
 *  XMHF core API 
 * 
 *  author: amit vasudevan (amitvasudevan@acm.org)
 */

#ifndef __XC_COREAPI_H__
#define __XC_COREAPI_H__

//core APIs
#define	XC_API_HPT_SETPROT							(0xA01)
#define	XC_API_HPT_GETPROT							(0xA02)
#define XC_API_HPT_SETENTRY							(0xA03)
#define XC_API_HPT_GETENTRY							(0xA04)
#define XC_API_HPT_FLUSHCACHES						(0xA05)
#define XC_API_HPT_FLUSHCACHES_SMP					(0xA06)
#define XC_API_HPT_LVL2PAGEWALK						(0xA07)


#define	XC_API_TRAPMASK_SET							(0xB01)
#define XC_API_TRAPMASK_CLEAR						(0xB02)

#define XC_API_CPUSTATE_SET							(0xC01)
#define XC_API_CPUSTATE_GET							(0xC02)

#ifndef __ASSEMBLY__


//HPT related core APIs
void xc_api_hpt_setprot(context_desc_t context_desc, u64 gpa, u32 prottype);
void xc_api_hpt_arch_setprot(context_desc_t context_desc, u64 gpa, u32 prottype);

u32 xc_api_hpt_getprot(context_desc_t context_desc, u64 gpa);
u32 xc_api_hpt_arch_getprot(context_desc_t context_desc, u64 gpa);

void xc_api_hpt_setentry(context_desc_t context_desc, u64 gpa, u64 entry);
void xc_api_hpt_arch_setentry(context_desc_t context_desc, u64 gpa, u64 entry);

u64 xc_api_hpt_getentry(context_desc_t context_desc, u64 gpa);
u64 xc_api_hpt_arch_getentry(context_desc_t context_desc, u64 gpa);

void xc_api_hpt_flushcaches(context_desc_t context_desc);
void xc_api_hpt_flushcaches_smp(context_desc_t context_desc);
void xc_api_hpt_arch_flushcaches(context_desc_t context_desc, bool dosmpflush);

u64 xc_api_hpt_lvl2pagewalk(context_desc_t context_desc, u64 gva);
u64 xc_api_hpt_arch_lvl2pagewalk(context_desc_t context_desc, u64 gva);


//trapmask related core APIs
void xc_api_trapmask_set(context_desc_t context_desc, xc_hypapp_arch_param_t trapmaskparams);
void xc_api_trapmask_arch_set(context_desc_t context_desc, xc_hypapp_arch_param_t trapmaskparams);

void xc_api_trapmask_clear(context_desc_t context_desc, xc_hypapp_arch_param_t trapmaskparams);
void xc_api_trapmask_arch_clear(context_desc_t context_desc, xc_hypapp_arch_param_t trapmaskparams);


//cpu state related core APIs
void xc_api_cpustate_set(context_desc_t context_desc, xc_hypapp_arch_param_t cpustateparams);
void xc_api_cpustate_arch_set(context_desc_t context_desc, xc_hypapp_arch_param_t cpustateparams);

xc_hypapp_arch_param_t xc_api_cpustate_get(context_desc_t context_desc, u64 operation);
xc_hypapp_arch_param_t xc_api_cpustate_arch_get(context_desc_t context_desc, u64 operation);


#endif	//__ASSEMBLY__

#endif //__XC_COREAPI_H__