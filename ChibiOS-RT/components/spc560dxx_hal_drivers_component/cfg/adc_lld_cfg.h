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
 * @file    adc_lld_cfg.h
 * @brief   ADC Driver configuration macros and structures.
 *
 * @addtogroup ADC
 * @{
 */

#ifndef _ADC_LLD_CFG_H_
#define _ADC_LLD_CFG_H_

#if HAL_USE_ADC || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Conversion groups constants
 * @{
 */
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/* List of the ADC0 ADCConversionGroup structures defined in adc_lld_cfg.c.*/

/* List of the ADC1 ADCConversionGroup structures defined in adc_lld_cfg.c.*/

#ifdef __cplusplus
extern "C" {
#endif
  /* List of the callback functions referenced from the ADC0 ADCConversionGroup
     structures in adc_lld_cfg.c.*/

  /* List of the callback functions referenced from the ADC1 ADCConversionGroup
     structures in adc_lld_cfg.c.*/
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_ADC */

#endif /* _ADC_LLD_CFG_H_ */

/** @} */
