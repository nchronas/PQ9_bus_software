#include "housekeeping_service.h"
#include "satellite.h"
#include "subsystem.h"

void crt_hk_request(SBSYS_id dest_id, uint8_t *flag) {
  pq9_pkt *resp_pkt;

  resp_pkt = get_pkt(0);
  if(!C_ASSERT(resp_pkt != NULL) == true) {
    return ;
  }

  crt_pkt(resp_pkt, dest_id, TC_HK_TYPE, TC_HK_REQ_SUBTYPE, 0, flag);
  queuePush(resp_pkt, RS_POOL_ID);
}

void crt_housekeeping_resp(SBSYS_id dest_id) {
  pq9_pkt *resp_pkt;

  resp_pkt = get_pkt(0);
  if(!C_ASSERT(resp_pkt != NULL) == true) {
    return ;
  }

//  uint8_t size = 1;
//  resp_pkt->msg[0] = SYSTEM_APP_ID;
//
//  populate_housekeeping(&resp_pkt->msg[1], &size);

   uint8_t size = 0;

   populate_housekeeping(&resp_pkt->msg[0], &size);


  crt_pkt(resp_pkt, dest_id, TC_HK_TYPE, TM_HK_RESP_SUBTYPE, size, NULL);
  queuePush(resp_pkt, RS_POOL_ID);
}

void crt_housekeeping_transmit(SBSYS_id id) {
  pq9_pkt *resp_pkt;

  resp_pkt = get_pkt(0);
  if(!C_ASSERT(resp_pkt != NULL) == true) {
    return ;
  }

  uint16_t size = 0;

  retrieve_housekeeping(id, resp_pkt->msg, &size);

  if(size == 0) {
    resp_pkt->msg[0] = id;

    resp_pkt->msg[1] = 'E';
    resp_pkt->msg[2] = 'M';
    resp_pkt->msg[3] = 'P';
    resp_pkt->msg[4] = 'T';
    resp_pkt->msg[5] = 'Y';
    size = 6;
  }

  crt_pkt(resp_pkt, COMMS_APP_ID, TC_HK_TYPE, TM_HK_RF_SUBTYPE, size, NULL);
  queuePush(resp_pkt, RS_POOL_ID);
}

void store_housekeeping_resp(pq9_pkt *pkt) {

  store_housekeeping(pkt->msg[0], pkt->msg, pkt->size);

}



void housekeeping_app(pq9_pkt *pkt) {

  if(pkt->subtype == TC_HK_REQ_SUBTYPE) {
    crt_housekeeping_resp(pkt->src_id);
  } else if(pkt->subtype == TM_HK_RESP_SUBTYPE) {
    store_housekeeping_resp(pkt);
  } else if(pkt->subtype == TM_HK_RF_SUBTYPE) {
    //transmit_housekeeping(pkt);
  }

}
