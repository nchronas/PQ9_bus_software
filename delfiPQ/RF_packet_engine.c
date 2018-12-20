
bool pack_RF(pq9_pkt *pq_pkt) {
  get_parameter(system_time_paramid, );

  pq9_pkt *resp_pkt;

  resp_pkt = get_pkt(0);
  if(!C_ASSERT(resp_pkt != NULL) == true) {
    return ;
  }

  resp_pkt->msg[0] = ;


  crt_pkt(resp_pkt, COMMS_APP_ID, TC_RF_TYPE, TC_RF_TX_SUBTYPE, 0);
  queuePush(resp_pkt, RS_POOL_ID);

}
