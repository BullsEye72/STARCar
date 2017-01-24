/*
 * Licensed under ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "hal.h"
#include "ch.h"
#include "shell.h"
#include "chprintf.h"
#include "shellcmd.h"
#include "shellbt.h"
#include "serial_input.h"
#include "speedsensor.h"
#include "carcommand.h"
#include <stdlib.h>
#include <string.h>

void turncmd(int direction) {
  if (direction == 1) {
    palClearPad(PORT_B, PIN_IN3);
    palSetPad(PORT_B, PIN_IN4);
    /*
     * Starts the PWM channel 1 using percentage dutsetspeedy cycle.
     */
    pwmEnableChannel(&PWMD1, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 10000));

    if (iCarBlinker == 0) {
      iCarBlinker = 1;
      /*
       * Creates the car blinker thread. (it does not exist)
       */
      chThdCreateStatic(waThreadCarBlinker, sizeof(waThreadCarBlinker),
      NORMALPRIO,
                        ThreadCarBlinker, NULL);
    }
    else {
      iCarBlinker = 1;
    }
  }
  else if (direction == 2) {
    palSetPad(PORT_B, PIN_IN3);
    palClearPad(PORT_B, PIN_IN4);

    /*
     * Starts the PWM channel 1 using percentage dutsetspeedy cycle.
     */
    pwmEnableChannel(&PWMD1, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 10000));

    if (iCarBlinker == 0) {
      iCarBlinker = 2;

      /*
       * Creates the car blinker thread. (it does not exist)
       */
      chThdCreateStatic(waThreadCarBlinker, sizeof(waThreadCarBlinker),
      NORMALPRIO,
                        ThreadCarBlinker, NULL);
    }
    else {
      iCarBlinker = 2;
    }

  }
  else {
    /* Shutdown the wheel */
    palClearPad(PORT_B, PIN_IN3);
    palClearPad(PORT_B, PIN_IN4);
    /*
     * Starts the PWM channel 1 using percentage dutsetspeedy cycle.
     */
    pwmEnableChannel(&PWMD1, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 0));

    iCarBlinker = 0;
  }
}

void drivecmd(int direction, int speed) {
  if (direction == 1) {
    palClearPad(PORT_B, PIN_IN1);
    palSetPad(PORT_B, PIN_IN2);
  }
  else if (direction == 2) {
    palSetPad(PORT_B, PIN_IN1);
    palClearPad(PORT_B, PIN_IN2);
  }
  else {
    /* Shutdown the motor */
    palClearPad(PORT_B, PIN_IN1);
    palClearPad(PORT_B, PIN_IN2);
  }
  /*
   * Starts the PWM channel 0 using percentage dutsetspeedy cycle.
   */
  pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, speed));
}

void stopcmd() {
  /* Shutdown the drive motor */
  palClearPad(PORT_B, PIN_IN1);
  palClearPad(PORT_B, PIN_IN2);

  /* Shutdown the wheel */
  palClearPad(PORT_B, PIN_IN3);
  palClearPad(PORT_B, PIN_IN4);

}

