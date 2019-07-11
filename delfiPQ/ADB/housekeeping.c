#include "housekeeping.h"

#include "devices.h"
#include "osal.h"
#include "packet_utilities.h"
#include "parameters.h"

void populate_housekeeping(uint8_t *buf, uint8_t *pkt_size) {

        uint16_t size = 0;
        uint16_t param_size = 0;
        uint32_t var;

        cnv32_8( OSAL_sys_GetTick(), &buf[size]);
        size += 4;

        get_parameter(testing_4_param_id, &var, &buf[size], &param_size);
        size += param_size;

        buf[size] = 0;
        size += 1;
        buf[size] = 0;
        size += 1;
        buf[size] = 0;
        size += 1;

        get_parameter(adb_sensor_status_param_id, &var, &buf[size], &param_size);
        size += param_size;

        struct ina_device ina_dev;

        read_device_parameters(ADB_MON_DEV_ID, &ina_dev);

        cnv16_8(ina_dev.current_raw, &buf[size]);
        size += 2;
        cnv16_8(ina_dev.voltage_raw, &buf[size]);
        size += 2;

        struct tmp_device tmp_dev;

        read_device_parameters(ADB_TEMP_DEV_ID, &tmp_dev);

        cnv16_8(tmp_dev.raw_temp, &buf[size]);
        size += 2;

        get_parameter(adb_deb_param_id, &var, &buf[size], &param_size);
        size += param_size;

        get_parameter(adb_int_temp_param_id, &var, &buf[size], &param_size);
        size += param_size;

        get_parameter(testing_2_param_id, &var, &buf[size], &param_size);
        size += param_size;

        *pkt_size += size;

    return SATR_OK;
}

void store_housekeeping(SBSYS_id id, uint8_t *buf, uint16_t size) {

}

void retrieve_housekeeping(SBSYS_id id, uint8_t *buf, uint16_t *size) {

}
