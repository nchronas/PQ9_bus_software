#include "hal_subsystem.h"

#include "packet_engine.h"
#include "satellite.h"
#include "PQ9_bus_engine.h"
#include "devices.h"

#include <ti/drivers/SPI.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTMSP432.h>
#include <ti/drivers/utils/RingBuf.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOMSP432.h>
#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCMSP432.h>
#include <ti/drivers/Watchdog.h>

#include "COMMS_board.h"

UART_Handle uart_pq9_bus;
UART_Handle uart_dbg_bus;
I2C_Handle i2c_brd;
SPI_Handle spi_rf_rx;
SPI_Handle spi_rf_tx;
SPI_Handle spi_rf_ctrl;
Timer_Handle tim_pq9_bus_tx_en;
ADC_Handle adc_comms_properties[MAX_ADC_DEVS];
Watchdog_Handle intWatchdogHandle;

void HAL_access_device_peripheral(dev_id id, void ** handle) {

  if(id == EPS_BUS_DEV_ID) {
    *handle = &uart_pq9_bus;
  } else if(id == EPS_DBG_DEV_ID) {
    //*handle = &uart_dbg_bus;
  } else if(id == COMMS_TEMP_DEV_ID) {
    *handle = &i2c_brd;
  } else if(id == COMMS_RF_TX_DEV_ID) {
    *handle = &spi_rf_tx;
  } else if(id == COMMS_RF_RX_DEV_ID) {
    *handle = &spi_rf_rx;
  } else if(id == COMMS_RF_CTRL_DEV_ID) {
    *handle = &spi_rf_ctrl;
  }

}

HAL_access_device_peripheral_meta(dev_id id, void *value) {
  if(id == COMMS_TEMP_DEV_ID) {
    *(uint8_t*)value = 0x4F;
  } else if(id == COMMS_RF_TX_DEV_ID) {
    *(Board_GPIOName*)value = RF_TX_CS;
  } else if(id == COMMS_RF_RX_DEV_ID) {
    *(Board_GPIOName*)value = RF_RX_CS;
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
  i2c_brd = I2C_open(COMMS_BRD, &i2cParams);

  if(!C_ASSERT(i2c_brd != NULL) == true) {
    usleep(1);
  }

  /* Initialize SPI handle as default master */
  SPI_Params_init(&spiParams);
  spiParams.frameFormat = SPI_POL0_PHA0;
  spiParams.bitRate = 100000;
  spi_rf_ctrl = SPI_open(RF_CTRL, &spiParams);
  spi_rf_tx = SPI_open(RF_TX, &spiParams);
  spi_rf_rx = SPI_open(RF_RX, &spiParams);

  if(!C_ASSERT(spi_rf_ctrl != NULL) == true) {
    usleep(1);
  }
  if(!C_ASSERT(spi_rf_tx != NULL) == true) {
    usleep(1);
  }
  if(!C_ASSERT(spi_rf_rx != NULL) == true) {
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

  for(uint8_t i=0; i < Board_ADCCOUNT; i++) {
    adc_comms_properties[i] = ADC_open(i, &adcParams);
    if(!C_ASSERT(adc_comms_properties[i] != NULL) == true) {
      usleep(1);
    }
  }

  Watchdog_Params_init(&wdgparams);
  wdgparams.resetMode = Watchdog_RESET_OFF;
  wdgparams.callbackFxn = (Watchdog_Callback) watchdogCallback;
  intWatchdogHandle = Watchdog_open(INTWATCHDOG, &wdgparams);
  if(!C_ASSERT(intWatchdogHandle != NULL) == true) {
    usleep(1);
  }
}

bool HAL_adc_reading(uint8_t id, uint16_t *val) {
  int_fast16_t res;

  res = ADC_convert(adc_comms_properties[id], (uint_fast16_t*)val);
  if (res == ADC_STATUS_SUCCESS) {
    return true;
  }
  return false;
}

extern GPIO_PinConfig gpioPinConfigs[];

void HAL_PQ9_RST() {

 // GPIO_PinConfig gpioPinConfigs[] = { GPIOMSP432_P2_0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_LOW | GPIO_CFG_OUT_HIGH };

  GPIO_PinConfig gpioPinConfigs[PQ9_RST] = { GPIOMSP432_P2_0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_LOW | GPIO_CFG_OUT_HIGH };


  GPIO_setConfig(PQ9_RST, gpioPinConfigs);
  usleep(10);
  GPIO_write(PQ9_RST, 0);
}
