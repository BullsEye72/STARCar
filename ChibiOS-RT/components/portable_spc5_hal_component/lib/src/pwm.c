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
 * @file    pwm.c
 * @brief   PWM Driver code.
 *
 * @addtogroup PWM
 * @{
 */

#include "hal.h"

#if HAL_USE_PWM || defined(__DOXYGEN__)

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
 * @brief   PWM Driver initialization.
 * @note    This function is implicitly invoked by @p halInit(), there is
 *          no need to explicitly initialize the driver.
 *
 * @init
 */
void pwmInit(void) {

  pwm_lld_init();
}

/**
 * @brief   Initializes the standard part of a @p PWMDriver structure.
 *
 * @param[out] pwmp     pointer to a @p PWMDriver object
 *
 * @init
 */
void pwmObjectInit(PWMDriver *pwmp) {

  pwmp->state    = PWM_STOP;
  pwmp->config   = NULL;
#if defined(PWM_DRIVER_EXT_INIT_HOOK)
  PWM_DRIVER_EXT_INIT_HOOK(pwmp);
#endif
}

/**
 * @brief   Configures and activates the PWM peripheral.
 * @note    Starting a driver that is already in the @p PWM_READY state
 *          disables all the active channels.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] config    pointer to a @p PWMConfig object
 *
 * @api
 */
void pwmStart(PWMDriver *pwmp, const PWMConfig *config) {

  osalDbgCheck((pwmp != NULL) && (config != NULL));

  osalSysLock();
  osalDbgAssert((pwmp->state == PWM_STOP) || (pwmp->state == PWM_READY),
                "invalid state");
  pwmp->config = config;
  pwmp->period = config->period;
  pwm_lld_start(pwmp);
  pwmp->state = PWM_READY;
  osalSysUnlock();
}

/**
 * @brief   Deactivates the PWM peripheral.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 *
 * @api
 */
void pwmStop(PWMDriver *pwmp) {

  osalDbgCheck(pwmp != NULL);

  osalSysLock();
  osalDbgAssert((pwmp->state == PWM_STOP) || (pwmp->state == PWM_READY),
                "invalid state");
  pwm_lld_stop(pwmp);
  pwmp->state = PWM_STOP;
  osalSysUnlock();
}

/**
 * @brief   Changes the period the PWM peripheral.
 * @details This function changes the period of a PWM unit that has already
 *          been activated using @p pwmStart().
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @post    The PWM unit period is changed to the new value.
 * @note    If a period is specified that is shorter than the pulse width
 *          programmed in one of the channels then the behavior is not
 *          guaranteed.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] period    new cycle time in ticks
 *
 * @api
 */
void pwmChangePeriod(PWMDriver *pwmp, pwmcnt_t period) {

  osalDbgCheck(pwmp != NULL);

  osalSysLock();
  osalDbgAssert(pwmp->state == PWM_READY,
                "invalid state");
  pwmChangePeriodI(pwmp, period);
  osalSysUnlock();
}

/**
 * @brief   Enables a PWM channel.
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @post    The channel is active using the specified configuration.
 * @note    Depending on the hardware implementation this function has
 *          effect starting on the next cycle (recommended implementation)
 *          or immediately (fallback implementation).
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] channel   PWM channel identifier (0...PWM_CHANNELS-1)
 * @param[in] width     PWM pulse width as clock pulses number
 *
 * @api
 */
void pwmEnableChannel(PWMDriver *pwmp,
                      pwmchannel_t channel,
                      pwmcnt_t width) {

  osalDbgCheck((pwmp != NULL) && (channel < PWM_CHANNELS));

  osalSysLock();
  osalDbgAssert(pwmp->state == PWM_READY, "not ready");
  pwm_lld_enable_channel(pwmp, channel, width);
  osalSysUnlock();
}

/**
 * @brief   Disables a PWM channel.
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @post    The channel is disabled and its output line returned to the
 *          idle state.
 * @note    Depending on the hardware implementation this function has
 *          effect starting on the next cycle (recommended implementation)
 *          or immediately (fallback implementation).
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] channel   PWM channel identifier (0...PWM_CHANNELS-1)
 *
 * @api
 */
void pwmDisableChannel(PWMDriver *pwmp, pwmchannel_t channel) {

  osalDbgCheck((pwmp != NULL) && (channel < PWM_CHANNELS));

  osalSysLock();
  osalDbgAssert(pwmp->state == PWM_READY, "not ready");
  pwm_lld_disable_channel(pwmp, channel);
  osalSysUnlock();
}

#endif /* HAL_USE_PWM */

/** @} */
