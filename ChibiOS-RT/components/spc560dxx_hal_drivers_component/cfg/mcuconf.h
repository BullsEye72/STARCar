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

#ifndef _MCUCONF_H_
#define _MCUCONF_H_

/*
 * SPC560Dxx drivers configuration.
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * IRQ priorities:
 * 1...15       Lowest...Highest.
 * DMA priorities:
 * 0...15       Highest...Lowest.
 */

#define SPC560Dxx_MCUCONF

/*
 * HAL driver system settings.
 */
#define SPC5_NO_INIT                        FALSE
#define SPC5_ALLOW_OVERCLOCK                FALSE
#define SPC5_DISABLE_WATCHDOG               TRUE
#define SPC5_FMPLL_IDF_VALUE                2U
#define SPC5_FMPLL_NDIV_VALUE               48U
#define SPC5_FMPLL_ODF                      SPC5_FMPLL_ODF_DIV8
#define SPC5_FMPLL_OPTIONS                  (0U)
#define SPC5_FMPLL_MR_INIT                  (0U)
#define SPC5_XOSCDIV_VALUE                  1U
#define SPC5_FIRCDIV_VALUE                  1U
#define SPC5_PERIPHERAL1_CLK_DIV_VALUE      2U
#define SPC5_PERIPHERAL2_CLK_DIV_VALUE      2U
#define SPC5_PERIPHERAL3_CLK_DIV_VALUE      2U
#define SPC5_SIRCDIV_VALUE                  4U
#define SPC5_API_RTC_CLK_SRC                SPC5_RTCC_CLKSEL_SIRCDIV
#define SPC5_CLKOUT_SRC                     SPC5_CGM_OCDS_SELCTL_FMPLL
#define SPC5_CLKOUT_DIV_VALUE               2U
#define SPC5_CMU_CSR_INIT                   (SPC5_CMU_CSR_RCDIV(0))
#define SPC5_CMU_HFREFR_INIT                4095
#define SPC5_CMU_LFREFR_INIT                0
#define SPC5_CMU_MDR_INIT                   0
#define SPC5_ME_ME_BITS                     (0UL | SPC5_ME_ME_RESET | SPC5_ME_ME_SAFE | SPC5_ME_ME_DRUN | SPC5_ME_ME_RUN0 | SPC5_ME_ME_RUN1 | SPC5_ME_ME_RUN2 | SPC5_ME_ME_RUN3 | SPC5_ME_ME_HALT | SPC5_ME_ME_STOP | SPC5_ME_ME_STANDBY)
#define SPC5_ME_SAFE_MC_BITS                (0UL | SPC5_ME_MC_PDO | SPC5_ME_MC_MVRON | SPC5_ME_MC_DFLAON_NORMAL | SPC5_ME_MC_CFLAON_NORMAL | SPC5_ME_MC_FIRCON | SPC5_ME_MC_SYSCLK_FIRC)
#define SPC5_ME_DRUN_MC_BITS                (0UL | SPC5_ME_MC_MVRON | SPC5_ME_MC_DFLAON_NORMAL | SPC5_ME_MC_CFLAON_NORMAL | SPC5_ME_MC_FMPLLON | SPC5_ME_MC_XOSCON | SPC5_ME_MC_FIRCON | SPC5_ME_MC_SYSCLK_FMPLL)
#define SPC5_ME_RUN0_MC_BITS                (0UL | SPC5_ME_MC_MVRON | SPC5_ME_MC_DFLAON_NORMAL | SPC5_ME_MC_CFLAON_NORMAL | SPC5_ME_MC_FMPLLON | SPC5_ME_MC_XOSCON | SPC5_ME_MC_FIRCON | SPC5_ME_MC_SYSCLK_FMPLL)
#define SPC5_ME_RUN1_MC_BITS                (0UL | SPC5_ME_MC_MVRON | SPC5_ME_MC_DFLAON_NORMAL | SPC5_ME_MC_CFLAON_NORMAL | SPC5_ME_MC_FIRCON | SPC5_ME_MC_SYSCLK_FIRC)
#define SPC5_ME_RUN2_MC_BITS                (0UL | SPC5_ME_MC_MVRON | SPC5_ME_MC_DFLAON_NORMAL | SPC5_ME_MC_CFLAON_NORMAL | SPC5_ME_MC_FIRCON | SPC5_ME_MC_SYSCLK_FIRC)
#define SPC5_ME_RUN3_MC_BITS                (0UL | SPC5_ME_MC_MVRON | SPC5_ME_MC_DFLAON_NORMAL | SPC5_ME_MC_CFLAON_NORMAL | SPC5_ME_MC_FIRCON | SPC5_ME_MC_SYSCLK_FIRC)
#define SPC5_ME_HALT_MC_BITS                (0UL | SPC5_ME_MC_MVRON | SPC5_ME_MC_DFLAON_NORMAL | SPC5_ME_MC_CFLAON_NORMAL | SPC5_ME_MC_FIRCON | SPC5_ME_MC_SYSCLK_FIRC)
#define SPC5_ME_STOP_MC_BITS                (0UL | SPC5_ME_MC_MVRON | SPC5_ME_MC_DFLAON_PD | SPC5_ME_MC_CFLAON_PD | SPC5_ME_MC_FIRCON | SPC5_ME_MC_SYSCLK_FIRC)
#define SPC5_ME_STANDBY_MC_BITS             (0UL | SPC5_ME_MC_PDO | SPC5_ME_MC_DFLAON_PD | SPC5_ME_MC_CFLAON_PD | SPC5_ME_MC_FIRCON | SPC5_ME_MC_SYSCLK_DISABLED)
#define SPC5_ME_RUN_PC3_BITS                (0UL)
#define SPC5_ME_RUN_PC4_BITS                (0UL)
#define SPC5_ME_RUN_PC5_BITS                (0UL)
#define SPC5_ME_RUN_PC6_BITS                (0UL)
#define SPC5_ME_RUN_PC7_BITS                (0UL)
#define SPC5_ME_LP_PC4_BITS                 (0UL)
#define SPC5_ME_LP_PC5_BITS                 (0UL)
#define SPC5_ME_LP_PC6_BITS                 (0UL)
#define SPC5_ME_LP_PC7_BITS                 (0UL)
#define SPC5_FINAL_RUNMODE                  SPC5_RUNMODE_RUN0
#define SPC5_CLOCK_FAILURE_HOOK()           osalSysHalt("clock failure")

