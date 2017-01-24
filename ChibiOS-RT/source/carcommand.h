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
#include <stdlib.h>
#include <string.h>

void turncmd(int direction);
void drivecmd(int direction,int speed);
void stopcmd(void);
