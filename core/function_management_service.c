#include "function_management_service.h"
#include "satellite.h"
#include "subsystem.h"

#include "housekeeping_service.h"
#include "satellite.h"
#include "subsystem.h"
#include "parameters.h"

#define TC_FM_SET_PARAMETER_SUBTYPE   1
#define TC_FM_GET_PARAMETER_SUBTYPE   2
#define TM_FM_PARAMETER_RESP_SUBTYPE  2

void crt_fm_get_parameter_command(pq9_pkt *pkt, SBSYS_id dest_id) {
  pq9_pkt *resp_pkt;

  resp_pkt = get_pkt(0);
  if(!C_ASSERT(resp_pkt != NULL) == true) {
    return ;
  }

  crt_pkt(resp_pkt, dest_id, TC_FM_TYPE, TC_FM_SET_PARAMETER_SUBTYPE, 0);
  queuePush(resp_pkt, 0);
}

void crt_fm_set_parameter_request(pq9_pkt *pkt, SBSYS_id dest_id) {
  pq9_pkt *resp_pkt;

  resp_pkt = get_pkt(0);
  if(!C_ASSERT(resp_pkt != NULL) == true) {
    return ;
  }

  crt_pkt(resp_pkt, dest_id, TC_FM_TYPE, TC_HK_REQ_SUBTYPE, 0);
  queuePush(resp_pkt, 0);
}

void function_management_app(pq9_pkt *pkt) {

  bool res = false;
  bool ack_flag = false;

  if(pkt->subtype == TC_FM_SET_PARAMETER_SUBTYPE) {
    //res = fm_set_parameter(pkt->msg[0], pkt->msg[1], &pkt->msg[2]);

    res = set_parameter(pkt->msg[0], &pkt->msg[1]);

    ack_flag = true;
  } else if(pkt->subtype == TC_FM_GET_PARAMETER_SUBTYPE) {

    pq9_pkt *resp_pkt;
    uint16_t size;

    resp_pkt = get_pkt(0);
    if(!C_ASSERT(resp_pkt != NULL) == true) {
      return ;
    }

    uint32_t val;
    get_parameter(pkt->msg[0], &val, resp_pkt->msg, &size);

    crt_pkt(resp_pkt, pkt->src_id, TC_FM_TYPE, TM_FM_PARAMETER_RESP_SUBTYPE, size);
    queuePush(resp_pkt, 0);

  }

  if(ack_flag) {
    crt_ack_response(pkt, res);
  }

}