#define SPC5_EMIOS0_GPRE_VALUE              20

/*
 * EDMA driver settings.
 */
#define SPC5_EDMA_CR_SETTING                (EDMA_CR_EMLM)
#define SPC5_EDMA_GROUP0_PRIORITIES         0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
#define SPC5_EDMA_ERROR_IRQ_PRIO            12
#define SPC5_EDMA_ERROR_HANDLER()           osalSysHalt("DMA failure")

/*
 * SERIAL driver system settings.
 */
#define SPC5_SERIAL_USE_LINFLEX0            TRUE
#define SPC5_SERIAL_USE_LINFLEX1            TRUE
#define SPC5_SERIAL_USE_LINFLEX2            FALSE
#define SPC5_SERIAL_LINFLEX0_PRIORITY       8
#define SPC5_SERIAL_LINFLEX1_PRIORITY       8
#define SPC5_SERIAL_LINFLEX2_PRIORITY       8

/*
 * SPI driver system settings.
 */
#define SPC5_SPI_USE_DSPI0                  FALSE
#define SPC5_SPI_USE_DSPI1                  FALSE
#define SPC5_SPI_DMA_MODE                   SPC5_SPI_DMA_RX_ONLY
#define SPC5_SPI_DSPI0_MCR                  (0 | SPC5_MCR_PCSIS0 | SPC5_MCR_PCSIS1 | SPC5_MCR_PCSIS2 | SPC5_MCR_PCSIS3 | SPC5_MCR_PCSIS4 | SPC5_MCR_PCSIS5)
#define SPC5_SPI_DSPI1_MCR                  (0 | SPC5_MCR_PCSIS0 | SPC5_MCR_PCSIS1 | SPC5_MCR_PCSIS2 | SPC5_MCR_PCSIS3 | SPC5_MCR_PCSIS4)
#define SPC5_SPI_DSPI0_TX1_DMA_CH_ID        4
#define SPC5_SPI_DSPI0_TX2_DMA_CH_ID        5
#define SPC5_SPI_DSPI0_RX_DMA_CH_ID         6
#define SPC5_SPI_DSPI1_TX1_DMA_CH_ID        7
#define SPC5_SPI_DSPI1_TX2_DMA_CH_ID        8
#define SPC5_SPI_DSPI1_RX_DMA_CH_ID         9
#define SPC5_SPI_DSPI0_DMA_IRQ_PRIO         10
#define SPC5_SPI_DSPI1_DMA_IRQ_PRIO         10
#define SPC5_SPI_DSPI0_IRQ_PRIO             10
#define SPC5_SPI_DSPI1_IRQ_PRIO             10
#define SPC5_SPI_DMA_ERROR_HOOK(spip)       osalSysHalt("DSPI DMA failure")

