#include "en_data_service.h"

#include "satellite.h"
#include "subsystem.h"

void crt_en_request(SBSYS_id dest_id) {
//  pq9_pkt *resp_pkt;
//
//  resp_pkt = get_pkt(0);
//  if(!C_ASSERT(resp_pkt != NULL) == true) {
//    return ;
//  }
//
//  crt_pkt(resp_pkt, dest_id, TC_EN_TYPE, TC_EN_REQ_SUBTYPE, 0);
//  queuePush(resp_pkt, RS_POOL_ID);
}

void crt_en_resp(SBSYS_id dest_id) {
//  pq9_pkt *resp_pkt;
//
//  resp_pkt = get_pkt(0);
//  if(!C_ASSERT(resp_pkt != NULL) == true) {
//    return ;
//  }
//
//  uint8_t size = 0;
//
//  bool res = transfer_rf_packet(resp_pkt->msg, &size);
//
//  uint8_t subtype = TM_EN_EMPTY_SUBTYPE;
//
//  if(res) {
//    subtype = TM_EN_RESP_SUBTYPE;
//  }
//
//  crt_pkt(resp_pkt, dest_id, TC_EN_TYPE, subtype, size);
//  queuePush(resp_pkt, RS_POOL_ID);
}

void en_data_app(pq9_pkt *pkt) {

//  if(pkt->subtype == TC_EN_REQ_SUBTYPE) {
//    crt_en_resp(pkt->src_id);
//  } else if(pkt->subtype == TM_EN_RESP_SUBTYPE) {
//    route_en_resp(pkt);
//  } else if(pkt->subtype == TM_EN_EMPTY_SUBTYPE) {
//
//  }

}
