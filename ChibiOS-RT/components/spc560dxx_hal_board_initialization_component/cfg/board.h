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

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for a generic SPC560Dxx board.
 */

/*
 * Board identifiers.
 */
#define BOARD_SPC56D_DISCOVERY
#define BOARD_NAME                  "STMicroelectronics SPC56D Discovery"

/*
 * Board frequencies.
 */
#if !defined(SPC5_XOSC_CLK)
#define SPC5_XOSC_CLK               16000000
#endif

/*
 * I/O definitions.
 */
#define PIN_WHEEL                   10
#define PA_BUTTON                   11
#define PIN_EVENT1                  14
#define PB_LIN0_TDX                 2
#define PB_LIN0_RDX                 3
#define PIN_BUTTON1                 4
#define PB_TRIMMER                  8
#define PIN_IN2                     10
#define PIN_IN1                     12
#define PIN_IN3                     13
#define PIN_SPEEDSENSOR             3
#define PIN_IN4                     14
#define PC_LED8                     2
#define PC_LED7                     3
#define PIN_LIN1_TDX                6
#define PIN_LIN1_RDX                7
#define PIN_EVENT4                  6
#define PIN_EVENT2                  7
#define PIN_EVENT3                  8
#define PIN_MOTOR                   9
#define PC_LEDBLEU                  4
#define PB_LEDBLANCHE               1
#define PA_LEDJAUNE1                2
#define PA_LEDJAUNE2                1
#define PC_LEDROUGE                 9

/*
 * Support macros.
 */
#define PCR(port, pin)  (((port) * 16) + (pin))

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
