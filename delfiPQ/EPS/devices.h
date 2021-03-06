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

struct ltc_device {
  dev_id id;
  int16_t raw_temp;
  uint16_t raw_cap;
  uint16_t raw_volt;
};

struct fram_device {
  dev_id id;
  uint16_t address;
  uint8_t *buffer;
  size_t count;
};

struct powerline_device {
  dev_id id;
  bool b1_enabled;
  bool b2_enabled;
  bool b3_enabled;
  bool b4_enabled;

  bool b1_state;
  bool b2_state;
  bool b3_state;
  bool b4_state;
};

struct int_wdg_device {
  dev_id id;
  bool clr;
  bool cmd;
};

void device_init();

void update_device(dev_id id);

void read_device_status(bool *status, uint16_t *size);

void read_device_parameters(dev_id id, void * data);

void write_device_parameters(dev_id id, void * data);

bool set_device_parameters(dev_id id, void * data);

void get_device_parameters(dev_id id, void * data);

bool ina_averaging(struct ina_average *ina_av,
                   int16_t current,
                   int16_t *new_value);

#endif
