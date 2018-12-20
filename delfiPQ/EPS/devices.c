
#include "devices.h"

#include "hal_functions.h"
#include "hal_subsystem.h"

#include "INA226.h"
#include "TMP100.h"
#include "LTC2942.h"
#include "MB85RS256A.h"


#include <ti/drivers/UART.h>

#define MAX_TMP_DEVS 4
#define MAX_INA_DEVS 10

struct tmp_device tmp_dev[MAX_TMP_DEVS];
struct ina_device ina_dev[MAX_INA_DEVS];
struct ltc_device ltc_dev;
struct powerline_device powerline_dev;
struct tmp_device int_temp_dev[1];
struct int_wdg_device int_wdg_dev;

bool tmp_status[MAX_TMP_DEVS];
bool ina_status[MAX_INA_DEVS];
bool ltc_status[1];
bool int_temp_status[1];

void device_init() {

  HAL_peripheral_open();

  uint8_t i;

  for(i = 0; i < MAX_TMP_DEVS; i++) {
    tmp_dev[i].id = i + SOL_YP_TEMP_DEV_ID;
    tmp_dev[i].temp = 0;
    tmp_dev[i].raw_temp = 0;
    tmp_init(tmp_dev[i].id);
  }

  for(i = 0; i < MAX_INA_DEVS; i++) {
    ina_dev[i].id = i + EPS_V1_MON_DEV_ID;
    ina_dev[i].voltage = 0;
    ina_dev[i].current = 0;
    ina_dev[i].power = 0;
    ina_dev[i].voltage_raw = 0;
    ina_dev[i].current_raw = 0;
    ina_dev[i].power_raw = 0;
    ina_dev[i].shunt = 0.040;
    INA226_configure(ina_dev[i].id,
                      INA226_AVERAGES_1,
                      INA226_BUS_CONV_TIME_1100US,
                      INA226_SHUNT_CONV_TIME_1100US,
                      INA226_MODE_SHUNT_BUS_CONT);
    usleep(10);
      // Calibrate INA226. Rshunt = 0.01 ohm, Max excepted current = 4A
    INA226_calibrate(ina_dev[i].id,
                     0.04,
                     0.5,
                     &(ina_dev[i].currentLSB),
                     &(ina_dev[i].powerLSB));
    usleep(10);
  }


  ltc_dev.id = BATT_CHARGE_DEV_ID;
  ltc_init(BATT_CHARGE_DEV_ID);

  usleep(10);

  FRAM_init(EPS_FRAM_DEV_ID);

  int_temp_dev[0].id = EPS_INT_TEMP_DEV_ID;
  int_temp_dev[0].temp = 55;
  int_temp_dev[0].raw_temp = 77;

  powerline_dev.b1_state = true;
  powerline_dev.b2_state = true;
  powerline_dev.b3_state = true;
  powerline_dev.b4_state = true;

  powerline_dev.b1_enabled = true;
  powerline_dev.b2_enabled = true;
  powerline_dev.b3_enabled = true;
  powerline_dev.b4_enabled = true;

  HAL_eps_v1_ON();
  HAL_eps_v2_ON();
  HAL_eps_v3_ON();
  HAL_eps_v4_ON();

  usleep(10);

  int_wdg_dev.clr = 0;
  int_wdg_dev.cmd = 0;

}

extern UART_Handle uart_dbg_bus;
char msg_dev[200];

