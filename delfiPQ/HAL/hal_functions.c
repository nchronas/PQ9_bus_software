#include "hal_functions.h"

#include "hal_subsystem.h"

#include "packet_engine.h"
#include "satellite.h"
#include "PQ9_bus_engine.h"

#include "subsystem.h"

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

extern UART_Handle uart_pq9_bus;
extern Timer_Handle tim_pq9_bus_tx_en;
extern Watchdog_Handle intWatchdogHandle;

void HAL_clear_int_wdg() {
  Watchdog_clear(intWatchdogHandle);
}

bool HAL_SPI_readWrite( dev_id id,
                        void *writeBuf,
                        size_t count,
                        void *readBuf) {

  SPI_Transaction spiTransaction;
  SPI_Handle *spi;
  Board_GPIOName *cs;
  bool res = false;

  HAL_access_device_peripheral(id, &spi);
  HAL_access_device_peripheral_meta(id, &cs);

  if(!C_ASSERT(*spi != NULL) == true) {
    return false;
  }

  char tx[3] = { 0xB0, 0x00, 0x50};

  spiTransaction.count = count;
  spiTransaction.txBuf = tx; //(void *)writeBuf;
  spiTransaction.rxBuf = (void *)readBuf;

//  GPIO_write(FRAM_CS, 0);
//  res = SPI_transfer(*spi, &spiTransaction);
//  GPIO_write(FRAM_CS, 1);

  GPIO_write(DPOT_CS, 0);
  res = SPI_transfer(*spi, &spiTransaction);
  GPIO_write(DPOT_CS, 1);

  if(!C_ASSERT(res == true) == true) {
    return false;
  }

  return true;
}

bool HAL_I2C_readWrite( dev_id id,
                        void *writeBuf,
                        size_t tx_count,
                        void *readBuf,
                        size_t rx_count) {

  I2C_Transaction i2cTransaction;
  I2C_Handle *i2c;
  uint8_t i2c_add = 0;
  bool res = false;

  HAL_access_device_peripheral(id, &i2c);
  HAL_access_device_peripheral_meta(id, &i2c_add);

  if(!C_ASSERT(*i2c != NULL) == true) {
    return false;
  }

  i2cTransaction.slaveAddress = i2c_add;
  i2cTransaction.writeBuf = writeBuf;
  i2cTransaction.writeCount = tx_count;
  i2cTransaction.readBuf = readBuf;
  i2cTransaction.readCount = rx_count;
  res = I2C_transfer((*i2c), &i2cTransaction);

  if(!C_ASSERT(res == true) == true) {
    return false;
  }

  return true;
}

extern uint8_t pq_rx_buf[300];
extern uint16_t pq_rx_count, pq_size;
extern bool pq_rx_flag;

bool HAL_uart_rx(dev_id id, uint8_t *buf, uint16_t *size) {

  if(pq_rx_flag) {

    pq_rx_flag = 0;

    memcpy(buf, pq_rx_buf, pq_rx_count);
    *size = pq_rx_count;
    return true;
  }

  return false;
}

void HAL_uart_tx(dev_id id, uint8_t *buf, uint16_t size) {

  if(!C_ASSERT(buf != NULL) == true) {
    return ;
  }

  UART_writePolling(uart_pq9_bus, buf, size);
}

void HAL_PQ9_BUS_enable_tx() {

  GPIO_write(PQ9_EN, 1);

  //if(!C_ASSERT(Timer_start(tim_pq9_bus_tx_en) != Timer_STATUS_ERROR) == true) {

  //}

}

void HAL_PQ9_BUS_disable_tx() {

  GPIO_write(PQ9_EN, 0);

  //Timer_stop(tim_pq9_bus_tx_en);

}

