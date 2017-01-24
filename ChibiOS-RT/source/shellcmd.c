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

int iCarBlinker = 0;
bool_t bFullDemoRunning = false;

/*
 * LEDs blinker thread, times are in milliseconds.
 */
WORKING_AREA(waThreadCarBlinker, 128);
msg_t ThreadCarBlinker(void *arg) {
  (void)arg;
  chRegSetThreadName("ThreadCarBlinker");

  while (iCarBlinker) {
    if (iCarBlinker == 1) {
      palTogglePad(PORT_A, PA_LEDJAUNE1);
    }
    else if (iCarBlinker == 2) {
      palTogglePad(PORT_A, PA_LEDJAUNE2);
    }
    else {
      palClearPad(PORT_A, PA_LEDJAUNE1);
      palClearPad(PORT_A, PA_LEDJAUNE2);
    }

    osalThreadSleepMilliseconds(500);
  }

  palClearPad(PORT_A, PA_LEDJAUNE1);
  palClearPad(PORT_A, PA_LEDJAUNE2);

  chThdExit(0);

  return 0;
}

/*
 * Full Demo thread, times are in milliseconds.
 */
WORKING_AREA(waThreadFullDemo, 128);
msg_t ThreadFullDemo(void *arg) {
  (void)arg;
  chRegSetThreadName("ThreadFullDemo");

  while (bFullDemoRunning) {

    /* Forward during 5 s*/
    if (bFullDemoRunning)
      drivecmd(1, 5000);
    else {
      stopcmd();
      break;
    }

    osalThreadSleepMilliseconds(5000);

    /* Reverse during 5 s*/
    if (bFullDemoRunning)
      drivecmd(2, 5000);
    else
      break;

    osalThreadSleepMilliseconds(5000);

    /* Turn Left*/
    if (bFullDemoRunning)
      turncmd(1);
    else {
      stopcmd();
      break;
    }

    osalThreadSleepMilliseconds(5000);

    /* Turn Right*/
    if (bFullDemoRunning)
      turncmd(2);
    else {
      stopcmd();
      break;
    }

    osalThreadSleepMilliseconds(5000);

    /* Straight Away*/
    if (bFullDemoRunning)
      turncmd(0);
    else {
      stopcmd();
      break;
    }

    osalThreadSleepMilliseconds(5000);

    /* Stop all the motors */
    if (bFullDemoRunning)
      stopcmd();
    else {
      stopcmd();
      break;
    }

    /* Blink the car */
    if (bFullDemoRunning) {
      bLightOn = true;
    }
    else {
      stopcmd();
      break;
    }
    osalThreadSleepMilliseconds(20000);
    bLightOn = false;
  }

  chThdExit(0);

  return 0;
}

/*
 * Memory statistics.
 */
void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[]) {
  size_t n, size;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: mem\r\n");
    return;
  }
  n = chHeapStatus(NULL, &size);
  chprintf(chp, "core free memory : %u bytes\r\n", chCoreStatus());
  chprintf(chp, "heap fragments   : %u\r\n", n);
  chprintf(chp, "heap free total  : %u bytes\r\n", size);
}

/*
 * List of threads.
 */
void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[]) {
  static const char *states[] = {THD_STATE_NAMES};
  Thread *tp;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: threads\r\n");
    return;
  }
  chprintf(chp, "    addr    stack prio refs     state time\r\n");
  tp = chRegFirstThread();
  do {
    chprintf(chp, "%.8lx %.8lx %4lu %4lu %9s %lu\r\n", (uint32_t)tp,
             (uint32_t)tp->p_ctx.sp, (uint32_t)tp->p_prio,
             (uint32_t)(tp->p_refs - 1), states[tp->p_state],
             (uint32_t)tp->p_time);
    tp = chRegNextThread(tp);
  } while (tp != NULL);
}

/*
 * Send a AT Command
 */
static void cmd_at(BaseSequentialStream *chp, int argc, char *argv[]) {

  char pval[30];

  (void)argv;
  if (argc == 0) {
    chprintf(chp, "Usage: send <ATCOMMAND>\r\n");
    chprintf(chp,
             "WARNING : BT device should not be connected on any terminal\r\n");
    return;
  }

  get_string(argv[0], pval, 1000);
  chprintf(chp, pval);
  chprintf(chp, "\r\n");
}

