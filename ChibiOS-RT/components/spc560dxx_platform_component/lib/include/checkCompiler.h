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
 * @file    checkCompiler.h
 * @brief   checkCompiler for PPC Compilers
 * @{
 */

#ifndef _CHECKCOMPILER_H_
#define _CHECKCOMPILER_H_

#if defined(__ghs_asm)
#define HI(R)    %hi(R) 
#define LO(R)    %lo(R)
#define _VLE     .vle
#define _NOVLE   .novle
#else
#define HI(R)    R@h
#define LO(R)    R@l
#define _VLE
#define _NOVLE
#endif /* __ghs_asm */

#if defined(__hightec_asm)
#define se_bge   bge
#define e_beq    beq
#define se_bne   bne
#endif /* __hightec_asm */

#endif /* _CHECKCOMPILER_H_ */
