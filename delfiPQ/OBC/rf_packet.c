#include "rf_packet.h"

#include "subsystem.h"
#include "queue.h"

void import_rf_packet(uint8_t *buf, uint16_t size) {

}

bool transfer_rf_packet(uint8_t *buf, uint16_t *size) {
  return false;
}

void route_en_resp(pq9_pkt *pkt) {

  pq9_pkt *rt_pkt;
  uint16_t size = 0;

  rt_pkt = get_pkt(size);
  if(!C_ASSERT(rt_pkt != NULL) == true) { return ; }

  bool res_unpack_PQ = unpack_PQ9_BUS(pkt->msg,
                                      pkt->size,
                                      rt_pkt);

  if(rt_pkt->dest_id != SYSTEM_APP_ID && res_unpack_PQ == true) {
      rt_pkt->size += 2; //type and subtype
      rt_pkt->size += 2; //packet counter
      enable_PQ9_tx();
      queuePush(rt_pkt, RS_POOL_ID);
  } else if(res_unpack_PQ == true) {
      route_pkt(rt_pkt);
      free_pkt(rt_pkt);
  } else {
      free_pkt(rt_pkt);
  }

  free_pkt(pkt);

}