void update_device(dev_id id) {

  OSAL_device_pend();

  if(id == EPS_V1_MON_DEV_ID ||
     id == EPS_V2_MON_DEV_ID ||
     id == EPS_V3_MON_DEV_ID ||
     id == EPS_V4_MON_DEV_ID ||
     id == EPS_DC_MON_DEV_ID ||
     id == EPS_UR_MON_DEV_ID ||
     id == SOL_YP_MON_DEV_ID ||
     id == SOL_YM_MON_DEV_ID ||
     id == SOL_XP_MON_DEV_ID ||
     id == SOL_XM_MON_DEV_ID ) {

    uint8_t pos_index = id - EPS_V1_MON_DEV_ID;

    ina_dev[pos_index].voltage_raw = 0;
    ina_dev[pos_index].current_raw = 0;

    bool r1 = INA226_readShuntCurrent_raw(id, &ina_dev[pos_index].current_raw );
    OSAL_sys_delay(1);

    bool r2 = INA226_readBusVoltage_raw(id, &ina_dev[pos_index].voltage_raw);
    OSAL_sys_delay(1);

    INA226_readBusPower_raw(id, &ina_dev[pos_index].power_raw);

    //uint8_t add;
    //HAL_access_device_peripheral_meta(id, &add);

    //sprintf(msg_dev, "INA: %d, %d, E: %d.%d, C %d, V %d\n", id, add, (int)r1, (int)r2, (int)(ina_dev[pos_index].current_raw), (int)ina_dev[pos_index].voltage_raw);
    //UART_write(uart_dbg_bus, msg_dev, strlen(msg_dev));

    //INA226_rawBusPower(ina_dev[pos_index].power_raw , ina_dev[pos_index].powerLSB);
    //INA226_rawShuntCurrent( ina_dev[pos_index].current_raw, ina_dev[pos_index].currentLSB);
    //INA226_rawBusVoltage(ina_dev[pos_index].voltage_raw);

    ina_status[pos_index] = r1 & r2;

  } else if(id == SOL_YP_TEMP_DEV_ID ||
            id == SOL_YM_TEMP_DEV_ID ||
            id == SOL_XP_TEMP_DEV_ID ||
            id == SOL_XM_TEMP_DEV_ID) {

     uint8_t pos_index = id - SOL_YP_TEMP_DEV_ID;

     tmp_dev[pos_index].raw_temp = 0;

     tmp_status[pos_index] = tmp_getTemperature_raw(id, &tmp_dev[pos_index].raw_temp);
     tmp_getRawTemperature(id, &tmp_dev[pos_index].raw_temp, &tmp_dev[pos_index].temp);

  }  else if(id == EPS_INT_TEMP_DEV_ID) {

    //int_temp_dev[0].raw_temp = 17;

    uint16_t val = 0;
    int_temp_status[0] = HAL_internal_temp(&val);
    //int_temp_dev[0].raw_temp = val;
    if(val == 0) {
        int_temp_dev[0].raw_temp = 0x69;
    } else {
        int_temp_dev[0].raw_temp = val;
    }

  }  else if(id == BATT_CHARGE_DEV_ID) {

    bool r1 = ltc_code_to_voltage(id, &ltc_dev.raw_volt);
    bool r2 = ltc_temp(id, &ltc_dev.raw_temp);
    bool r3 = ltc_capacity(id, &ltc_dev.raw_cap);

    ltc_status[0] = r1 & r2 & r3;

  }

  OSAL_device_post();

}

void read_device_status(bool *status, uint16_t *size) {

  for(uint16_t i = 0; i < MAX_TMP_DEVS; i++)
  {
    status[i] = tmp_status[i];
  }

  for(uint16_t i = 0; i < MAX_INA_DEVS; i++)
  {
    status[i + MAX_TMP_DEVS] = ina_status[i];
  }

  status[MAX_TMP_DEVS + MAX_INA_DEVS] = ltc_status[0];

  status[MAX_TMP_DEVS + MAX_INA_DEVS + 1] = int_temp_status[0];

  *size = MAX_TMP_DEVS + MAX_INA_DEVS + 1 + 1;
}

