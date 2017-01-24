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

Thread *tpgps = NULL;
bool_t bGpsRunning = false;

/*
 * LEDs blinker thread, times are in milliseconds.
 */
WORKING_AREA(waThreadGPS, 128);
msg_t ThreadGPS(void *arg) {

  (void)arg;
  int i = 0;
  chRegSetThreadName("ThreadGPS");

  while (bGpsRunning) {
    chprintf((BaseSequentialStream *)arg,
             "$GPGGA,162431.531,%d,N,07602.498,W,0,00,,,M,,M,,*51\r\n", i);
    i++;
    chThdSleepMilliseconds(100);
  }

  chThdExit(0);

  return 0;
}

/*
 * Array of defined commands, you can add more.
 */
const ShellCommand shell_commands_car[] = { {"startgps", startgps}, {"stopgps",
                                                                     stopgps},
                                           {"speed", speed}, {"drive", drive}, {
                                               "turn", turn},
                                           {"blink", blink}, {"startdemo",
                                                              startdemo},
                                           {"stopdemo", stopdemo}, {NULL, NULL}};
