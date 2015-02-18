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

// XMHF slab entry, uapi, and trampoline call stubs decls./defns.
// author: amit vasudevan (amitvasudevan@acm.org)
// XXX: need to split arch. dependent portions

#ifndef __XMHFSLAB_H__
#define __XMHFSLAB_H__




#ifndef __ASSEMBLY__



//////
// HIC UAPI and SLAB invocation macros



//HIC UAPI


/*
__xmhfhic_uapi_cpustate register mappings:

RDI = XMHF_HIC_UAPI
RSI = XMHF_HIC_UAPI_CPUSTATE
RDX = cpustatefn
RCX = undefined
R8 = iparams
R9 = oparams
R10 = return RSP
R11 = return_address

*/

//reserved_uapicall = XMHF_HIC_UAPI, reserved_uapicall_num = XMHF_HIC_UAPI_CPUSTATE
__attribute__((naked)) __attribute__ ((noinline)) static inline bool __xmhfhic_uapi_cpustate(u64 reserved_uapicall, u64 reserved_uapicall_num,
                                           u64 cpustatefn,
                                           u64 reserved, u64 iparams, u64 oparams){

    asm volatile (
        "movq %%rsp, %%r10 \r\n"
        "movq $1f, %%r11 \r\n"\
        "sysenter \r\n" \
        \
        "1:\r\n" \
        "retq \r\n" \
        :
        :
        :
    );


}


#if defined (__XMHF_VERIFICATION__)

#define XMHF_HIC_SLAB_UAPI_CPUSTATE(cpustatefn, iparams, oparams) \
    __xmhfhic_rtm_uapihandler(XMHF_HIC_UAPI, XMHF_HIC_UAPI_CPUSTATE, cpustatefn,0, iparams, oparams, 0, 0);\



#else

#define XMHF_HIC_SLAB_UAPI_CPUSTATE(cpustatefn, iparams, oparams) \
    __xmhfhic_uapi_cpustate(XMHF_HIC_UAPI, XMHF_HIC_UAPI_CPUSTATE, cpustatefn, 0, iparams, oparams)

#endif //__XMHF_VERIFICATION__







/*
__xmhfhic_uapi_physmem register mappings:

RDI = XMHF_HIC_UAPI
RSI = XMHF_HIC_UAPI_PHYSMEM
RDX = physmemfn
RCX = undefined
R8 = iparams
R9 = oparams
R10 = return RSP
R11 = return_address

*/

//reserved_uapicall = XMHF_HIC_UAPI, reserved_uapicall_num = XMHF_HIC_UAPI_PHYSMEM
__attribute__((naked)) __attribute__ ((noinline)) static inline bool __xmhfhic_uapi_physmem(u64 reserved_uapicall, u64 reserved_uapicall_num,
                                           u64 physmemfn,
                                           u64 reserved, u64 iparams, u64 oparams){

    asm volatile (
        "movq %%rsp, %%r10 \r\n"
        "movq $1f, %%r11 \r\n"\
        "sysenter \r\n" \
        \
        "1:\r\n" \
        "retq \r\n" \
        :
        :
        :
    );


}

#if defined (__XMHF_VERIFICATION__)

#define XMHF_HIC_SLAB_UAPI_PHYSMEM(physmemfn, iparams, oparams) \
    __xmhfhic_rtm_uapihandler(XMHF_HIC_UAPI, XMHF_HIC_UAPI_PHYSMEM, physmemfn,0, iparams, oparams, 0, 0);\



#else

#define XMHF_HIC_SLAB_UAPI_PHYSMEM(physmemfn, iparams, oparams) \
    __xmhfhic_uapi_physmem(XMHF_HIC_UAPI, XMHF_HIC_UAPI_PHYSMEM, physmemfn, 0, iparams, oparams)


#endif






/*
__xmhfhic_uapi_mempgtbl register mappings:

RDI = XMHF_HIC_UAPI
RSI = XMHF_HIC_UAPI_MEMPGTBL
RDX = mempgtblfn
RCX = undefined
R8 = iparams
R9 = oparams
R10 = return RSP
R11 = return_address

*/

//reserved_uapicall = XMHF_HIC_UAPI, reserved_uapicall_num = XMHF_HIC_UAPI_MEMPGTBL
__attribute__((naked)) __attribute__ ((noinline)) static inline bool __xmhfhic_uapi_mempgtbl(u64 reserved_uapicall, u64 reserved_uapicall_num,
                                           u64 mempgtblfn,
                                           u64 reserved, u64 iparams, u64 oparams){

    asm volatile (
        "movq %%rsp, %%r10 \r\n"
        "movq $1f, %%r11 \r\n"\
        "sysenter \r\n" \
        \
        "1:\r\n" \
        "retq \r\n" \
        :
        :
        :
    );


}


