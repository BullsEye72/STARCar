/*
    SPC5 HAL - Copyright (C) 2013 STMicroelectronics

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    crt0.s
 * @brief   Generic PowerPC startup file for GCC.
 *
 * @addtogroup PPC_STARTUP
 * @{
 */

#include "checkCompiler.h"

#if !defined(__DOXYGEN__)


        .section    .crt0, "axv"
        .align		2
        .globl      _boot_address
        .type       _boot_address, @function
_VLE
_boot_address:
        /*
         * Stack setup.
         */
		e_lis       %r1, HI(__process_stack_end__)
        e_or2i      %r1, LO(__process_stack_end__)
        se_li       %r0, 0
        e_stwu      %r0, -8(%r1)
        /*
         * Small sections registers initialization.
         */
        e_lis       %r2,  HI(__sdata2_start__)
        e_or2i      %r2,  LO(__sdata2_start__)
        e_lis       %r13, HI(__sdata_start__)
        e_or2i      %r13, LO(__sdata_start__)
        /*
         * Early initialization.
         */
        e_bl        __early_init
        /*
         * BSS clearing.
         */
        e_lis       %r4, HI(__bss_start__)
        e_or2i      %r4, LO(__bss_start__)
        e_lis       %r5, HI(__bss_end__)
        e_or2i      %r5, LO(__bss_end__)
        se_li       %r7, 0
.bssloop:
_NOVLE
        cmpl        cr0, %r4, %r5
_VLE
        se_bge      .bssend
        se_stw      %r7, 0(%r4)
        se_addi     %r4, 4
        se_b        .bssloop
.bssend:
        /*
         * DATA initialization.
         */
        e_lis       %r4, HI(__romdata_start__)
        e_or2i      %r4, LO(__romdata_start__)
        e_lis       %r5, HI(__data_start__)
        e_or2i      %r5, LO(__data_start__)
        e_lis       %r6, HI(__data_end__)
        e_or2i      %r6, LO(__data_end__)
.dataloop:
_NOVLE
.align 2
        cmpl        cr0, %r5, %r6
_VLE
        se_bge      .dataend
        se_lwz      %r7, 0(%r4)
        se_addi     %r4, 4
        se_stw      %r7, 0(%r5)
        se_addi     %r5, 4
        se_b        .dataloop
.dataend:
        /*
         * Late initialization.
         */
        e_bl        __late_init
        /*
         * Main program invocation.
         */
        e_bl        main
        e_b         _main_exit_handler

        /*
         * Default main exit code, infinite loop.
         */
        .weak       _main_exit_handler
        .globl      _main_exit_handler
        .type       _main_exit_handler, @function
_main_exit_handler:
        e_b         _main_exit_handler

        /*
         * Default early initialization code, none.
         */
        .weak       __early_init
        .globl      __early_init
        .type       __early_init, @function
__early_init:
        se_blr

        /*
         * Default late initialization code, none.
         */
        .weak       __late_init
        .globl      __late_init
        .type       __late_init, @function
__late_init:
        se_blr
#endif /* !defined(__DOXYGEN__) */

/** @} */