/*
 * Start GPS Frames
 */
void startgps(BaseSequentialStream *chp, int argc, char *argv[]) {

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: startgps\r\n");
    return;
  }

  /*
   * Creates the GPS thread.
   */
  if (bGpsRunning == false) {
    bGpsRunning = true;
    chprintf(chp, "ThreadGPS started\r\n");
    tpgps = chThdCreateStatic(waThreadGPS, sizeof(waThreadGPS), NORMALPRIO,
                              ThreadGPS, &SD2);
  }
  else {
    chprintf(chp, "ThreadGPS already started\r\n");
  }
}

/*
 * Stop GPS Frames
 */
void stopgps(BaseSequentialStream *chp, int argc, char *argv[]) {

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: stopgps\r\n");
    return;
  }

  /*
   * Suspend the GPS Thread.
   */
  if (bGpsRunning) {
    bGpsRunning = false;
    chprintf(chp, "ThreadGPS terminated\r\n");
  }
  if (bGpsRunning) {
    chprintf(chp, "ThreadGPS not running\r\n");
  }
}

/*
 * Display Speed Counter
 */
void speed(BaseSequentialStream *chp, int argc, char *argv[]) {

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: speed\r\n");
    return;
  }

  /*
   * Display the Speed Counter.
   */
  chprintf(chp, "Speed %d\r\n", counter);
}

/*
 * drive motor
 */
void drive(BaseSequentialStream *chp, int argc, char *argv[]) {

  int speed = 0;
  int direction = 0;

  (void)argv;
  if (argc != 2) {
    chprintf(chp, "Usage: drive <DIRECTION (0/1/2)> <SPEED (0-10000)>\r\n");
    return;
  }

  direction = atoi(argv[0]);
  speed = atoi(argv[1]);

  if ((speed < 0) || (speed > 10000)) {
    chprintf(chp, "Please between 0 and 10000\r\n");
  }
  else {
    drivecmd(direction, speed);
  }

}

/*
 *  turn
 */
void turn(BaseSequentialStream *chp, int argc, char *argv[]) {

  int direction = 0;

  (void)argv;
  if (argc != 1) {
    chprintf(chp, "Usage: turn <DIRECTION (0/1/2)>\r\n");
    return;
  }

  direction = atoi(argv[0]);

  /* Call the Command turn*/
  turncmd(direction);
}

/*
 * blink the car
 */
void blink(BaseSequentialStream *chp, int argc, char *argv[]) {

  int direction = 0;

  (void)argv;
  if (argc == 0) {
    chprintf(chp, "Usage: blink <0/1>\r\n");
    return;
  }

  direction = atoi(argv[0]);

  if (direction) {
    bLightOn = true;
  }
  else {
    bLightOn = false;
  }
}

/*
 * full demo start spc5carsimu
 */
void startdemo(BaseSequentialStream *chp, int argc, char *argv[]) {

  (void)argv;
  if (argc != 0) {
    chprintf(chp, "Usage: startdemo\r\n");
    return;
  }

  if (bFullDemoRunning == false) {
    bFullDemoRunning = true;
    /*
     * Creates the Full Demo thread. (it does not exist)
     */
    chThdCreateStatic(waThreadFullDemo, sizeof(waThreadFullDemo), NORMALPRIO,
                      ThreadFullDemo, chp);
  }
  else {
    chprintf(chp, "Full Demo Already running\r\n");
  }

}

/*
 * full demo start spc5carsimu
 */
void stopdemo(BaseSequentialStream *chp, int argc, char *argv[]) {

  (void)argv;
  if (argc != 0) {
    chprintf(chp, "Usage: stopdemo\r\n");
    return;
  }

  bFullDemoRunning = false;
}

/*
 * Array of defined commands, you can add more.
 */
const ShellCommand shell_commands[] = { {"mem", cmd_mem}, {"threads",
                                                           cmd_threads},
                                       {"send", cmd_at}, {"startgps", startgps},
                                       {"stopgps", stopgps}, {"speed", speed}, {
                                           "drive", drive},
                                       {"turn", turn}, {"blink", blink}, {
                                           "startdemo", startdemo},
                                       {"stopdemo", stopdemo}, {NULL, NULL}};
