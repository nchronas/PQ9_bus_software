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

#include "MPP_Board.h"

UART_Handle uart_pq9_bus;
UART_Handle uart_dbg_bus;
I2C_Handle i2c_brd;
SPI_Handle spi_fram;
SPI_Handle spi_dpot;
Timer_Handle tim_pq9_bus_tx_en;
ADC_Handle adc_lpm_sen;
Watchdog_Handle intWatchdogHandle;

void HAL_access_device_peripheral(dev_id id, void ** handle) {

 if(id == MPP_BOARD_MON_DEV_ID ||
    id == MPP_HOLD_MON_DEV_ID ||
    id == MPP_SPIKE_MON_DEV_ID ||
    id == MPP_HEATER_MON_DEV_ID ||
    id == MPP_TEMP_DEV_ID) {
    *handle = &i2c_brd;
  // } else if(id == MPP_FRAM_DEV_ID) {
  //   *handle = &spi_fram;
  } else if(id == MPP_DPOT_DEV_ID) {
    *handle = &spi_dpot;
  }

}

HAL_access_device_peripheral_meta(dev_id id, void *value) {

  if(id == MPP_BOARD_MON_DEV_ID) {
    *(uint8_t*)value = 0x40;
  } else if(id == MPP_HOLD_MON_DEV_ID) {
    *(uint8_t*)value = 0x41;
  } else if(id == MPP_SPIKE_MON_DEV_ID) {
    *(uint8_t*)value = 0x42;
  } else if(id == MPP_HEATER_MON_DEV_ID) {
    *(uint8_t*)value = 0x43;
  } else if(id == MPP_TEMP_DEV_ID) {
    *(uint8_t*)value = 0x48;
  } else if(id == MPP_FRAM_DEV_ID) {
    *(Board_GPIOName*)value = FRAM_CS;
  } else if(id == MPP_DPOT_DEV_ID) {
    *(Board_GPIOName*)value = DPOT_CS;
  }

}

void temp(UART_Handle handle, void *buf, size_t count) {

}

void watchdogCallback(uintptr_t unused)
{
    /* Clear watchdog interrupt flag */
    Watchdog_clear(intWatchdogHandle);

}

void HAL_peripheral_open() {

  I2C_Params  i2cParams;
  UART_Params uartParams;
  SPI_Params spiParams;
  Timer_Params params;
  ADC_Params adcParams;
  Watchdog_Params wdgparams;

  /* Create a UART with data processing off. */
  UART_Params_init(&uartParams);
  uartParams.writeMode = UART_MODE_BLOCKING;
  uartParams.writeDataMode = UART_DATA_BINARY;
  uartParams.readMode = UART_MODE_CALLBACK;
  uartParams.readDataMode = UART_DATA_BINARY;
  uartParams.readReturnMode = UART_RETURN_FULL;
  uartParams.readEcho = UART_ECHO_OFF;
  uartParams.baudRate = 115200; //500000;
  uartParams.readCallback = &temp;
  uart_pq9_bus = UART_open(PQ9, &uartParams);

  if(!C_ASSERT(uart_pq9_bus != NULL) == true) {
    usleep(1);
  }

  UARTMSP432_HWAttrsV1 const *hwAttrs = uart_pq9_bus->hwAttrs;
  UART_setDormant(hwAttrs->baseAddr);

  UART_Params_init(&uartParams);
  uartParams.writeMode = UART_MODE_BLOCKING;
  uartParams.writeDataMode = UART_DATA_BINARY;
  uartParams.readMode = UART_MODE_BLOCKING;
  uartParams.readDataMode = UART_DATA_BINARY;
  uartParams.readReturnMode = UART_RETURN_FULL;
  uartParams.readEcho = UART_ECHO_ON;
  uartParams.baudRate = 115200;
  uart_dbg_bus = UART_open(DBG, &uartParams);

  I2C_Params_init(&i2cParams);
  i2cParams.transferMode = I2C_MODE_BLOCKING;
  i2cParams.bitRate = I2C_100kHz;
  i2c_brd = I2C_open(I2C_MON, &i2cParams);

  if(!C_ASSERT(i2c_brd != NULL) == true) {
    usleep(1);
  }

  /* Initialize SPI handle as default master */
  // SPI_Params_init(&spiParams);
  // spiParams.frameFormat = SPI_POL0_PHA0;
  // spiParams.bitRate = 1000;
  // spi_fram = SPI_open(FRAM, &spiParams);
  //
  // if(!C_ASSERT(spi_fram != NULL) == true) {
  //   usleep(1);
  // }

  SPI_Params_init(&spiParams);
  spiParams.frameFormat = SPI_POL0_PHA0;
  spiParams.bitRate = 10000;
  spi_dpot = SPI_open(DPOT, &spiParams);

  if(!C_ASSERT(spi_dpot != NULL) == true) {
    usleep(1);
  }

  Timer_Params_init(&params);
  params.periodUnits = Timer_PERIOD_US;
  params.period = 5000000;
  params.timerMode  = Timer_ONESHOT_CALLBACK;
  params.timerCallback = disable_PQ9_tx;
  tim_pq9_bus_tx_en = Timer_open(PQ9_TX_TIM, &params);

  if(!C_ASSERT(tim_pq9_bus_tx_en != NULL) == true) {
    usleep(1);
  }

  /* Set up an ADC peripheral in ADCBuf_RECURRENCE_MODE_CONTINUOUS */
  ADC_Params_init(&adcParams);
  adc_lpm_sen = ADC_open(EXT_LPM_SEN19, &adcParams);

  if(!C_ASSERT(adc_lpm_sen != NULL) == true) {
    usleep(1);
  }

  /* Set up an ADC peripheral in ADCBuf_RECURRENCE_MODE_CONTINUOUS */
  // ADC_Params_init(&adcParams);
  // adc_internal_temp = ADC_open(ADC_INTERNAL_TEMP0, &adcParams);

  // if(!C_ASSERT(adc_internal_temp != NULL) == true) {
  //   usleep(1);
  // }

  Watchdog_Params_init(&wdgparams);
  wdgparams.resetMode = Watchdog_RESET_OFF;
  wdgparams.callbackFxn = (Watchdog_Callback) watchdogCallback;
  intWatchdogHandle = Watchdog_open(INTWATCHDOG, &wdgparams);
  if(!C_ASSERT(intWatchdogHandle != NULL) == true) {
    usleep(1);
  }

}

bool HAL_lpm_sen(int16_t *val) {
  int_fast16_t res;
  uint16_t conv;

  res = ADC_convert(adc_lpm_sen, &conv);
  *val = conv;

  if (res == ADC_STATUS_SUCCESS) {
    return true;
  }
  return false;
}

void HAL_lpm_heat(uint8_t val) {
  GPIO_write( LPM_HEAT, val);
}

void HAL_vlm_heat(uint8_t val) {
  GPIO_write( VLM_HEAT, val);
}

void HAL_lpm_spike(uint8_t val) {
  GPIO_write( LPM_VALVE_SPIKE, val);
}

void HAL_vlm_spike(uint8_t val) {
  GPIO_write( VLM_VALVE_SPIKE, val);
}

void HAL_lpm_hold(uint8_t val) {
  GPIO_write( LPM_VALVE_HOLD, val);
}

void HAL_vlm_hold(uint8_t val) {
  GPIO_write( VLM_VALVE_HOLD, val);
}
