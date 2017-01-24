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

#include "hal.h"

#if HAL_USE_PAL || defined(__DOXYGEN__)
/* Initial setup of all defined pads, the list is terminated by a {-1, 0, 0}.*/
static const spc_siu_init_t spc_siu_init[] = {
  {PCR(PORT_A, PIN_WHEEL),  PAL_LOW,    PAL_MODE_OUTPUT_ALTERNATE(1)},
  {PCR(PORT_A, PA_BUTTON),  PAL_LOW,    PAL_MODE_INPUT_PULLUP},
  {PCR(PORT_A, PIN_EVENT1), PAL_LOW,    PAL_MODE_INPUT_PULLUP},
  {PCR(PORT_B, PB_LIN0_TDX), PAL_HIGH,   PAL_MODE_OUTPUT_ALTERNATE(1)},
  {PCR(PORT_B, PB_LIN0_RDX), PAL_HIGH,   PAL_MODE_INPUT},
  {PCR(PORT_B, PIN_BUTTON1), PAL_LOW,    PAL_MODE_INPUT},
  {PCR(PORT_B, PB_TRIMMER), PAL_LOW,    PAL_MODE_INPUT_ANALOG},
  {PCR(PORT_B, PIN_IN2),    PAL_LOW,    PAL_MODE_OUTPUT_PUSHPULL},
  {PCR(PORT_B, PIN_IN1),    PAL_LOW,    PAL_MODE_OUTPUT_PUSHPULL},
  {PCR(PORT_B, PIN_IN3),    PAL_LOW,    PAL_MODE_OUTPUT_PUSHPULL},
  {PCR(PORT_A, PIN_SPEEDSENSOR), PAL_LOW,    PAL_MODE_INPUT_PULLUP},
  {PCR(PORT_B, PIN_IN4),    PAL_LOW,    PAL_MODE_OUTPUT_PUSHPULL},
  {PCR(PORT_C, PC_LED8),    PAL_LOW,    PAL_MODE_OUTPUT_PUSHPULL},
  {PCR(PORT_C, PC_LED7),    PAL_LOW,    PAL_MODE_OUTPUT_PUSHPULL},
  {PCR(PORT_C, PIN_LIN1_TDX), PAL_LOW,    PAL_MODE_OUTPUT_ALTERNATE(1)},
  {PCR(PORT_C, PIN_LIN1_RDX), PAL_LOW,    PAL_MODE_INPUT},
  {PCR(PORT_A, PIN_EVENT4), PAL_LOW,    PAL_MODE_INPUT_PULLUP},
  {PCR(PORT_A, PIN_EVENT2), PAL_LOW,    PAL_MODE_INPUT_PULLUP},
  {PCR(PORT_A, PIN_EVENT3), PAL_LOW,    PAL_MODE_INPUT_PULLUP},
  {PCR(PORT_A, PIN_MOTOR),  PAL_LOW,    PAL_MODE_OUTPUT_ALTERNATE(1)},
  {PCR(PORT_C, PC_LEDBLEU), PAL_LOW,    PAL_MODE_OUTPUT_PUSHPULL},
  {PCR(PORT_B, PB_LEDBLANCHE), PAL_LOW,    PAL_MODE_OUTPUT_PUSHPULL},
  {PCR(PORT_A, PA_LEDJAUNE1), PAL_LOW,    PAL_MODE_OUTPUT_PUSHPULL},
  {PCR(PORT_A, PA_LEDJAUNE2), PAL_LOW,    PAL_MODE_OUTPUT_PUSHPULL},
  {PCR(PORT_C, PC_LEDROUGE), PAL_LOW,    PAL_MODE_OUTPUT_PUSHPULL},
  {-1, 0, 0}
};

/* Initialization array for the PSMI registers.*/
static const uint8_t spc_padsels_init[SPC5_SIUL_NUM_PADSELS] = {
  0,   0,   0,   0,   0,   0,   0,   0,   
  0,   0,   0,   0,   0,   0,   0,   0,   
  0,   0,   0,   0,   0,   0,   0,   0,   
  0,   0,   0,   0,   0,   0,   0,   0,   
  0,   0,   0,   0,   0,   0,   0,   0,   
  0,   0,   0,   0,   0,   0,   0,   0,   
  0,   0,   0,   0,   0,   0,   0,   0,   
  0,   0,   0,   0,   0,   0,   0,   
};

/**
 * @brief   PAL setup.
 */
const PALConfig pal_default_config = {
  PAL_MODE_UNCONNECTED,
  spc_siu_init,
  spc_padsels_init
};
#endif

/*
 * Early initialization code.
 * This initialization must be performed just after stack setup and before
 * any other initialization.
 */
void __early_init(void) {

  spc_clock_init();
}

/*
 * Board-specific initialization code.
 */
void boardInit(void) {
}