/*
 *  ======== Modified readIsrBinaryCallback ========
 *  1. Add to ti/drivers/uart/UARTMSP432.c this function
 *  2. add function readIsrModBinaryCallback definition in the .h
 *  3. Modify UARTMSP432.c, the staticFxnTable() and
 *     replace readIsrBinaryCallback with
 *     readIsrModBinaryCallback
    4. Add the other code
 *  5. Modify function UART_writePolling
 *  6. Modify function initHw
 *  7. Rebuild the using gmake eg /Applications/ti/xdctools_3_50_05_12_core/gmake
 */

 // Step 6 Find in the function the first and last loc and add the between them
 // static void initHw(UARTMSP432_Object *object,
 //    UARTMSP432_HWAttrsV1 const *hwAttrs, uint32_t inputClkFreq)
 //
 // uartConfig.numberofStopBits = stopBits[object->stopBits];
 //     if(hwAttrs->uartEUSCIMultiProcMode){
 //       uartConfig.uartMode = EUSCI_A_UART_ADDRESS_BIT_MULTI_PROCESSOR_MODE;
 //     } else {
 //       uartConfig.uartMode = EUSCI_A_UART_MODE;
 //     }
 //
 //     uartConfig.overSampling = hwAttrs->baudrateLUT[baudrateIndex].oversampling;

// Step 4 just copy that
// uint8_t pq_rx_buf[300];
// uint16_t pq_rx_count, pq_size;
// bool pq_rx_flag;
//
// extern uint8_t get_subs_addr();
//
// bool rx_pq9_bus(int readIn, uint_fast8_t addr) {
//
//   bool res = false;
//
//   uint8_t subs_addr = get_subs_addr();
//
//   if(addr && readIn == subs_addr) {
//       pq_rx_buf[0] = readIn;
//       pq_rx_count = 1;
//       res = true;
//     } else if(addr) {
//       pq_rx_count = 0;
//       res = false;
//     } else if(pq_rx_count == 1) {
//       pq_size = readIn;
//       pq_rx_buf[pq_rx_count] = readIn;
//       pq_rx_count++;
//       res = true;
//     } else if(pq_rx_count < pq_size + 5 - 1 && pq_rx_count != 0) {
//       pq_rx_buf[pq_rx_count] = readIn;
//       pq_rx_count++;
//       res = true;
//     } else if(pq_rx_count == pq_size + 5 -1 && pq_rx_count != 0) {
//       pq_rx_buf[pq_rx_count] = readIn;
//       pq_rx_count++;
//       pq_rx_flag = true;
//       res = false;
//     } else {
//       pq_rx_count = 0;
//       res = false;
//     }
//
//   return res;
// }
//
// bool UART_getDormant(uint32_t moduleInstance)
// {
//   uint16_t reg = EUSCI_A_CMSIS(moduleInstance)->CTLW0;
//   uint16_t mask = reg & EUSCI_A_CTLW0_DORM;
//   bool res = (mask == EUSCI_A_CTLW0_DORM);
//   return res;
// }
//
// #define PC_INTERFACE 1
//
// static bool readIsrModBinaryCallback(UART_Handle handle)
// {
//    int                         readIn;
//    bool                        ret = true;
//    UARTMSP432_Object          *object = handle->object;
//    UARTMSP432_HWAttrsV1 const *hwAttrs = handle->hwAttrs;
//
//    /*
//     * Here, we will do a quick check if another data byte has come in from
//     * when the RX interrupt was generated. This helps us avoid (not protect)
//     * data overruns by processing the next byte without having to wait for
//     * another RX interrupt ISR to kick in.
//     */
//    // bool add_res = UART_getDormant(hwAttrs->baseAddr);
//
//    bool addr = (UART_queryStatusFlags(hwAttrs->baseAddr, EUSCI_A_UART_ADDRESS_RECEIVED) == EUSCI_A_UART_ADDRESS_RECEIVED);
//
//    while (EUSCI_A_CMSIS(hwAttrs->baseAddr)->IFG & EUSCI_A_IFG_RXIFG) {
//        readIn = MAP_UART_receiveData(hwAttrs->baseAddr);
//
//
//
// //#ifdef PC_INTERFACE == 1
//        // UART_resetDormant(hwAttrs->baseAddr);
//        // if(addr) {
//        //    RingBuf_put(&object->ringBuffer, (unsigned char) 0x7e);
//        //    RingBuf_put(&object->ringBuffer, (unsigned char) readIn);
//        //  } else if(readIn == 0x7e) {
//        //    RingBuf_put(&object->ringBuffer, (unsigned char) 0x7d);
//        //    RingBuf_put(&object->ringBuffer, (unsigned char) 0x5e);
//        //  } else if(readIn == 0x7d) {
//        //    RingBuf_put(&object->ringBuffer, (unsigned char) 0x7d);
//        //    RingBuf_put(&object->ringBuffer, (unsigned char) 0x5d);
//        //  } else {
//        //   RingBuf_put(&object->ringBuffer, (unsigned char) readIn);
//        // }
// //#else
//      if(rx_pq9_bus(readIn, addr)) {
//        UART_resetDormant(hwAttrs->baseAddr);
//      } else {
//        UART_setDormant(hwAttrs->baseAddr);
//       }
// //#endif
//        addr = false;
//    }
//    DebugP_log2("UART:(%p) buffered '0x%02x'", hwAttrs->baseAddr,
//        (unsigned char) readIn);
//
//    return (ret);
// }


