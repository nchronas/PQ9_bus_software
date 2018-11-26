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

        //boot counter + software boot counter
        buf[size] = 0;
        size ++;
        buf[size] = 0;
        size ++;
        buf[size] = 0;
        size ++;

        get_parameter(testing_2_param_id, &var, &buf[size], &param_size);
        size += param_size;

        *pkt_size += size;

    return SATR_OK;
}

void store_housekeeping(SBSYS_id id, uint8_t *buf, uint16_t size) {

}

void retrieve_housekeeping(SBSYS_id id, uint8_t *buf, uint16_t *size) {

}
