/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

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
 * @file    icu.c
 * @brief   ICU Driver code.
 *
 * @addtogroup ICU
 * @{
 */

#include "hal.h"

#if HAL_USE_ICU || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   ICU Driver initialization.
 * @note    This function is implicitly invoked by @p halInit(), there is
 *          no need to explicitly initialize the driver.
 *
 * @init
 */
void icuInit(void) {

  icu_lld_init();
}

/**
 * @brief   Initializes the standard part of a @p ICUDriver structure.
 *
 * @param[out] icup     pointer to the @p ICUDriver object
 *
 * @init
 */
void icuObjectInit(ICUDriver *icup) {

  icup->state  = ICU_STOP;
  icup->config = NULL;
}

/**
 * @brief   Configures and activates the ICU peripheral.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 * @param[in] config    pointer to the @p ICUConfig object
 *
 * @api
 */
void icuStart(ICUDriver *icup, const ICUConfig *config) {

  osalDbgCheck((icup != NULL) && (config != NULL));

  osalSysLock();
  osalDbgAssert((icup->state == ICU_STOP) || (icup->state == ICU_READY),
                "invalid state");
  icup->config = config;
  icu_lld_start(icup);
  icup->state = ICU_READY;
  osalSysUnlock();
}

/**
 * @brief   Deactivates the ICU peripheral.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @api
 */
void icuStop(ICUDriver *icup) {

  osalDbgCheck(icup != NULL);

  osalSysLock();
  osalDbgAssert((icup->state == ICU_STOP) || (icup->state == ICU_READY),
                "invalid state");
  icu_lld_stop(icup);
  icup->state = ICU_STOP;
  osalSysUnlock();
}

/**
 * @brief   Enables the input capture.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @api
 */
void icuEnable(ICUDriver *icup) {

  osalDbgCheck(icup != NULL);

  osalSysLock();
  osalDbgAssert(icup->state == ICU_READY, "invalid state");
  icu_lld_enable(icup);
  icup->state = ICU_WAITING;
  osalSysUnlock();
}

/**
 * @brief   Disables the input capture.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @api
 */
void icuDisable(ICUDriver *icup) {

  osalDbgCheck(icup != NULL);

  osalSysLock();
  osalDbgAssert((icup->state == ICU_READY) || (icup->state == ICU_WAITING) ||
                (icup->state == ICU_ACTIVE) || (icup->state == ICU_IDLE),
                "invalid state");
  icu_lld_disable(icup);
  icup->state = ICU_READY;
  osalSysUnlock();
}

#endif /* HAL_USE_ICU */

/** @} */
