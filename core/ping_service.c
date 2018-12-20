#include "ping_service.h"

void crt_ping_resp(SBSYS_id dest_id) {

  pq9_pkt *resp_pkt;

  resp_pkt = get_pkt(0);
  if(!C_ASSERT(resp_pkt != NULL) == true) {
    return ;
  }

  crt_pkt(resp_pkt, dest_id, TC_PING_TYPE, TM_PING_RESP_SUBTYPE, 0, NULL);
  queuePush(resp_pkt, RS_POOL_ID);
}

void ping_app(pq9_pkt *pkt) {

  if(pkt->subtype == TC_PING_REQ_SUBTYPE) {
    crt_ping_resp(pkt->src_id);
  }
}
