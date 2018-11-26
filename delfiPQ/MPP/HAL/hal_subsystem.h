#ifndef __HAL_SUBSYSTEM_H
#define __HAL_SUBSYSTEM_H

#include <stdint.h>
#include <satellite.h>

void HAL_access_device_peripheral(dev_id id, void ** handle);

void HAL_access_device_peripheral_meta(dev_id id, void *value);

void HAL_peripheral_open();

bool HAL_internal_temp(int16_t *val);
#endif
