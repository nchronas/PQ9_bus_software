#include "pkt_pool.h"

#include <stddef.h>
#include "satellite.h"
#include "packet_engine.h"
#include "osal.h"


struct _pkt_pool{
    pq9_pkt pkt[POOL_PKT_SIZE];
    uint8_t free[POOL_PKT_SIZE];
    uint32_t time[POOL_PKT_SIZE];

};

struct _pkt_pool pkt_pool;

pq9_pkt * get_pkt(const uint16_t size) {

    if(size <= PKT_NORMAL) {
        for(uint8_t i = 0; i < POOL_PKT_SIZE; i++) {
            if(pkt_pool.free[i] == true) {
                pkt_pool.free[i] = false;
                pkt_pool.time[i] = OSAL_sys_GetTick();
                pkt_pool.pkt[i].notification_flag = NULL;
                return &pkt_pool.pkt[i];
            }
        }
    }

    return NULL;
}

SAT_returnState free_pkt(pq9_pkt *pkt) {

    if(!C_ASSERT(pkt != NULL) == true) { return SATR_ERROR; }

    for(uint8_t i = 0; i <= POOL_PKT_SIZE; i++) {
        if(&pkt_pool.pkt[i] == pkt) {
            pkt_pool.free[i] = true;
            return SATR_OK;
        }
    }

    return SATR_ERROR;
}

bool is_free_pkt(pq9_pkt *pkt) {

   for(uint8_t i = 0; i <= POOL_PKT_SIZE; i++) {
        if(&pkt_pool.pkt[i] == pkt) {
            if(pkt_pool.free[i] == true) {
                return true;
            }
            return false;
        }
    }
    return false;
}

void pkt_pool_INIT() {

    for(uint8_t i = 0; i < POOL_PKT_SIZE; i++) {
       pkt_pool.free[i] = true;
       pkt_pool.pkt[i].notification_flag = NULL;
    }
}

void pkt_pool_IDLE(uint32_t tmp_time) {

    for(uint8_t i = 0; i < POOL_PKT_SIZE; i++) {
        if(pkt_pool.free[i] == false && pkt_pool.time[i] - tmp_time > PKT_TIMEOUT) {
            pkt_pool.free[i] = true;
        }
    }

}
