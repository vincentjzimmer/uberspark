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

#ifndef __XCAPIPLATFORM_H__
#define __XCAPIPLATFORM_H__


#ifndef __ASSEMBLY__

#define	XMHF_SLAB_XCAPIPLATFORM_FNINITIALIZEANDENUMERATEDEVICES						1
#define	XMHF_SLAB_XCAPIPLATFORM_FNINITIALIZEANDENUMERATEDEVICES_SIZE 			(sizeof(context_desc_t))

#define XMHF_SLAB_XCAPIPLATFORM_FNQUIESCECPUSINPARTITION                            2
#define XMHF_SLAB_XCAPIPLATFORM_FNQUIESCECPUSINPARTITION_SIZE                   (sizeof(context_desc_t))

///////////////////////////////////////////////////////////////////////////////
//platform related core APIs
void xc_api_platform_shutdown(context_desc_t context_desc);
void xc_api_platform_arch_shutdown(context_desc_t context_desc);

xc_platformdevice_desc_t xc_api_platform_initializeandenumeratedevices(context_desc_t context_desc);
xc_platformdevice_desc_t xc_api_platform_arch_initializeandenumeratedevices(context_desc_t context_desc);

bool xc_api_platform_allocdevices_to_partition(context_desc_t context_desc, xc_platformdevice_desc_t device_descs);
bool xc_api_platform_arch_allocdevices_to_partition(context_desc_t context_desc, xc_platformdevice_desc_t device_descs);

bool xc_api_platform_deallocdevices_from_partition(context_desc_t context_desc, xc_platformdevice_desc_t device_descs);
bool xc_api_platform_arch_deallocdevices_from_partition(context_desc_t context_desc, xc_platformdevice_desc_t device_descs);

void xc_api_platform_quiescecpus_in_partition(context_desc_t context_desc);
void xc_api_platform_arch_quiescecpus_in_partition(context_desc_t context_desc);

void xc_coreapi_arch_eventhandler_nmiexception(struct regs *r);


#endif	//__ASSEMBLY__


#endif //__XCAPIPLATFORM_H__