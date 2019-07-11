#ifndef __HAL_SUBSYSTEM_H
#define __HAL_SUBSYSTEM_H

#include <stdint.h>
#include <satellite.h>

void HAL_access_device_peripheral(dev_id id, void ** handle);

void HAL_access_device_peripheral_meta(dev_id id, void *value);

void HAL_peripheral_open();

void HAL_LED_ON();

void HAL_LED_OFF();

uint8_t HAL_S1();
uint8_t HAL_S2();

#endif