#if defined (__XMHF_VERIFICATION__)

#define XMHF_HIC_SLAB_UAPI_MEMPGTBL(mempgtblfn, iparams, oparams) \
    __xmhfhic_rtm_uapihandler(XMHF_HIC_UAPI, XMHF_HIC_UAPI_MEMPGTBL, mempgtblfn,0, iparams, oparams, 0, 0);\


#else

//#define XMHF_HIC_SLAB_UAPI_MEMPGTBL(mempgtblfn, iparams, oparams)

#define XMHF_HIC_SLAB_UAPI_MEMPGTBL(mempgtblfn, iparams, oparams) \
    __xmhfhic_uapi_mempgtbl(XMHF_HIC_UAPI, XMHF_HIC_UAPI_MEMPGTBL, mempgtblfn, 0, iparams, oparams)


#endif //__XMHF_VERIFICATION__




/*
__slab_callstub register mappings:

RDI = call type (XMHF_HIC_SLABCALL)
RSI = iparams
RDX = iparams_size
RCX = oparams
R8 = oparams_size
R9 = dst_slabid
R10 = return RSP;
R11 = return_address

*/


__attribute__((naked)) __attribute__ ((noinline)) static inline bool __slab_callstub(u64 reserved, slab_input_params_t *iparams, u64 iparams_size, slab_output_params_t *oparams, u64 oparams_size, u64 dst_slabid){
    asm volatile (
        "pushq %%rbx \r\n"
        "pushq %%r12 \r\n"
        "pushq %%r13 \r\n"
        "pushq %%r14 \r\n"
        "pushq %%r15 \r\n"

        "movq %0, %%rdi \r\n"
        "movq %%rsp, %%r10 \r\n"
        "movq $1f, %%r11 \r\n"\
        "sysenter \r\n" \
        \
        "1:\r\n" \
        "popq %%r15 \r\n"
        "popq %%r14 \r\n"
        "popq %%r13 \r\n"
        "popq %%r12 \r\n"
        "popq %%rbx \r\n"
        "retq \r\n" \
        :
        : "i" (XMHF_HIC_SLABCALL)
        :
    );
}


#if defined (__XMHF_VERIFICATION__)

#define XMHF_SLAB_CALL(dst_slabname, dst_slabid, iparams, iparams_size, oparams, oparams_size)
#define XMHF_SLAB(slab_name)
#define XMHF_SLAB_GUEST(slab_name)
#define XMHF_SLAB_INTERCEPT(slab_name)
#define XMHF_SLAB_EXCEPTION(slab_name)


#else




#define XMHF_SLAB_CALL(dst_slabname, dst_slabid, iparams, iparams_size, oparams, oparams_size) __slab_callstub(0, iparams, iparams_size, oparams, oparams_size, dst_slabid)


/*
_slab_entrystub entry register mappings:

RDI = iparams
RSI = iparams_size
RDX = slab entrystub; used for SYSEXIT
RCX = slab entrystub stack TOS for the CPU; used for SYSEXIT
R8 = oparams
R9 = oparams_size
R10 = src_slabid
R11 = cpuid

*/


#define XMHF_SLAB(slab_name)	\
	__attribute__ ((section(".rodata"))) char * slab_name##_string="_xmhfslab_"#slab_name"_";	\
	__attribute__ ((section(".stack"))) __attribute__ ((aligned(4096))) u8 slab_name##_slab_stack[MAX_PLATFORM_CPUS][XMHF_SLAB_STACKSIZE];	\
	__attribute__ ((section(".stackhdr"))) u64 slab_name##_slab_tos[MAX_PLATFORM_CPUS]= { ((u64)&slab_name##_slab_stack[0] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[1] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[2] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[3] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[4] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[5] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[6] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[7] + XMHF_SLAB_STACKSIZE)  };	\
    __attribute__ ((section(".slab_dmadata"))) u8 slab_name##dmadataplaceholder[1];\
    \
    \
	__attribute__((naked)) __attribute__ ((section(".slab_entrystub"))) __attribute__((align(1))) void _slab_entrystub_##slab_name(void){	\
	asm volatile ( \
            "pushq %%r10 \r\n" \
            "movq %%r8, %%rdx \r\n" \
            "movq %%r9, %%rcx \r\n" \
            "movq %%r10, %%r8 \r\n" \
            "movq %%r11, %%r9 \r\n" \
            "callq "#slab_name"_interface \r\n"		\
            "popq %%r9 \r\n" \
            "movq %0, %%rdi \r\n" \
            "sysenter \r\n" \
            \
            "int $0x03 \r\n" \
            "1: jmp 1b \r\n" \
            \
			:  \
			:  "i" (XMHF_HIC_SLABRET) \
			:  \
		);	\
    }\



