//*****************************************************************************
// Board.c
//
// configure the device pins for different signals
//
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

// This file was automatically generated on 23/07/2018 at 11:00:30
// by TI PinMux version 4.0.1525
//
//*****************************************************************************

#include <stdbool.h>

#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerMSP432.h>

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/rom.h>
#include <ti/devices/msp432p4xx/driverlib/rom_map.h>
#include <ti/devices/msp432p4xx/driverlib/adc14.h>
#include <ti/devices/msp432p4xx/driverlib/dma.h>
#include <ti/devices/msp432p4xx/driverlib/gpio.h>
#include <ti/devices/msp432p4xx/driverlib/i2c.h>
#include <ti/devices/msp432p4xx/driverlib/interrupt.h>
#include <ti/devices/msp432p4xx/driverlib/pmap.h>
#include <ti/devices/msp432p4xx/driverlib/ref_a.h>
#include <ti/devices/msp432p4xx/driverlib/spi.h>
#include <ti/devices/msp432p4xx/driverlib/timer_a.h>
#include <ti/devices/msp432p4xx/driverlib/timer32.h>
#include <ti/devices/msp432p4xx/driverlib/uart.h>
#include <ti/devices/msp432p4xx/driverlib/wdt_a.h>

#include "COMMS_Board.h"

/*
 *  =============================== ADC ===============================
 */
#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCMSP432.h>

/* ADC objects */
ADCMSP432_Object adcMSP432Objects[Board_ADCCOUNT];

/* ADC configuration structure */
const ADCMSP432_HWAttrsV1 adcMSP432HWAttrs[Board_ADCCOUNT] = {
    {
        .adcPin = ADCMSP432_P4_5_A8,
        .refVoltage = REF_A_VREF2_5V,
        .resolution = ADC_14BIT,
    },
    {
        .adcPin = ADCMSP432_P4_6_A7,
        .refVoltage = REF_A_VREF2_5V,
        .resolution = ADC_14BIT,
    },
    {
        .adcPin = ADCMSP432_P4_7_A6,
        .refVoltage = REF_A_VREF2_5V,
        .resolution = ADC_14BIT,
    },
    {
        .adcPin = ADCMSP432_P5_0_A5,
        .refVoltage = REF_A_VREF2_5V,
        .resolution = ADC_14BIT,
    },
    {
        .adcPin = ADCMSP432_P5_1_A4,
        .refVoltage = REF_A_VREF2_5V,
        .resolution = ADC_14BIT,
    },
    {
        .adcPin = ADCMSP432_P5_2_A3,
        .refVoltage = REF_A_VREF2_5V,
        .resolution = ADC_14BIT,
    },
    {
        .adcPin = ADCMSP432_P5_3_A2,
        .refVoltage = REF_A_VREF2_5V,
        .resolution = ADC_14BIT,
    },
    {
        .adcPin = ADCMSP432_P5_4_A1,
        .refVoltage = REF_A_VREF2_5V,
        .resolution = ADC_14BIT,
    },
    {
        .adcPin = ADCMSP432_P5_5_A0,
        .refVoltage = REF_A_VREF2_5V,
        .resolution = ADC_14BIT,
    },
};

const ADC_Config ADC_config[Board_ADCCOUNT] = {
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[comms_p9_rf_rx_voltage],
        .hwAttrs = &adcMSP432HWAttrs[comms_p9_rf_rx_voltage]
    },
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[comms_p8_rf_tx_voltage],
        .hwAttrs = &adcMSP432HWAttrs[comms_p8_rf_tx_voltage]
    },
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[comms_p7_nc],
        .hwAttrs = &adcMSP432HWAttrs[comms_p7_nc]
    },
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[comms_p6_pq_voltage],
        .hwAttrs = &adcMSP432HWAttrs[comms_p6_pq_voltage]
    },
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[comms_p5_msp_voltage],
        .hwAttrs = &adcMSP432HWAttrs[comms_p5_msp_voltage]
    },
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[comms_p4_prot_voltage],
        .hwAttrs = &adcMSP432HWAttrs[comms_p4_prot_voltage]
    },
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[comms_p3_3v3],
        .hwAttrs = &adcMSP432HWAttrs[comms_p3_3v3]
    },
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[comms_p2_vbus],
        .hwAttrs = &adcMSP432HWAttrs[comms_p2_vbus]
    },
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[comms_p1_supply_current],
        .hwAttrs = &adcMSP432HWAttrs[comms_p1_supply_current]
    },
};

const uint_least8_t ADC_count = Board_ADCCOUNT;

/*
 *  =============================== DMA ===============================
 */
