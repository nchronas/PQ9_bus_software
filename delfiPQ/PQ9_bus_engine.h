#ifndef __PQ9_BUS_ENGINE_H
#define __PQ9_BUS_ENGINE_H

#include "satellite.h"
#include <stddef.h>
#include <stdint.h>
#include "satellite_ids.h"

#define PQ9_MASTER_APP_ID _OBC_APP_ID_

typedef struct {
  SBSYS_id dest_id;
  uint8_t size;
  SBSYS_id src_id;
  uint8_t type;
  uint8_t subtype;
  uint16_t packet_counter;
  uint8_t msg[253];

  uint8_t *notification_flag;
}pq9_pkt;

bool is_enabled_PQ9_tx();

void disable_PQ9_tx();

void enable_PQ9_tx();

void PQ9_tx();

bool unpack_PQ9_BUS(const uint8_t *buf,
                    const uint16_t size,
                    pq9_pkt *pq_pkt);

bool pack_PQ9_BUS(pq9_pkt *pq_pkt, uint8_t *buf, uint16_t *size);

#endif
