#include "parameters.h"
#include "satellite.h"
#include "devices.h"
#include <stdint.h>

struct parameters_memory_pool {

  uint16_t testing_2;
  uint32_t testing_4;

  uint32_t sensor_loop;

}mem_pool;

void init_parameters() {

  mem_pool.testing_2 = 0xCAFE;
  mem_pool.testing_4 = 0xDEADBEEF;

  mem_pool.sensor_loop = 100000;

}

void get_parameter(param_id pid, void* value, uint8_t *buf, uint16_t *size) {


  if(pid == testing_2_param_id) {
    *((uint16_t*)value) = mem_pool.testing_2;
    cnv16_8(mem_pool.testing_2, buf);
    *size = 2;
  } else if(pid == testing_4_param_id) {
    *((uint32_t*)value) = mem_pool.testing_4;
    cnv32_8(mem_pool.testing_4, buf);
    *size = 4;

  } else if(pid == SBSYS_sensor_loop_param_id) {
    *((uint32_t*)value) = mem_pool.sensor_loop;
    cnv32_8(mem_pool.sensor_loop, buf);
    *size = 4;

  } else if(pid == adb_int_temp_param_id) {

    struct tmp_device tmp_dev;

    read_device_parameters(ADB_INT_TEMP_DEV_ID, &tmp_dev);

    *((uint16_t*)value) = tmp_dev.raw_temp;
    cnv16_8(tmp_dev.raw_temp, buf);
    *size = 2;

  } else if(pid == adb_sensor_status_param_id) {

    bool status[16];
    uint16_t size2;

    read_device_status(status, &size2);

    buf[0] = 0;

    for(uint8_t i = 0; i < size2; i++) {
      buf[0] |= (status[i] << i);
    }

    *((uint8_t*)value) = buf[0];
    *size = 1;

  } else if(pid == adb_deb_param_id) {

    struct dep_device dev;

    read_device_parameters(ADB_DEP_DEV_ID, &dev);

    buf[0] = 0;
    buf[1] = 0;

    buf[1] = (dev.b1_status << 3) | \
             (dev.b2_status << 2) | \
             (dev.b3_status << 1) | \
              dev.b4_status;

    buf[0] = (dev.b1_enabled << 7) | \
             (dev.b2_enabled << 6) | \
             (dev.b3_enabled << 5) | \
             (dev.b4_enabled << 4) | \
             (dev.b1_state << 3) | \
             (dev.b2_state << 2) | \
             (dev.b3_state << 1) | \
              dev.b4_state;

    *((uint16_t*)value) = (buf[1] << 8) | buf[0];
    *size = 2;

  } else {
    *size = 0;
  }

}

uint8_t burn_sw_num;
uint8_t burn_feedback;
uint16_t burn_time;

bool set_parameter(param_id pid, void* value) {

  bool res = true;

  if(pid == adb_deb_param_id) {

    uint8_t *buf;
    buf = (uint8_t*)value;

    burn_sw_num = buf[0];
    burn_feedback = buf[1];

    cnv8_16LE(&buf[2], &burn_time);

    if(!C_ASSERT(burn_time > 0 && burn_time < 200) == true) {
      return false;
    }

    HAL_post_burn_event();

  } else if(pid == SBSYS_sensor_loop_param_id) {
    uint8_t *buf;
    buf = (uint8_t*)value;
    cnv8_32LE(&buf[0], &mem_pool.sensor_loop );

  } else if(pid == SBSYS_reset_clr_int_wdg_param_id) {

    struct int_wdg_device dev;
    read_device_parameters(INT_WDG_DEV_ID, &dev);
    dev.clr = true;
    write_device_parameters(INT_WDG_DEV_ID, &dev);

  } else if(pid == SBSYS_reset_cmd_int_wdg_param_id) {

    struct int_wdg_device dev;
    read_device_parameters(INT_WDG_DEV_ID, &dev);
    dev.cmd = true;
    write_device_parameters(INT_WDG_DEV_ID, &dev);

  } else if(pid == ft_param_id) {

        uint8_t *mem;
        uint32_t temp;

        uint8_t *buf;
        buf = (uint8_t*)value;
        cnv8_32LE(&buf[0], &temp);
        mem = temp;

        uint8_t operation = buf[4];
        uint8_t value = buf[5];

        if(operation == 0) {
           *mem = *mem & value;
        } else if(operation == 1) {
           *mem = *mem | value;
        } else if(operation == 2) {
           *mem = *mem ^ value;
        }

  } else {
    res = false;
  }

  return res;
}
