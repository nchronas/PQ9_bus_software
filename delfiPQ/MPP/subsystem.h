#ifndef __SUBSYSTEM_H
#define __SUBSYSTEM_H

#include "satellite.h"
#include "packet_engine.h"
#include "satellite_ids.h"
#include "PQ9_bus_engine.h"
#include "MPP_Board.h"

#define SYSTEM_APP_ID _MPP_APP_ID_

void route_pkt(pq9_pkt *pkt);

#endif