void read_device_parameters(dev_id id, void * data) {

  OSAL_device_pend();

  if(id == EPS_V1_MON_DEV_ID ||
     id == EPS_V2_MON_DEV_ID ||
     id == EPS_V3_MON_DEV_ID ||
     id == EPS_V4_MON_DEV_ID ||
     id == EPS_DC_MON_DEV_ID ||
     id == EPS_UR_MON_DEV_ID ||
     id == SOL_YP_MON_DEV_ID ||
     id == SOL_YM_MON_DEV_ID ||
     id == SOL_XP_MON_DEV_ID ||
     id == SOL_XM_MON_DEV_ID ) {

      uint8_t pos_index = id - EPS_V1_MON_DEV_ID;

    ((struct ina_device*)data)->power = ina_dev[pos_index].power;
    ((struct ina_device*)data)->current = ina_dev[pos_index].current;
    ((struct ina_device*)data)->voltage = ina_dev[pos_index].voltage;

    ((struct ina_device*)data)->power_raw = ina_dev[pos_index].power_raw;
    ((struct ina_device*)data)->current_raw = ina_dev[pos_index].current_raw;
    ((struct ina_device*)data)->voltage_raw = ina_dev[pos_index].voltage_raw;


  } else if(id == SOL_YP_TEMP_DEV_ID ||
            id == SOL_YM_TEMP_DEV_ID ||
            id == SOL_XP_TEMP_DEV_ID ||
            id == SOL_XM_TEMP_DEV_ID) {

      uint8_t pos_index = id - SOL_YP_TEMP_DEV_ID;

     ((struct tmp_device*)data)->raw_temp = tmp_dev[pos_index].raw_temp;
     ((struct tmp_device*)data)->temp = tmp_dev[pos_index].temp;

  }  else if(id == BATT_CHARGE_DEV_ID) {

    ((struct ltc_device*)data)->raw_temp = ltc_dev.raw_temp;
    ((struct ltc_device*)data)->raw_cap = ltc_dev.raw_cap;
    ((struct ltc_device*)data)->raw_volt = ltc_dev.raw_volt;

  }  else if(id == EPS_FRAM_DEV_ID) {

     FRAM_read(id,
               ((struct fram_device*)data)->address,
               ((struct fram_device*)data)->buffer,
               ((struct fram_device*)data)->count);

  }  else if(id == EPS_POWERLINES_DEV_ID) {

    ((struct powerline_device*)data)->b1_state = powerline_dev.b1_state;
    ((struct powerline_device*)data)->b2_state = powerline_dev.b2_state;
    ((struct powerline_device*)data)->b3_state = powerline_dev.b3_state;
    ((struct powerline_device*)data)->b4_state = powerline_dev.b4_state;

    ((struct powerline_device*)data)->b1_enabled = powerline_dev.b1_enabled;
    ((struct powerline_device*)data)->b2_enabled = powerline_dev.b2_enabled;
    ((struct powerline_device*)data)->b3_enabled = powerline_dev.b3_enabled;
    ((struct powerline_device*)data)->b4_enabled = powerline_dev.b4_enabled;

  }  else if(id == EPS_INT_TEMP_DEV_ID) {

    ((struct tmp_device*)data)->raw_temp = int_temp_dev[0].raw_temp;

    //((struct tmp_device*)data)->raw_temp = int_raw_temp;

  }  else if(id == INT_WDG_DEV_ID) {

    ((struct int_wdg_device*)data)->clr = int_wdg_dev.clr;
    ((struct int_wdg_device*)data)->cmd = int_wdg_dev.cmd;

  }

  OSAL_device_post();
}

