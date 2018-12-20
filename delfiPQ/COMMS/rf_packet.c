#include "rf_packet.h"

#include "subsystem.h"
#include "queue.h"

void import_rf_packet(uint8_t *buf, uint16_t size) {

  pq9_pkt *pkt;

  pkt = get_pkt(size);
  if(!C_ASSERT(pkt != NULL) == true) { return ; }

  bool res_unpack_PQ = unpack_PQ9_BUS(buf,
                                      size,
                                      pkt);
  if(res_unpack_PQ == true) {
    if(pkt->dest_id == SYSTEM_APP_ID) {
      route_pkt(pkt);
      free_pkt(pkt);
    } else {
      queuePush(pkt, RS_POOL_ID);
    }
  } else {
    free_pkt(pkt);
  }

}

bool transfer_rf_packet(uint8_t *buf, uint16_t *size) {

  pq9_pkt *pkt = 0;

  if((pkt = queuePop(RF_POOL_ID)) ==  NULL) {
    return false;
  }
  pkt->size += 2; //type and subtype
  pkt->size += 2; //packet counter

  bool res = pack_PQ9_BUS(pkt, buf, size);

  free_pkt(pkt);

//  buf[0] = 0x02;
//  buf[1] = 0x04;
//  buf[2] = 0x01;
//  buf[3] = 0x00;
//  buf[4] = 0x00;
//  buf[5] = 0x11;
//  buf[6] = 0x01;
//  buf[7] = 0x1D;
//  buf[8] = 0xBE;
//
//  *size = 9;

  return true;
}

void route_en_resp(pq9_pkt *pkt) {

}
