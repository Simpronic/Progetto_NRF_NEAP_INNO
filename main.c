/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

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

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "rf.h"
#include "defines.h"
#include "string.h"

BaseSequentialStream * chp = (BaseSequentialStream *) &SD2;
/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();
  palSetPadMode( GPIOA, 2, PAL_MODE_ALTERNATE(7) );
  palSetPadMode( GPIOA, 3, PAL_MODE_ALTERNATE(7) );

  /*
   * Activates the Serial or SIO driver using the default configuration.
   */
    palSetLineMode(NRF_SCK_LINE,  PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(NRF_MISO_LINE, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(NRF_MOSI_LINE, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(NRF_SPI_CS, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);

    palSetLineMode(NRF_CE_LINE, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(NRF_IRQ_LINE, PAL_MODE_INPUT | PAL_STM32_OSPEED_HIGHEST);


//chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  rf_msg_t msg;
  char msg_to_send[6];
  strcpy(msg_to_send,MSG);
  sdStart( &SD2, NULL);
  //rfInit();
  //rfStart(&RFD1,&nrf24l01_cfg);
  while (true) {
    if (palReadLine(LINE_BUTTON)) {
          chprintf(chp,"Bottone cliccato \n\r");
          palToggleLine(LINE_LED_GREEN);
          /*msg = rfTransmitString(&RFD1,msg_to_send,"TavB5",TIME_INFINITE);
          if(msg == RF_OK){
            chprintf(chp,"MESSAGGIO INVIATO");
          }else{
            chprintf(chp,"ERRORE NELL'INVIO");
          }*/
       }
       chThdSleepMilliseconds(500);
  }
  sdStop(&SD2);
  //rfStop(&RFD1);
}