void write_device_parameters(dev_id id, void * data) {

  if(id == EPS_V1_MON_DEV_ID ||
     id == EPS_V2_MON_DEV_ID ||
     id == EPS_V3_MON_DEV_ID ||
     id == EPS_V4_MON_DEV_ID ||
     id == EPS_DC_MON_DEV_ID ||
     id == EPS_UR_MON_DEV_ID ||
     id == SOL_YP_MON_DEV_ID ||
     id == SOL_YM_MON_DEV_ID ||
     id == SOL_XP_MON_DEV_ID ||
     id == SOL_XM_MON_DEV_ID ) {

       uint16_t temp_id = id - EPS_V1_MON_DEV_ID;
       ina_dev[temp_id].shunt = ((struct ina_device*)data)->shunt;
       //ina_setShuntResistor(ina_dev[temp_id].id,
       //                     ina_dev[temp_id].shunt);

  } else if(id == SOL_YP_TEMP_DEV_ID ||
            id == SOL_YM_TEMP_DEV_ID ||
            id == SOL_XP_TEMP_DEV_ID ||
            id == SOL_XM_TEMP_DEV_ID) {

        uint16_t temp_id = id - SOL_YP_TEMP_DEV_ID;

        //tmp_init(tmp_dev[temp_id].id,
        //            &(tmp_dev[temp_id].mul),
        //            tmp_dev[temp_id].resolution);

  }  else if(id == BATT_CHARGE_DEV_ID) {

  }  else if(id == EPS_FRAM_DEV_ID) {

     FRAM_write(id,
                ((struct fram_device*)data)->address,
                ((struct fram_device*)data)->buffer,
                ((struct fram_device*)data)->count);

  }  else if(id == EPS_POWERLINES_DEV_ID) {

    powerline_dev.b1_state = ((struct powerline_device*)data)->b1_state;
    powerline_dev.b2_state = ((struct powerline_device*)data)->b2_state;
    powerline_dev.b3_state = ((struct powerline_device*)data)->b3_state;
    powerline_dev.b4_state = ((struct powerline_device*)data)->b4_state;

    powerline_dev.b1_enabled = ((struct powerline_device*)data)->b1_enabled;
    powerline_dev.b2_enabled = ((struct powerline_device*)data)->b2_enabled;
    powerline_dev.b3_enabled = ((struct powerline_device*)data)->b3_enabled;
    powerline_dev.b4_enabled = ((struct powerline_device*)data)->b4_enabled;

    if(powerline_dev.b1_enabled && powerline_dev.b1_state) {
      powerline_dev.b1_state = true;
      HAL_eps_v1_ON();
    } else if(powerline_dev.b1_enabled && !powerline_dev.b1_state) {
      powerline_dev.b1_state = false;
      HAL_eps_v1_OFF();
    } else {
      powerline_dev.b1_state = false;
      HAL_eps_v1_OFF();
    }

    if(powerline_dev.b2_enabled && powerline_dev.b2_state) {
      powerline_dev.b2_state = true;
      HAL_eps_v2_ON();
    } else if(powerline_dev.b2_enabled && !powerline_dev.b2_state) {
      powerline_dev.b2_state = false;
      HAL_eps_v2_OFF();
    } else {
      powerline_dev.b2_state = false;
      HAL_eps_v2_OFF();
    }


    if(powerline_dev.b3_enabled && powerline_dev.b3_state) {
      powerline_dev.b3_state = true;
      HAL_eps_v3_ON();
    } else if(powerline_dev.b3_enabled && !powerline_dev.b3_state) {
      powerline_dev.b3_state = false;
      HAL_eps_v3_OFF();
    } else {
      powerline_dev.b3_state = false;
      HAL_eps_v3_OFF();
    }

    if(powerline_dev.b4_enabled && powerline_dev.b4_state) {
      powerline_dev.b4_state = true;
      HAL_eps_v4_ON();
    } else if(powerline_dev.b2_enabled && !powerline_dev.b4_state) {
      powerline_dev.b4_state = false;
      HAL_eps_v4_OFF();
    } else {
      powerline_dev.b4_state = false;
      HAL_eps_v4_OFF();
    }

  }  else if(id == INT_WDG_DEV_ID) {

    int_wdg_dev.clr = ((struct int_wdg_device*)data)->clr;
    int_wdg_dev.cmd = ((struct int_wdg_device*)data)->cmd;

    if(int_wdg_dev.clr && !int_wdg_dev.cmd) {
      HAL_clear_int_wdg();
      int_wdg_dev.clr = false;
    }

  }

}

bool set_device_parameters(dev_id id, void * data) {

  bool res = false;

  return res;
}