#include <ti/drivers/dma/UDMAMSP432.h>

#if defined(__TI_COMPILER_VERSION__)
#pragma DATA_ALIGN(dmaControlTable, 256)
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=256
#elif defined(__GNUC__)
__attribute__ ((aligned (256)))
#endif
static DMA_ControlTable dmaControlTable[8];

/*
 *  ======== dmaErrorHwi ========
 *  This is the handler for the uDMA error interrupt.
 */
static void dmaErrorHwi(uintptr_t arg)
{
    int status = MAP_DMA_getErrorStatus();
    MAP_DMA_clearErrorStatus();

    /* Suppress unused variable warning */
    (void)status;

    while (1);
}

UDMAMSP432_Object udmaMSP432Object;

const UDMAMSP432_HWAttrs udmaMSP432HWAttrs = {
    .controlBaseAddr = (void *)dmaControlTable,
    .dmaErrorFxn = (UDMAMSP432_ErrorFxn)dmaErrorHwi,
    .intNum = INT_DMA_ERR,
    .intPriority = (~0)
};

const UDMAMSP432_Config UDMAMSP432_config = {
    .object = &udmaMSP432Object,
    .hwAttrs = &udmaMSP432HWAttrs
};


/*
 *  ======== MSP_EXP432P401R_initGeneral ========
 */
void MSP_EXP432P401R_initGeneral(void)
{
    Power_init();
}

/*
 *  =============================== GPIO ===============================
 */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOMSP432.h>

/*
 * Array of Pin configurations
 * NOTE: The order of the pin configurations must coincide with what was
 *       defined in MSP_EXP432P401R.h
 * NOTE: Pins not used for interrupts should be placed at the end of the
 *       array.  Callback entries can be omitted from callbacks array to
 *       reduce memory usage.
 */
GPIO_PinConfig gpioPinConfigs[] = {
    GPIOMSP432_P9_0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_LOW | GPIO_CFG_OUT_HIGH,
    GPIOMSP432_P10_4 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_LOW | GPIO_CFG_OUT_HIGH,
    GPIOMSP432_P10_5 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_LOW | GPIO_CFG_OUT_HIGH,
    //GPIOMSP432_P2_0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_LOW | GPIO_CFG_OUT_HIGH,
    GPIOMSP432_P2_0 | GPIO_CFG_IN_NOPULL,

};

/*
 * Array of callback function pointers
 * NOTE: The order of the pin configurations must coincide with what was
 *       defined in MSP_EXP432P401R.h
 * NOTE: Pins not used for interrupts can be omitted from callbacks array to
 *       reduce memory usage (if placed at end of gpioPinConfigs array).
 */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    NULL,
    NULL
};

const GPIOMSP432_Config GPIOMSP432_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .numberOfPinConfigs = sizeof(gpioPinConfigs)/sizeof(GPIO_PinConfig),
    .numberOfCallbacks = sizeof(gpioCallbackFunctions)/sizeof(GPIO_CallbackFxn),
    .intPriority = (~0)
};
/*
 *  =============================== I2C ===============================
 */
#include <ti/drivers/I2C.h>
#include <ti/drivers/i2c/I2CMSP432.h>

I2CMSP432_Object i2cMSP432Objects[Board_I2CCOUNT];

const I2CMSP432_HWAttrsV1 i2cMSP432HWAttrs[Board_I2CCOUNT] = {
    {
        .baseAddr = EUSCI_B0_BASE,
        .intNum = INT_EUSCIB0,
        .intPriority = (~0),
        .clockSource = EUSCI_B_I2C_CLOCKSOURCE_SMCLK,
        .dataPin = I2CMSP432_P1_6_UCB0SDA,
        .clkPin = I2CMSP432_P1_7_UCB0SCL,
    },
};

const I2C_Config I2C_config[Board_I2CCOUNT] = {
    {
        .fxnTablePtr = &I2CMSP432_fxnTable,
        .object = &i2cMSP432Objects[COMMS_BRD],
        .hwAttrs = &i2cMSP432HWAttrs[COMMS_BRD]
    },
};

const uint_least8_t I2C_count = Board_I2CCOUNT;
/*
 *  =============================== Power ===============================
 */
const PowerMSP432_ConfigV1 PowerMSP432_config = {
    .policyInitFxn = &PowerMSP432_initPolicy,
    .policyFxn = &PowerMSP432_sleepPolicy,
    .initialPerfLevel = 2,
    .enablePolicy = true,
    .enablePerf = true,
    .enableParking = true
};

/*
 *  =============================== SPI ===============================
 */
#include <ti/drivers/SPI.h>
#include <ti/drivers/spi/SPIMSP432DMA.h>

