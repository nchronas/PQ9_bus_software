#include "housekeeping.h"

#include "devices.h"
#include "osal.h"
#include "packet_utilities.h"
#include "parameters.h"


void populate_housekeeping(uint8_t *buf, uint8_t *pkt_size) {

        uint16_t size = 0;
        uint16_t param_size = 0;

        uint8_t buf2[4];

        cnv32_8( OSAL_sys_GetTick(), &buf[size]);
        size += 4;

        {
          uint32_t var;
          get_parameter(testing_4_param_id, &var, &buf[size], &param_size);
          //cnv32_8(var, &buf[size]);
          size += param_size;
        }

        //boot counter + software boot counter
        buf[size] = 0;
        size ++;
        buf[size] = 0;
        size ++;
        buf[size] = 0;
        size ++;

        {
          uint32_t var;
          get_parameter(comms_sensor_status_param_id, &var, &buf[size], &param_size);
          size += param_size;
        }

        struct tmp_device tmp_dev;

        read_device_parameters(COMMS_TEMP_DEV_ID, &tmp_dev);

        cnv16_8(tmp_dev.raw_temp,&buf[size]);
        size += 2;

        struct adc_device adc_dev;

        read_device_parameters(COMMS_ADC_DEV_ID, &adc_dev);

        for(uint16_t i = 0; i < MAX_ADC_DEVS; i++)
        {
          cnv16_8(adc_dev.raw[i],&buf[size]);
          size += 2;
        }

        {
          uint16_t var;
          get_parameter(testing_2_param_id, &var, &buf[size], &param_size);
          size += param_size;
        }


        *pkt_size += size;

    return SATR_OK;
}

void store_housekeeping(SBSYS_id id, uint8_t *buf, uint16_t size) {

}

void retrieve_housekeeping(SBSYS_id id, uint8_t *buf, uint16_t *size) {

}
