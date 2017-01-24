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

/*
 * Size of the stack used by the shell thread.
 */
#define SHELL_WA_SIZE   THD_WA_SIZE(1024)

/*
 * Array of the custom shell commands.
 */
extern const ShellCommand shell_commands[];
extern bool_t bLightOn;
extern int iCarBlinker;
extern bool_t bFullDemoRunning;

extern WORKING_AREA(waThreadCarBlinker, 128);
msg_t ThreadCarBlinker(void *arg);
extern WORKING_AREA(waThreadFullDemo, 128);
msg_t ThreadFullDemo(void *arg);

/*
 * Function availables for BT and SERIAL(FTDI) Shells
 */
void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[]);
void startgps(BaseSequentialStream *chp, int argc, char *argv[]);
void stopgps(BaseSequentialStream *chp, int argc, char *argv[]);
void speed(BaseSequentialStream *chp, int argc, char *argv[]);
void forward(BaseSequentialStream *chp, int argc, char *argv[]);
void reverse(BaseSequentialStream *chp, int argc, char *argv[]);
void stop(BaseSequentialStream *chp, int argc, char *argv[]);
void drive(BaseSequentialStream *chp, int argc, char *argv[]);
void turn(BaseSequentialStream *chp, int argc, char *argv[]);
void blink(BaseSequentialStream *chp, int argc, char *argv[]);
void startdemo(BaseSequentialStream *chp, int argc, char *argv[]);
void stopdemo(BaseSequentialStream *chp, int argc, char *argv[]);
