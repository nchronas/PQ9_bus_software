#include "hal_subsystem.h"

#include "packet_engine.h"
#include "satellite.h"
#include "PQ9_bus_engine.h"

#include <ti/drivers/SPI.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTMSP432.h>
#include <ti/drivers/utils/RingBuf.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCMSP432.h>
#include <ti/drivers/Watchdog.h>

#include "RED_board.h"

UART_Handle uart_pq9_bus;
UART_Handle uart_dbg_bus;
I2C_Handle i2c_brd;
SPI_Handle spi_fram;
Timer_Handle tim_pq9_bus_tx_en;
Watchdog_Handle intWatchdogHandle;

Timer_Handle tim_pq9_bus_rx_en;

void HAL_access_device_peripheral(dev_id id, void ** handle) {

  if(id == EPS_BUS_DEV_ID) {
    *handle = &uart_pq9_bus;
  } else if(id == EPS_DBG_DEV_ID) {
    //*handle = &uart_dbg_bus;
  }

}

HAL_access_device_peripheral_meta(dev_id id, void *value) {

}

void temp(UART_Handle handle, void *buf, size_t count) {

}

void watchdogCallback(uintptr_t unused)
{
    /* Clear watchdog interrupt flag */
    Watchdog_clear(intWatchdogHandle);

}

void test_tim_int(){
  GPIO_toggle(Board_GPIO_LED1);
}

void HAL_enable_PQ9_rx() {

  if(!C_ASSERT(Timer_start(tim_pq9_bus_rx_en) != Timer_STATUS_ERROR) == true) {
    usleep(1);
  }

}

void HAL_peripheral_open() {

  UART_Params uartParams;
  Timer_Params params;
  Watchdog_Params wdgparams;

  /* Create a UART with data processing off. */
//  UART_Params_init(&uartParams);
//  uartParams.writeMode = UART_MODE_BLOCKING;
//  uartParams.writeDataMode = UART_DATA_BINARY;
//  uartParams.readMode = UART_MODE_CALLBACK;
//  uartParams.readDataMode = UART_DATA_BINARY;
//  uartParams.readReturnMode = UART_RETURN_FULL;
//  uartParams.readEcho = UART_ECHO_OFF;
//  uartParams.baudRate = 115200;
//  uartParams.readCallback = &temp;
//
// // uart_pq9_bus = UART_open(DBG, &uartParams);
//
//  if(!C_ASSERT(uart_pq9_bus != NULL) == true) {
//    usleep(1);
//  }
//
//  //UARTMSP432_HWAttrsV1 const *hwAttrs = uart_pq9_bus->hwAttrs;
//  //UART_setDormant(hwAttrs->baseAddr);
//
//   UART_Params_init(&uartParams);
//   uartParams.writeMode = UART_MODE_BLOCKING;
//   uartParams.writeDataMode = UART_DATA_BINARY;
//   uartParams.readMode = UART_MODE_BLOCKING;
//   uartParams.readDataMode = UART_DATA_BINARY;
//   uartParams.readReturnMode = UART_RETURN_FULL;
//   uartParams.readEcho = UART_ECHO_OFF;
//   uartParams.baudRate = 115200;

  uartParams.writeMode = UART_MODE_BLOCKING;
  uartParams.writeDataMode = UART_DATA_BINARY;

  uartParams.readMode = UART_MODE_BLOCKING;
  uartParams.readDataMode = UART_DATA_BINARY;
  uartParams.readTimeout = 1;
  uartParams.readReturnMode = UART_RETURN_FULL;
  uartParams.readEcho = UART_ECHO_OFF;
  uartParams.baudRate = 115200;
   uart_dbg_bus = UART_open(DBG, &uartParams);

  Timer_Params_init(&params);
  params.periodUnits = Timer_PERIOD_US;
  params.period = 5000000;
  params.timerMode  = Timer_ONESHOT_CALLBACK;
  params.timerCallback = disable_PQ9_tx;
  tim_pq9_bus_tx_en = Timer_open(PQ9_TX_TIM, &params);

  if(!C_ASSERT(tim_pq9_bus_tx_en != NULL) == true) {
    usleep(1);
  }

  Timer_Params_init(&params);
  params.periodUnits = Timer_PERIOD_US;
  params.period = 10000000;
  params.timerMode  = Timer_CONTINUOUS_CALLBACK;
  params.timerCallback = test_tim_int; //enable_PQ9_tx;
  tim_pq9_bus_rx_en = Timer_open(PQ9_RX_TIM, &params);

  if(!C_ASSERT(tim_pq9_bus_rx_en != NULL) == true) {
    usleep(1);
  }

  Watchdog_Params_init(&wdgparams);
  wdgparams.resetMode = Watchdog_RESET_OFF;
  wdgparams.callbackFxn = (Watchdog_Callback) watchdogCallback;
  intWatchdogHandle = Watchdog_open(INTWATCHDOG, &wdgparams);
  if(!C_ASSERT(intWatchdogHandle != NULL) == true) {
    usleep(1);
  }

  HAL_enable_PQ9_rx();

}

void HAL_LED_ON() {
  GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_ON);
  GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_ON);

}

void HAL_LED_OFF() {
  GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_OFF);
  GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_OFF);
}

uint8_t HAL_S1() {
  return GPIO_read(MSP_EXP432P401R_GPIO_S1);
}

uint8_t HAL_S2() {
  return GPIO_read(MSP_EXP432P401R_GPIO_S2);
}