/* SPI objects */
SPIMSP432DMA_Object spiMSP432DMAObjects[Board_SPICOUNT];

/* SPI configuration structure */
const SPIMSP432DMA_HWAttrsV1 spiMSP432DMAHWAttrs[Board_SPICOUNT] = {
    {
        .baseAddr = EUSCI_B3_BASE,
        .bitOrder = EUSCI_B_SPI_MSB_FIRST,
        .clockSource = EUSCI_B_SPI_CLOCKSOURCE_SMCLK,
        .defaultTxBufValue = 0,
        .dmaIntNum = INT_DMA_INT1,
        .intPriority = (~0),
        .rxDMAChannelIndex = DMA_CH7_EUSCIB3RX0,
        .txDMAChannelIndex = DMA_CH6_EUSCIB3TX0,
        .clkPin = SPIMSP432DMA_P10_1_UCB3CLK,
        .simoPin = SPIMSP432DMA_P10_2_UCB3SIMO,
        .somiPin = SPIMSP432DMA_P10_3_UCB3SOMI,
        //.stePin = SPIMSP432DMA_P__,
        .pinMode = EUSCI_SPI_3PIN
    },
    {
        .baseAddr = EUSCI_B1_BASE,
        .bitOrder = EUSCI_B_SPI_MSB_FIRST,
        .clockSource = EUSCI_B_SPI_CLOCKSOURCE_SMCLK,
        .defaultTxBufValue = 0,
        .dmaIntNum = INT_DMA_INT2,
        .intPriority = (~0),
        .rxDMAChannelIndex = DMA_CH3_EUSCIB1RX0,
        .txDMAChannelIndex = DMA_CH2_EUSCIB1TX0,
        .clkPin = SPIMSP432DMA_P6_3_UCB1CLK,
        .simoPin = SPIMSP432DMA_P6_4_UCB1SIMO,
        .somiPin = SPIMSP432DMA_P6_5_UCB1SOMI,
        //.stePin = SPIMSP432DMA_P__,
        .pinMode = EUSCI_SPI_3PIN
    },
    {
        .baseAddr = EUSCI_A1_BASE,
        .bitOrder = EUSCI_A_SPI_MSB_FIRST,
        .clockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK,
        .defaultTxBufValue = 0,
        .dmaIntNum = INT_DMA_INT3,
        .intPriority = (~0),
        .rxDMAChannelIndex = DMA_CH3_EUSCIA1RX,
        .txDMAChannelIndex = DMA_CH2_EUSCIA1TX,
        .clkPin = SPIMSP432DMA_P3_5_UCA1CLK,
        .simoPin = SPIMSP432DMA_P3_6_UCA1SIMO,
        .somiPin = SPIMSP432DMA_P3_7_UCA1SOMI,
        //.stePin = SPIMSP432DMA_P__,
        .pinMode = EUSCI_SPI_3PIN
    },
};

const SPI_Config SPI_config[Board_SPICOUNT] = {
    {
        .fxnTablePtr = &SPIMSP432DMA_fxnTable,
        .object = &spiMSP432DMAObjects[RF_CTRL],
        .hwAttrs = &spiMSP432DMAHWAttrs[RF_CTRL]
    },
    {
        .fxnTablePtr = &SPIMSP432DMA_fxnTable,
        .object = &spiMSP432DMAObjects[RF_TX],
        .hwAttrs = &spiMSP432DMAHWAttrs[RF_TX]
    },
    {
        .fxnTablePtr = &SPIMSP432DMA_fxnTable,
        .object = &spiMSP432DMAObjects[RF_RX],
        .hwAttrs = &spiMSP432DMAHWAttrs[RF_RX]
    },
};

const uint_least8_t SPI_count = Board_SPICOUNT;
/*
 *  =============================== Timer ===============================
 */
#include <ti/drivers/Timer.h>
#include <ti/drivers/timer/TimerMSP432.h>

TimerMSP432_Object timerMSP432Objects[Board_TIMERCOUNT];

const TimerMSP432_HWAttrs timerMSP432HWAttrs[Board_TIMERCOUNT] = {
    {
        .timerBaseAddress = TIMER_A0_BASE,
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .intNum = INT_TA0_0,
        .intPriority = ~0
    },
};

const Timer_Config Timer_config[Board_TIMERCOUNT] = {
    {
        .fxnTablePtr = &TimerMSP432_Timer_A_fxnTable,
        .object = &timerMSP432Objects[PQ9_TX_TIM],
        .hwAttrs = &timerMSP432HWAttrs[PQ9_TX_TIM]
    },
};