/*
 * ICU-PWM driver system settings.
 */
#define SPC5_ICU_USE_EMIOS0_CH0             FALSE
#define SPC5_ICU_USE_EMIOS0_CH1             FALSE
#define SPC5_ICU_USE_EMIOS0_CH2             FALSE
#define SPC5_ICU_USE_EMIOS0_CH3             FALSE
#define SPC5_ICU_USE_EMIOS0_CH4             FALSE
#define SPC5_ICU_USE_EMIOS0_CH5             FALSE
#define SPC5_ICU_USE_EMIOS0_CH6             FALSE
#define SPC5_ICU_USE_EMIOS0_CH7             FALSE
#define SPC5_ICU_USE_EMIOS0_CH24            FALSE

#define SPC5_PWM_USE_EMIOS0_GROUP0          TRUE
#define SPC5_PWM_USE_EMIOS0_GROUP1          FALSE

#define SPC5_EMIOS0_GFR_F0F1_PRIORITY       8
#define SPC5_EMIOS0_GFR_F2F3_PRIORITY       8
#define SPC5_EMIOS0_GFR_F4F5_PRIORITY       8
#define SPC5_EMIOS0_GFR_F6F7_PRIORITY       8
#define SPC5_EMIOS0_GFR_F8F9_PRIORITY       8
#define SPC5_EMIOS0_GFR_F10F11_PRIORITY     8
#define SPC5_EMIOS0_GFR_F12F13_PRIORITY     8
#define SPC5_EMIOS0_GFR_F14F15_PRIORITY     8
#define SPC5_EMIOS0_GFR_F16F17_PRIORITY     8
#define SPC5_EMIOS0_GFR_F18F19_PRIORITY     8
#define SPC5_EMIOS0_GFR_F20F21_PRIORITY     8
#define SPC5_EMIOS0_GFR_F22F23_PRIORITY     8
#define SPC5_EMIOS0_GFR_F24F25_PRIORITY     8

#define SPC5_EMIOS0_START_PCTL              (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_EMIOS0_STOP_PCTL               (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))

/*
 * CAN driver system settings.
 */
#define SPC5_CAN_USE_FILTERS                FALSE

#define SPC5_CAN_USE_FLEXCAN0               FALSE
#define SPC5_CAN_FLEXCAN0_USE_EXT_CLK       FALSE
#define SPC5_CAN_FLEXCAN0_PRIORITY          12
#define SPC5_CAN_NUM_RX_MAILBOXES			8
#define SPC5_CAN_NUM_TX_MAILBOXES			24
#define SPC5_CAN_FLEXCAN0_START_PCTL        (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_CAN_FLEXCAN0_STOP_PCTL         (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))

/*
* ADC driver system settings.
*/


#define SPC5_ADC_DMA_MODE                   SPC5_ADC_DMA_ON

#define SPC5_ADC_USE_ADC1                   FALSE
#define SPC5_ADC_ADC1_CLK_FREQUENCY         HALF_PERIPHERAL_SET_CLOCK_FREQUENCY
#define SPC5_ADC_ADC1_AUTO_CLOCK_OFF        FALSE
#define SPC5_ADC_ADC1_WD_PRIORITY           12
#define SPC5_ADC_ADC1_EOC_PRIORITY          SPC5_ADC_ADC1_WD_PRIORITY
#define SPC5_ADC_ADC1_DMA_CH_ID             2
#define SPC5_ADC_ADC1_DMA_IRQ_PRIO          12
#define SPC5_ADC_ADC1_START_PCTL            (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_ADC_ADC1_STOP_PCTL             (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))

#endif /* _MCUCONF_H_ */