#define XMHF_SLAB_GUEST(slab_name)	\
	__attribute__ ((section(".rodata"))) char * slab_name##_string="_xmhfslab_"#slab_name"_";	\
	__attribute__ ((section(".stack"))) __attribute__ ((aligned(4096))) u8 slab_name##_slab_stack[MAX_PLATFORM_CPUS][XMHF_SLAB_STACKSIZE];	\
	__attribute__ ((section(".stackhdr"))) u64 slab_name##_slab_tos[MAX_PLATFORM_CPUS]= { ((u64)&slab_name##_slab_stack[0] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[1] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[2] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[3] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[4] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[5] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[6] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[7] + XMHF_SLAB_STACKSIZE)  };	\
    __attribute__ ((section(".slab_dmadata"))) u8 slab_name##dmadataplaceholder[1];\
    __attribute__ ((section(".rwdatahdr"))) guest_slab_header_t slab_name##_guestslabheader = {GUEST_SLAB_HEADER_MAGIC, 0};\
    \
    \
	__attribute__((naked)) __attribute__ ((section(".slab_entrystub"))) __attribute__((align(1))) void _slab_entrystub_##slab_name(void){	\
	asm volatile ( \
          "jmp "#slab_name"_interface \r\n"		\
			:  \
			:  \
			:  \
		);	\
    }\



#define XMHF_SLAB_INTERCEPT(slab_name)	\
	__attribute__ ((section(".rodata"))) char * slab_name##_string="_xmhfslab_"#slab_name"_";	\
	__attribute__ ((section(".stack"))) __attribute__ ((aligned(4096))) u8 slab_name##_slab_stack[MAX_PLATFORM_CPUS][XMHF_SLAB_STACKSIZE];	\
	__attribute__ ((section(".stackhdr"))) u64 slab_name##_slab_tos[MAX_PLATFORM_CPUS]= { ((u64)&slab_name##_slab_stack[0] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[1] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[2] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[3] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[4] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[5] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[6] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[7] + XMHF_SLAB_STACKSIZE)  };	\
    __attribute__ ((section(".slab_dmadata"))) u8 slab_name##dmadataplaceholder[1];\
    \
    \
	__attribute__((naked)) __attribute__ ((section(".slab_entrystub"))) __attribute__((align(1))) void _slab_entrystub_##slab_name(void){	\
	asm volatile ( \
            "pushq %%r10 \r\n" \
            "movq %%r8, %%rdx \r\n" \
            "movq %%r9, %%rcx \r\n" \
            "movq %%r10, %%r8 \r\n" \
            "movq %%r11, %%r9 \r\n" \
            "callq "#slab_name"_interface \r\n"		\
            "popq %%r9 \r\n" \
            "movq %0, %%rdi \r\n" \
            "sysenter \r\n" \
            \
            "int $0x03 \r\n" \
            "1: jmp 1b \r\n" \
            \
			:  \
			:  "i" (XMHF_HIC_SLABRETINTERCEPT) \
			:  \
		);	\
    }\



#define XMHF_SLAB_EXCEPTION(slab_name)	\
	__attribute__ ((section(".rodata"))) char * slab_name##_string="_xmhfslab_"#slab_name"_";	\
	__attribute__ ((section(".stack"))) __attribute__ ((aligned(4096))) u8 slab_name##_slab_stack[MAX_PLATFORM_CPUS][XMHF_SLAB_STACKSIZE];	\
	__attribute__ ((section(".stackhdr"))) u64 slab_name##_slab_tos[MAX_PLATFORM_CPUS]= { ((u64)&slab_name##_slab_stack[0] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[1] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[2] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[3] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[4] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[5] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[6] + XMHF_SLAB_STACKSIZE), ((u64)&slab_name##_slab_stack[7] + XMHF_SLAB_STACKSIZE)  };	\
    __attribute__ ((section(".slab_dmadata"))) u8 slab_name##dmadataplaceholder[1];\
    \
    \
	__attribute__((naked)) __attribute__ ((section(".slab_entrystub"))) __attribute__((align(1))) void _slab_entrystub_##slab_name(void){	\
	asm volatile ( \
            "pushq %%r10 \r\n" \
            "movq %%r8, %%rdx \r\n" \
            "movq %%r9, %%rcx \r\n" \
            "movq %%r10, %%r8 \r\n" \
            "movq %%r11, %%r9 \r\n" \
            "callq "#slab_name"_interface \r\n"		\
            "popq %%r9 \r\n" \
            "movq %0, %%rdi \r\n" \
            "sysenter \r\n" \
            \
            "int $0x03 \r\n" \
            "1: jmp 1b \r\n" \
            \
			:  \
			:  "i" (XMHF_HIC_SLABRETEXCEPTION) \
			:  \
		);	\
    }\




#endif //__XMHF_VERIFICATION__





#endif //__ASSEMBLY__


#endif //__XMHFSLAB_H__

