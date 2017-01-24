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
 * @file    pwm_lld_cfg.c
 * @brief   PWM Driver configuration code.
 *
 * @addtogroup PWM
 * @{
 */

#include "hal.h"
#include "pwm_lld_cfg.h"

#if HAL_USE_PWM || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   Structure defining the PWM configuration "cfgmotor".
 */
const PWMConfig pwm_config_cfgmotor = {
  100000,
  20000,
  NULL,
  {
    {
      PWM_OUTPUT_ACTIVE_HIGH,
      NULL
    },
    {
      PWM_OUTPUT_ACTIVE_HIGH,
      NULL
    },
    {
      PWM_OUTPUT_DISABLED,
      NULL
    },
    {
      PWM_OUTPUT_DISABLED,
      NULL
    },
    {
      PWM_OUTPUT_DISABLED,
      NULL
    },
    {
      PWM_OUTPUT_DISABLED,
      NULL
    },
    {
      PWM_OUTPUT_DISABLED,
      NULL
    }
  },
  PWM_ALIGN_EDGE
};

/*===========================================================================*/
/* Driver local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

#endif /* HAL_USE_PWM */

/** @} */
