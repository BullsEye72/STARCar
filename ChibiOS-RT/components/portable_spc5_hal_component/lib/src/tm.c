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
 * @file    tm.c
 * @brief   Time Measurement driver code.
 *
 * @addtogroup TM
 * @{
 */

#include "hal.h"

#if HAL_USE_TM || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/**
 * @brief   Subsystem calibration value.
 */
static halrtcnt_t measurement_offset;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   Starts a measurement.
 *
 * @param[in,out] tmp   pointer to a @p TimeMeasurement structure
 *
 * @notapi
 */
static void tm_start(TimeMeasurement *tmp) {

  tmp->last = halGetCounterValue();
}

/**
 * @brief   Stops a measurement.
 *
 * @param[in,out] tmp   pointer to a @p TimeMeasurement structure
 *
 * @notapi
 */
static void tm_stop(TimeMeasurement *tmp) {

  halrtcnt_t now = halGetCounterValue();
  tmp->last = now - tmp->last - measurement_offset;
  if (tmp->last > tmp->worst)
      tmp->worst = tmp->last;
  else if (tmp->last < tmp->best)
      tmp->best = tmp->last;
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes the Time Measurement unit.
 *
 * @init
 */
void tmInit(void) {
  TimeMeasurement tm;

  /* Time Measurement subsystem calibration, it does a null measurement
     and calculates the call overhead which is subtracted to real
     measurements.*/
  measurement_offset = 0;
  tmObjectInit(&tm);
  tmStartMeasurement(&tm);
  tmStopMeasurement(&tm);
  measurement_offset = tm.last;
}

/**
 * @brief   Initializes a @p TimeMeasurement object.
 *
 * @param[out] tmp      pointer to a @p TimeMeasurement structure
 *
 * @init
 */
void tmObjectInit(TimeMeasurement *tmp) {

  tmp->start = tm_start;
  tmp->stop  = tm_stop;
  tmp->last  = (halrtcnt_t)0;
  tmp->worst = (halrtcnt_t)0;
  tmp->best  = (halrtcnt_t)-1;
}

#endif /* HAL_USE_TM */

/** @} */
