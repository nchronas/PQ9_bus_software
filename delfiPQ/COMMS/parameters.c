#include "parameters.h"
#include "satellite.h"
#include "devices.h"
#include "packet_utilities.h"
#include <stdint.h>


struct parameters_memory_pool {

  uint16_t testing_2;
  uint32_t testing_4;
  uint32_t testing_4_rw;

  uint32_t sensor_loop;

}mem_pool;

void init_parameters() {

  mem_pool.testing_2 = 0xCAFE;
  mem_pool.testing_4 = 0xDEADBEEF;

  mem_pool.testing_4_rw = 0xDEADBEEF;

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

  } else if(pid == eps_testing_4_rw_param_id) {

    *((uint32_t*)value) = mem_pool.testing_4_rw;
    cnv32_8(mem_pool.testing_4_rw, buf);
    *size = 4;

  } else if(pid == SBSYS_sensor_loop_param_id) {
    *((uint32_t*)value) = mem_pool.sensor_loop;
    cnv32_8(mem_pool.sensor_loop, buf);
    *size = 4;

  } else if(pid == comms_uptime_param_id) {

        uint32_t uptime = OSAL_sys_GetTick();
        *((uint32_t*)value) = uptime;
        cnv32_8(uptime, buf);
        *size = 4;

  } else if(pid == comms_sensor_status_param_id) {

    bool status[16];
    uint16_t size2;

    read_device_status(&status, &size2);

    buf[0] = 0;
    buf[1] = 0;

    for(uint8_t i = 0; i < 8; i++) {
      buf[1] |= (status[i] << i);
    }

    for(uint8_t i = 0; i < 8; i++) {
      buf[0] |= (status[i + 8] << i);
    }

    *((uint8_t*)value) = 0;
    *size = 2;

  } else {
    *size = 0;
  }

}

bool set_parameter(param_id pid, void* value) {

  bool res = true;

  if(pid == eps_testing_4_rw_param_id) {
    mem_pool.testing_4_rw = *((uint32_t*)value);

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

  } else if(pid == COMMS_EPS_RST_param_id) {

    HAL_PQ9_RST();

  } else {
    res = false;
  }
  return res;
}