const uint_least8_t Timer_count = Board_TIMERCOUNT;

/*
 *  =============================== UART ===============================
 */
#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTMSP432.h>

UARTMSP432_Object uartMSP432Objects[Board_UARTCOUNT];
unsigned char uartMSP432RingBuffer[Board_UARTCOUNT][32];

/*
 * The baudrate dividers were determined by using the MSP432 baudrate
 * calculator
 * http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 */
const UARTMSP432_BaudrateConfig uartMSP432Baudrates[] = {
    /* {baudrate, input clock, prescalar, UCBRFx, UCBRSx, oversampling} */
    {
        .outputBaudrate = 115200,
        .inputClockFreq = 12000000,
        .prescalar = 6,
        .hwRegUCBRFx = 8,
        .hwRegUCBRSx = 32,
        .oversampling = 1
    },
    {500000, 12000000,  1,  8,   0, 1},
    {460800, 12000000,  1,  10,  0, 1},
    {115200, 6000000,   3,  4,   2, 1},
    {115200, 3000000,   1, 10,   0, 1},
    {9600,   12000000, 78,  2,   0, 1},
    {9600,   6000000,  39,  1,   0, 1},
    {9600,   3000000,  19,  8,  85, 1},
    {9600,   32768,     3,  0, 146, 0}
};

const UARTMSP432_HWAttrsV1 uartMSP432HWAttrs[Board_UARTCOUNT] = {
    {
        .baseAddr = EUSCI_A3_BASE,
        .intNum = INT_EUSCIA3,
        .intPriority = (~0),
        .clockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK,
        .bitOrder = EUSCI_A_UART_LSB_FIRST,
        .numBaudrateEntries = sizeof(uartMSP432Baudrates) /
            sizeof(UARTMSP432_BaudrateConfig),
        .baudrateLUT = uartMSP432Baudrates,
        .ringBufPtr  = uartMSP432RingBuffer[PQ9],
        .ringBufSize = sizeof(uartMSP432RingBuffer[PQ9]),
        .rxPin = UARTMSP432_P9_6_UCA3RXD,
        .txPin = UARTMSP432_P9_7_UCA3TXD,
        .uartEUSCIMultiProcMode = true,
    },
    {
        .baseAddr = EUSCI_A0_BASE,
        .intNum = INT_EUSCIA0,
        .intPriority = (~0),
        .clockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK,
        .bitOrder = EUSCI_A_UART_LSB_FIRST,
        .numBaudrateEntries = sizeof(uartMSP432Baudrates) /
            sizeof(UARTMSP432_BaudrateConfig),
        .baudrateLUT = uartMSP432Baudrates,
        .ringBufPtr  = uartMSP432RingBuffer[DBG],
        .ringBufSize = sizeof(uartMSP432RingBuffer[DBG]),
        .rxPin = UARTMSP432_P1_2_UCA0RXD,
        .txPin = UARTMSP432_P1_3_UCA0TXD,
    },
};

const UART_Config UART_config[Board_UARTCOUNT] = {
    {
        .fxnTablePtr = &UARTMSP432_fxnTable,
        .object = &uartMSP432Objects[PQ9],
        .hwAttrs = &uartMSP432HWAttrs[PQ9]
    },
    {
        .fxnTablePtr = &UARTMSP432_fxnTable,
        .object = &uartMSP432Objects[DBG],
        .hwAttrs = &uartMSP432HWAttrs[DBG]
    },
};

const uint_least8_t UART_count = Board_UARTCOUNT;

/*
 *  =============================== Watchdog ===============================
 */
#include <ti/drivers/Watchdog.h>
#include <ti/drivers/watchdog/WatchdogMSP432.h>

WatchdogMSP432_Object watchdogMSP432Objects[Board_WATCHDOGCOUNT];

const WatchdogMSP432_HWAttrs watchdogMSP432HWAttrs[Board_WATCHDOGCOUNT] = {
    {
        .baseAddr = WDT_A_BASE,
        .intNum = INT_WDT_A,
        .intPriority = (~0),
        .clockSource = WDT_A_CLOCKSOURCE_SMCLK,
        .clockDivider = WDT_A_CLOCKDIVIDER_128M
    },
};

const Watchdog_Config Watchdog_config[Board_WATCHDOGCOUNT] = {
    {
        .fxnTablePtr = &WatchdogMSP432_fxnTable,
        .object = &watchdogMSP432Objects[INTWATCHDOG],
        .hwAttrs = &watchdogMSP432HWAttrs[INTWATCHDOG]
    },
};

const uint_least8_t Watchdog_count = Board_WATCHDOGCOUNT;
