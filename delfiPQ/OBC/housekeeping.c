#include "housekeeping.h"

#include "devices.h"
#include "osal.h"
#include "packet_utilities.h"
#include "parameters.h"

uint8_t adb_hk_buffer[255];
uint8_t adcs_hk_buffer[255];
uint8_t eps_hk_buffer[255];
uint8_t comms_hk_buffer[255];

uint8_t adb_hk_size = 0;
uint8_t adcs_hk_size = 0;
uint8_t eps_hk_size = 0;
uint8_t comms_hk_size = 0;

void clr_hk_storage() {
  adb_hk_size = 0;
  adcs_hk_size = 0;
  eps_hk_size = 0;
  comms_hk_size = 0;
}

void populate_housekeeping(uint8_t *buf, uint8_t *pkt_size) {

        uint16_t size = 0;
        uint16_t param_size = 0;
        uint32_t var;

        cnv32_8( OSAL_sys_GetTick(), &buf[size]);
        size += 4;

        get_parameter(testing_4_param_id, &var, &buf[size], &param_size);
        size += param_size;

        get_parameter(OBC_boot_counter_param_id, (void*)&var, &buf[size], &param_size);
        size += param_size;

        buf[size] = 0;
        size += 1;

        get_parameter(obc_sensor_status_param_id, &var, &buf[size], &param_size);
        size += param_size;

        struct ina_device ina_dev;

        read_device_parameters(OBC_MON_DEV_ID, &ina_dev);

        cnv16_8(ina_dev.current_raw, &buf[size]);
        size += 2;
        cnv16_8(ina_dev.voltage_raw, &buf[size]);
        size += 2;

        get_parameter(MPP_lpm_sen_param_id, &var, &buf[size], &param_size);
        size += param_size;

        get_parameter(testing_2_param_id, &var, &buf[size], &param_size);
        size += param_size;

        *pkt_size += size;

    return SATR_OK;
}

void store_housekeeping(SBSYS_id id, uint8_t *buf, uint16_t size) {

  if(id == ADB_APP_ID) {
    memcpy(adb_hk_buffer, buf, size);
    adb_hk_size = size;
  } else if(id == ADCS_APP_ID) {
    memcpy(adcs_hk_buffer, buf, size);
    adcs_hk_size = size;
  } else if(id == EPS_APP_ID) {
    memcpy(eps_hk_buffer, buf, size);
    eps_hk_size = size;
  } else if(id == COMMS_APP_ID) {
    memcpy(comms_hk_buffer, buf, size);
    comms_hk_size = size;
  }

}

void retrieve_housekeeping(SBSYS_id id, uint8_t *buf, uint16_t *size) {

  if(id == ADB_APP_ID) {
    memcpy(buf, adb_hk_buffer, adb_hk_size);
    *size = adb_hk_size;
  } else if(id == ADCS_APP_ID) {
    memcpy(buf, adcs_hk_buffer, adcs_hk_size);
    *size = adcs_hk_size;
  } else if(id == EPS_APP_ID) {
    memcpy(buf, eps_hk_buffer, eps_hk_size);
    *size = eps_hk_size;
  } else if(id == COMMS_APP_ID) {
    memcpy(buf, comms_hk_buffer, comms_hk_size);
    *size = comms_hk_size;
  } else if(id == OBC_APP_ID) {
    buf[0] = OBC_APP_ID;
    populate_housekeeping(&buf[1], size);
  }
}