// Step 5 Replace that function.
// /*
//  *  ======== UARTMSP432_writePolling ========
//  */
// int_fast32_t UARTMSP432_writePolling(UART_Handle handle, const void *buf,
//         size_t size)
// {
//     uintptr_t                   key;
//     unsigned char *buffer = (unsigned char *) buf;
//     UARTMSP432_Object          *object = handle->object;
//     UARTMSP432_HWAttrsV1 const *hwAttrs = handle->hwAttrs;
//
//     if (!size) {
//         return (0);
//     }
//
//     key = HwiP_disable();
//
//     if (object->writeCount) {
//         HwiP_restore(key);
//         DebugP_log1("UART:(%p) Could not write data, uart in use.",
//             hwAttrs->baseAddr);
//
//         return (UART_ERROR);
//     }
//
//     /* Save the data to be written and restore interrupts. */
//     //object->writeBuf = &buf[1];
//     //object->writeSize = size - 1;
//     //object->writeCount = size - 1;
//
//     /*
//      * Set power constraint to keep peripheral active during transfer and
//      * to prevent a performance level change
//      */
// #if DeviceFamily_ID == DeviceFamily_ID_MSP432P401x
//     Power_setConstraint(PowerMSP432_DISALLOW_DEEPSLEEP_0);
// #endif
//     Power_setConstraint(PowerMSP432_DISALLOW_PERF_CHANGES);
//
//
//     /* Wait until the byte has gone out the wire. */
//     while (!MAP_UART_getInterruptStatus(hwAttrs->baseAddr,
//                    EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG));
//     /*
//      *  Atomically clear the TX complete flag so we don't wipe
//      *  out any incoming RX interrupts.
//      */
//     clearTXCPTIFG(hwAttrs->baseAddr);
//
//     //MAP_UART_transmitData(hwAttrs->baseAddr,  *buffer);
//     MAP_UART_transmitAddress(hwAttrs->baseAddr, *buffer);
//
//     /* Wait until the byte has gone out the wire. */
//     while (!MAP_UART_getInterruptStatus(hwAttrs->baseAddr,
//                    EUSCI_A_UART_TRANSMIT_COMPLETE_INTERRUPT_FLAG));
//
//                    size--;
//                    buffer++;
//
//     while(size) {
//       /* Wait until the byte has gone out the wire. */
//       while (!MAP_UART_getInterruptStatus(hwAttrs->baseAddr,
//                      EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG));
//       /*
//        *  Atomically clear the TX complete flag so we don't wipe
//        *  out any incoming RX interrupts.
//        */
//       clearTXCPTIFG(hwAttrs->baseAddr);
//
//       //MAP_UART_transmitData(hwAttrs->baseAddr,  *buffer);
//       MAP_UART_transmitData(hwAttrs->baseAddr, *buffer);
//
//       /* Wait until the byte has gone out the wire. */
//       while (!MAP_UART_getInterruptStatus(hwAttrs->baseAddr,
//                      EUSCI_A_UART_TRANSMIT_COMPLETE_INTERRUPT_FLAG));
//                      size--;
//                      buffer++;
//     }
//
//     return (0);
// }
