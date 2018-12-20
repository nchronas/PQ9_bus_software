#include "packet_stats.h"

uint16_t rx_raw_counter = 0;

uint16_t rx_obc_counter = 0;
uint16_t rx_eps_counter = 0;
uint16_t rx_adb_counter = 0;
uint16_t rx_adcs_counter = 0;
uint16_t rx_comms_counter = 0;
uint16_t rx_dbg_counter = 0;

uint16_t tx_obc_counter = 0;
uint16_t tx_eps_counter = 0;
uint16_t tx_adb_counter = 0;
uint16_t tx_adcs_counter = 0;
uint16_t tx_comms_counter = 0;
uint16_t tx_dbg_counter = 0;

uint16_t err_counter = 0;

void copy_stats(uint8_t *buf, uint16_t *pkt_size) {

  uint16_t size = 0;

  cnv16_8(rx_raw_counter, &buf[size]);
  size += 2;

  cnv16_8(err_counter, &buf[size]);
  size += 2;

  cnv16_8(rx_obc_counter, &buf[size]);
  size += 2;
  cnv16_8(rx_eps_counter, &buf[size]);
  size += 2;
  cnv16_8(rx_adb_counter, &buf[size]);
  size += 2;
  cnv16_8(rx_adcs_counter, &buf[size]);
  size += 2;
  cnv16_8(rx_comms_counter, &buf[size]);
  size += 2;
  cnv16_8(rx_dbg_counter, &buf[size]);
  size += 2;

  cnv16_8(tx_obc_counter, &buf[size]);
  size += 2;
  cnv16_8(tx_eps_counter, &buf[size]);
  size += 2;
  cnv16_8(tx_adb_counter, &buf[size]);
  size += 2;
  cnv16_8(tx_adcs_counter, &buf[size]);
  size += 2;
  cnv16_8(tx_comms_counter, &buf[size]);
  size += 2;
  cnv16_8(tx_dbg_counter, &buf[size]);
  size += 2;

  *pkt_size += size;
}


void crt_pstats_request(SBSYS_id dest_id) {
  pq9_pkt *resp_pkt;

  resp_pkt = get_pkt(0);
  if(!C_ASSERT(resp_pkt != NULL) == true) {
    return ;
  }

  uint16_t size = 0;

  crt_pkt(resp_pkt, dest_id, TC_STATS_TYPE, TC_STATS_REQ_SUBTYPE, size, NULL);
  queuePush(resp_pkt, RS_POOL_ID);
}

void crt_pstats_resp(SBSYS_id dest_id) {
  pq9_pkt *resp_pkt;

  resp_pkt = get_pkt(0);
  if(!C_ASSERT(resp_pkt != NULL) == true) {
    return ;
  }

  uint16_t size = 0;

  copy_stats(resp_pkt->msg, &size);

  crt_pkt(resp_pkt, dest_id, TC_STATS_TYPE, TM_STATS_RESP_SUBTYPE, size, NULL);
  queuePush(resp_pkt, RS_POOL_ID);
}

void pstats_app(pq9_pkt *pkt) {
  if(pkt->subtype == TC_STATS_REQ_SUBTYPE) {
    crt_pstats_resp(pkt->src_id);
  }
}

void update_pstats_rx_raw_counter() {
  rx_raw_counter++;
}

void update_pstats_rx_counter(SBSYS_id id) {

  if(id == OBC_APP_ID) {
    rx_obc_counter++;
  } else if(id == EPS_APP_ID) {
    rx_eps_counter++;
  } else if(id == ADB_APP_ID) {
    rx_adb_counter++;
  } else if(id == ADCS_APP_ID) {
    rx_adcs_counter++;
  } else if(id == COMMS_APP_ID) {
    rx_comms_counter++;
  } else if(id == DBG_APP_ID) {
    rx_dbg_counter++;
  }
}

void update_pstats_tx_counter(SBSYS_id id) {

  if(id == OBC_APP_ID) {
    tx_obc_counter++;
  } else if(id == EPS_APP_ID) {
    tx_eps_counter++;
  } else if(id == ADB_APP_ID) {
    tx_adb_counter++;
  } else if(id == ADCS_APP_ID) {
    tx_adcs_counter++;
  } else if(id == COMMS_APP_ID) {
    tx_comms_counter++;
  } else if(id == DBG_APP_ID) {
    tx_dbg_counter++;
  }
}

void update_pstats_rx_err_counter() {
    err_counter++;
}
