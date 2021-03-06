#ifndef __DEVICES_H
#define __DEVICES_H

#include "satellite.h"
#include "stdint.h"

struct ina_device {
  dev_id id;
  float current;
  float voltage;
  float power;
  uint16_t voltage_raw;
  uint16_t current_raw;
  uint16_t power_raw;
  float shunt;
  float iMaxExpected;
  float currentLSB;
  float powerLSB;
};

struct tmp_device {
  dev_id id;
  float temp;
  int16_t raw_temp;
};

struct fram_device {
  dev_id id;
  uint16_t address;
  uint8_t *buffer;
  size_t count;
};

struct int_wdg_device {
  dev_id id;
  bool clr;
  bool cmd;
};

void device_init();

void update_device(const dev_id id);

void read_device_status(bool *status, uint16_t *size);

void read_device_parameters(dev_id id, void * data);

void write_device_parameters(dev_id id, void * data);

bool set_device_parameters(dev_id id, void * data);

#endif
