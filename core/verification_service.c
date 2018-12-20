#include "verification_service.h"
#include "satellite.h"
#include "subsystem.h"

#include "housekeeping_service.h"
#include "satellite.h"
#include "subsystem.h"

void crt_ack_response(SBSYS_id dest_id, bool status) {
  pq9_pkt *resp_pkt;

  resp_pkt = get_pkt(0);
  if(!C_ASSERT(resp_pkt != NULL) == true) {
    return ;
  }

  uint8_t subtype;

  if(status) {
    subtype = TM_ACK_OK_SUBTYPE;
  } else {
    subtype = TM_ACK_ERROR_SUBTYPE;
  }

  crt_pkt(resp_pkt, dest_id, TC_VER_TYPE, subtype, 0, NULL);
  queuePush(resp_pkt, RS_POOL_ID);
}

void verification_app(pq9_pkt *pkt) {

}
