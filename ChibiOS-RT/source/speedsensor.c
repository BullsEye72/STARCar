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

#include "components.h"
#include "speedsensor.h"

unsigned long counter = 0;

#define SPEEDSENSOR vector41

/*
 * SpeedSensor or Events
 */
OSAL_IRQ_HANDLER(SPEEDSENSOR) {
  uint32_t sr0;

  OSAL_IRQ_PROLOGUE();

  /* Reading status bits.*/
  sr0 = SIU.ISR.R;

  /* Event 4 - EIRQ1*/
  if (sr0 & (1 << 1)) {
    SIU.ISR.B.EIF1 = 1;

    palTogglePad(PORT_C, PC_LEDBLEU);
  }

  /* Event 4 - EIRQ2*/
  if (sr0 & (1 << 2)) {
    SIU.ISR.B.EIF2 = 1;

    palTogglePad(PORT_C, PC_LEDROUGE);
  }

  /* Event 3 - EIRQ3*/
  if (sr0 & (1 << 3)) {
    SIU.ISR.B.EIF3 = 1;

    palTogglePad(PORT_A, PA_LEDJAUNE1);
    palTogglePad(PORT_A, PA_LEDJAUNE2);
  }

  /* Event 1 - EIRQ4*/
  if (sr0 & (1 << 4)) {
    SIU.ISR.B.EIF4 = 1;

    palTogglePad(PORT_B, PB_LEDBLANCHE);
  }

  /* Speed Sensor*/
  if (sr0 & (1 << 0)) {
    SIU.ISR.B.EIF0 = 1;
    counter++;
  }

  OSAL_IRQ_EPILOGUE();
}

void initSpeedSensor() {
  /* Enable Vector Interruption SIU External IRQ_0 */
  /* Cf Table 123                                  */
  INTC_PSR(41) = 7;

  /* Activate Rising Edge Events */
  SIU.IREER.B.IREE0 = 1;

  /* Enable EIRQ #0 */
  SIU.IRER.B.IRE0 = 1;
}

void initEvents() {
  /* Enable Vector Interruption SIU External IRQ_0 */
  /* Cf Table 123                                  */
  INTC_PSR(41) = 7;

  /* Activate EVENT4 - EIRQ1 */
  SIU.IFEER.B.IFEE1 = 1;
  SIU.IFER.B.IFE1 = 1;
  SIU.IFMC[1].R = 15;

  /* Activate EVENT2 - EIRQ2 */
  SIU.IFEER.B.IFEE2 = 1;
  SIU.IFER.B.IFE2 = 1;
  SIU.IFMC[2].R = 15;

  /* Activate EVENT3 - EIRQ3 */
  SIU.IFEER.B.IFEE3 = 1;
  SIU.IFER.B.IFE3 = 1;
  SIU.IFMC[3].R = 15;

  /* Activate EVENT1 - EIRQ4 */
  SIU.IFEER.B.IFEE4 = 1;
  SIU.IFER.B.IFE4 = 1;
  SIU.IFMC[4].R = 15;

  /* Enable EIRQ EVENT1-2-3-4 */
  SIU.IRER.B.IRE1 = 1;
  SIU.IRER.B.IRE2 = 1;
  SIU.IRER.B.IRE3 = 1;
  SIU.IRER.B.IRE4 = 1;
}

void resetSpeedSensor() {
  counter = 0;
}

