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
 * @file    platform.h
 * @brief   Platform parameters for the SPC560Dxx.
 * @{
 */

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

/**
 * @brief   Specific model identification macro.
 */
#define _SPC560D40L1_

/**
 * @brief   Family identification macro.
 */
#define _SPC560Dxx_

/**
 * @brief   Power e200z core model.
 */
#define CORE_VARIANT                0

/**
 * @brief   Number of cores.
 */
#define CORE_NUMBER                 1

/**
 * @brief   Number of writable bits in IVPR register.
 */
#define CORE_IVPR_BITS              20

/**
 * @brief   IVORx registers support.
 */
#define CORE_SUPPORTS_IVORS         0

/**
 * @brief   Book E instruction set support.
 */
#define CORE_SUPPORTS_BOOKE         0

/**
 * @brief   VLE instruction set support.
 */
#define CORE_SUPPORTS_VLE           1

/**
 * @brief   Supports VLS Load/Store Multiple Volatile instructions.
 */
#define CORE_SUPPORTS_VLE_MULTI     1

/**
 * @brief   Supports the decrementer timer.
 */
#define CORE_SUPPORTS_DECREMENTER   0

#endif /* _PLATFORM_H_ */

/** @} */
