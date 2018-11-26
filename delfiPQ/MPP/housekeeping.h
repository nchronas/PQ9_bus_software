#ifndef __HOUSEKEEPING_H
#define __HOUSEKEEPING_H

#include <stdint.h>
#include "subsystem.h"

void populate_housekeeping(uint8_t *buf, uint8_t *pkt_size);
void store_housekeeping(SBSYS_id id, uint8_t *buf, uint16_t size);
void retrieve_housekeeping(SBSYS_id id, uint8_t *buf, uint16_t *size);

#endif
