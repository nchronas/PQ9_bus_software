#ifndef __SUBSYSTEM_POOL_H
#define __SUBSYSTEM_POOL_H

#include "satellite.h"
#include "queue.h"
#include "PQ9_bus_engine.h"

void subsystem_queue_init();

struct _queue * get_subsystem_queue(pool_id id);

#endif
