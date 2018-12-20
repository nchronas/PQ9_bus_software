#ifndef __HOUSEKEEPING_SERVICE_H
#define __HOUSEKEEPING_SERVICE_H

#include <stdint.h>
#include "PQ9_bus_engine.h"

void crt_hk_request(SBSYS_id dest_id, uint8_t *flag);

void housekeeping_app(pq9_pkt *pkt);

#endif
