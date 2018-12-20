#include "packet_engine.h"

#include "PQ9_bus_engine.h"
#include "hal_functions.h"
#include "packet_stats.h"
#include "testing.h"

#define TX_RETRIES_NUM 3

struct _uart_data {
    uint8_t uart_rx_buf[UART_BUF_SIZE];
    uint8_t uart_tx_buf[UART_BUF_SIZE];
} ud;


extern bool master_loop_flag;

void PQ9_master() {

  uint32_t cmd_loop;
  uint8_t buf[4];
  uint16_t size;
  uint8_t flag;
  uint8_t num_of_retries;

#ifdef DEBUG
  if(!master_loop_flag) {
    return;
  }
#endif

  get_parameter(Master_command_loop_param_id, &cmd_loop, buf, &size);

  clr_hk_storage();

  flag = false;
  num_of_retries = 3;

  crt_hk_request(ADB_APP_ID, NULL);
  // enable_PQ9_tx();
  sleep(1); //usleep(cmd_loop);

  crt_hk_request(EPS_APP_ID, NULL);
  // enable_PQ9_tx();
  sleep(1); //usleep(cmd_loop);

  crt_hk_request(ADCS_APP_ID, NULL);
  // enable_PQ9_tx();
  sleep(1); //usleep(cmd_loop);

  crt_hk_request(COMMS_APP_ID, &flag);
  // enable_PQ9_tx();
  sleep(1); //usleep(cmd_loop);

  sleep(9);

  do {
    /* code */
    num_of_retries--;
    usleep(10);
  } while(!flag && num_of_retries);

  if(num_of_retries) {
    // call FDIR
  }



  // crt_pstats_request(ADB_APP_ID);
  // enable_PQ9_tx();
  // sleep(1);

  // crt_pstats_request(EPS_APP_ID);
  // enable_PQ9_tx();
  // sleep(1);

  // crt_pstats_request(ADCS_APP_ID);
  // enable_PQ9_tx();
  // sleep(1);
  //
  // crt_pstats_request(COMMS_APP_ID);
  // enable_PQ9_tx();
  // sleep(1);

  // crt_pstats_resp(DBG_APP_ID);
  // enable_PQ9_tx();
  // sleep(1);

  //add parameter
  //usleep(cmd_loop);

}

void query_comms() {



}

void beacon_generation() {

  crt_housekeeping_transmit(ADB_APP_ID);
  sleep(1); //usleep(cmd_loop);

  crt_housekeeping_transmit(EPS_APP_ID);
  sleep(1); //usleep(cmd_loop);

  crt_housekeeping_transmit(ADCS_APP_ID);
  sleep(1); //usleep(cmd_loop);

  crt_housekeeping_transmit(COMMS_APP_ID);
  sleep(1); //usleep(cmd_loop);

  crt_housekeeping_transmit(OBC_APP_ID);
  sleep(1); //usleep(cmd_loop);

}

void transmit() {

  pq9_pkt *pkt_tx = 0;
  uint16_t size = 0;

  if((pkt_tx = queuePop(RS_POOL_ID)) ==  NULL) {
    disable_PQ9_tx();
    return ;
  }

  PQ9_tx();

  bool res = pack_PQ9_BUS(pkt_tx, ud.uart_tx_buf, &size);
  if(res == false) {
    disable_PQ9_tx();
    free_pkt(pkt_tx);
    return ;
  }

  if(!C_ASSERT(size > 0) == true) {
    disable_PQ9_tx();
    free_pkt(pkt_tx);
    return ;
  }

  //update_pstats_tx_counter(pkt_tx->dest_id);
  HAL_uart_tx(0, &ud.uart_tx_buf, size);

  disable_PQ9_tx();

  free_pkt(pkt_tx);
}

