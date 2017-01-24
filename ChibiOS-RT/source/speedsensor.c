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
extern int nBlinkers;
extern int nWiper;

unsigned long counter = 0;
extern int carMode;

/*
 * carMode
 * 0 : Rien
 * 1 : NUIT (EIRQ4)
 * 2 : PLUIE (EIRQ1)
 * 4 : URGENCE (EIRQ2)
 * 8 : SENS (EIRQ3)
 *
 * exemples
 * 1+2=3 : Nuit + Pluie
 * 2+8=10 : Pluie + Sens
 * 1+2+4+8=15 : Totale
 */


#define SPEEDSENSOR vector41

/*
 * SpeedSensor or Events
 */
OSAL_IRQ_HANDLER(SPEEDSENSOR) {
  uint32_t sr0;

  OSAL_IRQ_PROLOGUE();

  /* Reading status bits.*/
  sr0 = SIU.ISR.R;

  //=====================================
  /* Event 4 - EIRQ1*/
    if (sr0 & (1 << 1)) {/*BTN BLEU*/
      SIU.ISR.B.EIF1 = 1;
      pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 1000));
      palTogglePad(PORT_C, PC_LEDBLEU);
      nWiper=1;

		if (carMode>=2){
			carMode-=2;
		}else{
			carMode+=2;
		}
    }

    /* Event 4 - EIRQ2*/
    if (sr0 & (1 << 2)) {/*BTN ROUGE*/
      SIU.ISR.B.EIF2 = 1;
      /* Shutdown the motor */
         palClearPad(PORT_B, PIN_IN1);
         palClearPad(PORT_B, PIN_IN2);
         /*warning*/
         nBlinkers=3;
         palTogglePad(PORT_A, PA_LEDJAUNE1);
         palTogglePad(PORT_A, PA_LEDJAUNE2);

 		if (carMode>=4){
 			carMode-=4;
 		}else{
 			carMode+=4;
 		}
    }

    /* Event 3 - EIRQ3*/
    if (sr0 & (1 << 3)) {/*BTN JAUNE*/
      SIU.ISR.B.EIF3 = 1;
      pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 3000));

      pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 1500));

      pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 1000));

      /* Shutdown the motor */
      palClearPad(PORT_B, PIN_IN1);
      palClearPad(PORT_B, PIN_IN2);

      /*Marche Arriere*/

		palSetPad(PORT_B, PIN_IN1);
		palClearPad(PORT_B, PIN_IN2);
		pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 1000));
		//palTogglePad(PORT_C, PC_LEDROUGE);

		if (carMode>=8){
			carMode-=8;
		}else{
			carMode+=8;
		}
    }

    /* Event 1 - EIRQ4*/
    if (sr0 & (1 << 4)) {/*BTN NOIR*/
      SIU.ISR.B.EIF4 = 1;
      palTogglePad(PORT_C, PC_LEDROUGE);
      palTogglePad(PORT_B, PB_LEDBLANCHE);
      if (carMode>=1){
    	  carMode-=1;
      }else{
    	  carMode+=1;
      }
    }



  //===================================




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

