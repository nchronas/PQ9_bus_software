#include "parameters.h"
#include "satellite.h"
#include "devices.h"
#include "packet_utilities.h"
#include <stdint.h>

struct parameters_memory_pool {


  uint16_t testing_2;
  uint32_t testing_4;
  uint32_t testing_4_rw;

}mem_pool;

void init_parameters() {


  mem_pool.testing_2 = 0xCAFE;
  mem_pool.testing_4 = 0xDEADBEEF;

  mem_pool.testing_4_rw = 0xDEADBEEF;
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

  } else if(pid == red_uptime_param_id) {

        uint32_t uptime = OSAL_sys_GetTick();
        *((uint32_t*)value) = uptime;
        cnv32_8(uptime, buf);
        *size = 4;

  } else {
    *size = 0;
  }

}

bool set_parameter(param_id pid, void* value) {

  bool res = true;

  if(pid == eps_testing_4_rw_param_id) {
    mem_pool.testing_4_rw = *((uint32_t*)value);

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

  } else if(pid == dbg_led_param_id) {

      uint8_t val = *((uint8_t*)value);
      if(val == 1) {
        HAL_LED_ON();
      } else {
        HAL_LED_OFF();
      }

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
