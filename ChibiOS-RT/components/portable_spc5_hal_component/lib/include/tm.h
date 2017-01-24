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
 * @file    tm.h
 * @brief   Time Measurement driver header.
 *
 * @addtogroup TM
 * @{
 */

#ifndef _TM_H_
#define _TM_H_

#if HAL_USE_TM || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a Time Measurement object.
 * @note    Start/stop of measurements is performed through the function
 *          pointers in order to avoid inlining of those functions which
 *          could compromise measurement accuracy.
 * @note    The maximum measurable time period depends on the implementation
 *          of the realtime counter in the HAL driver.
 * @note    The measurement is not 100% cycle-accurate, it can be in excess
 *          of few cycles depending on the compiler and target architecture.
 * @note    Interrupts can affect measurement if the measurement is performed
 *          with interrupts enabled.
 */
typedef struct TimeMeasurement TimeMeasurement;

/**
 * @brief   Time Measurement structure.
 */
struct TimeMeasurement {
  void (*start)(TimeMeasurement *tmp);  /**< @brief Starts a measurement.   */
  void (*stop)(TimeMeasurement *tmp);   /**< @brief Stops a measurement.    */
  halrtcnt_t           last;            /**< @brief Last measurement.       */
  halrtcnt_t           worst;           /**< @brief Worst measurement.      */
  halrtcnt_t           best;            /**< @brief Best measurement.       */
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Starts a measurement.
 * @pre     The @p TimeMeasurement must be initialized.
 * @note    This function can be invoked in any context.
 *
 * @param[in,out] tmp   pointer to a @p TimeMeasurement structure
 *
 * @special
 */
#define tmStartMeasurement(tmp) (tmp)->start(tmp)

/**
 * @brief   Stops a measurement.
 * @pre     The @p TimeMeasurement must be initialized.
 * @note    This function can be invoked in any context.
 *
 * @param[in,out] tmp   pointer to a @p TimeMeasurement structure
 *
 * @special
 */
#define tmStopMeasurement(tmp) (tmp)->stop(tmp)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void tmInit(void);
  void tmObjectInit(TimeMeasurement *tmp);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_TM */

#endif /* _TM_H_ */

/** @} */