void PQ9_beta() {

  bool res_uart = false;

  pq9_pkt *pkt_rx;
  uint16_t uart_size = 0;
  uint16_t pq_size = 0;

  res_uart = HAL_uart_rx(0, &ud.uart_rx_buf, &uart_size);
  if(res_uart == true) {

    //update_pstats_rx_raw_counter();

    pkt_rx = get_pkt(pq_size);
    if(!C_ASSERT(pkt_rx != NULL) == true) {
      //update_pstats_rx_err_counter();
      return ;
    }

    bool res_unpack_PQ = unpack_PQ9_BUS(&ud.uart_rx_buf,
                                        uart_size,
                                        pkt_rx);
    if(res_unpack_PQ == true) {

      //notify_tx_event(pkt_rx);
      //update_pstats_rx_counter(pkt_rx->src_id);

      enable_PQ9_tx();

      route_pkt(pkt_rx);
    } else {
      //update_pstats_rx_err_counter();
      free_pkt(pkt_rx);
      return ;
    }

    free_pkt(pkt_rx);

    transmit();

  }

}

void PQ9_primary() {

  PQ9_beta();

  pq9_pkt *pkt_tx = 0;
  uint16_t size = 0;

  if((pkt_tx = queuePop(RS_POOL_ID)) ==  NULL) {
    return ;
  }

  PQ9_tx();

  bool res = pack_PQ9_BUS(pkt_tx, ud.uart_tx_buf, &size);
  if(res == false) {
    disable_PQ9_tx();
    free_pkt(pkt_tx);
    return ;
  }

  if(!C_ASSERT(size > 0) == true) {
    disable_PQ9_tx();
    free_pkt(pkt_tx);
    return ;
  }

  //update_pstats_tx_counter(pkt_tx->dest_id);
  HAL_uart_tx(0, &ud.uart_tx_buf, size);

  disable_PQ9_tx();

  bool res_uart = false;

  pq9_pkt *pkt_rx;
  uint16_t uart_size = 0;
  uint16_t pq_size = 0;
  uint8_t  rx_tries = 0;

  usleep(10);

  do {
    res_uart = HAL_uart_rx(0, &ud.uart_rx_buf, &uart_size);
    if(res_uart == true) {

      //update_pstats_rx_raw_counter();

      pkt_rx = get_pkt(pq_size);
      if(!C_ASSERT(pkt_rx != NULL) == true) {
        //update_pstats_rx_err_counter();
        return ;
      }

      bool res_unpack_PQ = unpack_PQ9_BUS(&ud.uart_rx_buf,
                                          uart_size,
                                          pkt_rx);
      if(res_unpack_PQ == true) {

        //update_pstats_rx_counter(pkt_rx->src_id);

        disable_PQ9_tx();

        route_pkt(pkt_rx);
      } else {
        //update_pstats_rx_err_counter();
      }
      free_pkt(pkt_rx);
    } else {
      rx_tries++;
      usleep(10);
    }
  } while(res_uart == true || rx_tries < TX_RETRIES_NUM);



  if(rx_tries < TX_RETRIES_NUM) {
    //notify_tx_event(pkt_tx);
  } else {
    // add fdir
  }

  pkt_tx->notification_flag = true;
  free_pkt(pkt_tx);

}

void notify_tx_event(pq9_pkt *pkt) {
#if SYSTEM_APP_ID == OBC_APP_ID
//  if(pkt->type == TC_HK_TYPE && pkt->subtype == TM_HK_RESP_SUBTYPE && pkt->src == COMMS_APP_ID) {
//    hk_flag = true;
//  } else if(pkt->type == TC_HK_TYPE && pkt->subtype == TM_HK_RESP_SUBTYPE && pkt->src == COMMS_APP_ID) {
//    hk_tx_flag = true;
//  } else if(pkt->type == TC_HK_TYPE && pkt->subtype == TM_HK_RESP_SUBTYPE && pkt->src == COMMS_APP_ID) {
//    packets_request_flag = true;
//  }
#endif
}

void notify_rx_event(pq9_pkt *pkt) {
#if SYSTEM_APP_ID == EPS_APP_ID
 //obc_rx_time = OSAL_sys_GetTick();
#elif SYSTEM_APP_ID == OBC_APP_ID
// subsys_rx_time[pkt->source] = OSAL_sys_GetTick();
//
// if(pkt->type == TC_HK_TYPE && pkt->subtype == TM_HK_RESP_SUBTYPE && pkt->source == COMMS_APP_ID) {
//   en_ok_flag = true;
// } else if(pkt->type == TC_HK_TYPE && pkt->subtype == TM_HK_RESP_SUBTYPE && pkt->source == COMMS_APP_ID) {
//   en_no_flag = true;
// }
#endif
}
