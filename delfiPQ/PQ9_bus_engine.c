#include "PQ9_bus_engine.h"
#include "subsystem.h"
#include "hal_functions.h"

#define CRC_POLY 0x1021

uint16_t packet_counter = 0;

/**** CRC calculator ****/
uint16_t crc_PQ9(uint16_t crc1, uint8_t data, uint16_t poly) {

    for (unsigned char i = 0; i < 8; i++)
    {
      if (((( crc1 & 0x8000) >> 8) ^ (data & 0x80)) != 0)
      {
        crc1 <<= 1;
        crc1 ^= poly;
      }
      else
      {
        crc1 <<= 1;
      }
      data <<= 1;
    }
    return crc1;
}

uint16_t calculate_crc_PQ9(uint8_t *buf, const uint16_t size) {

  if(!C_ASSERT(buf != NULL) == true) {
    return true;
  }

  if(!C_ASSERT(size != NULL) == true) {
    return true;
  }

  uint16_t val = 0xFFFF;

  for(uint16_t i = 0; i < size; i++) {
    val = crc_PQ9(val, buf[i], 0x1021);
  }

  return val;
}

uint8_t get_subs_addr() {
  return (uint8_t)SYSTEM_APP_ID;
}

static bool pq9_tx_flag = false;

bool is_enabled_PQ9_tx() {
  return pq9_tx_flag;
}

void enable_PQ9_tx() {
  pq9_tx_flag = true;
}

void PQ9_tx() {
  if(pq9_tx_flag == true) {
    HAL_PQ9_BUS_enable_tx();
    #if(SYSTEM_APP_ID == PQ9_MASTER_APP_ID)
      //HAL_reset_PQ9_rx();
    #endif
  }
}

void disable_PQ9_tx() {
  pq9_tx_flag = false;
  HAL_PQ9_BUS_disable_tx();
}

bool unpack_PQ9_BUS(const uint8_t *buf,
                    const uint16_t size,
                    pq9_pkt *pq_pkt) {

  pq_pkt->dest_id = buf[0];
  pq_pkt->size = buf[1];
  pq_pkt->src_id = buf[2];
  cnv8_16LE(&buf[3], &pq_pkt->packet_counter);
  pq_pkt->type = buf[5];
  pq_pkt->subtype = buf[6];

  if(pq_pkt->size != size - 5) {
    return false;
  }

  if(pq_pkt->dest_id != SYSTEM_APP_ID) {
   // return false;
  }

  uint16_t crc_calc = calculate_crc_PQ9(buf, size - 2);
  uint16_t crc_pkt = 0;

  cnv8_16LE(&buf[size-2], &crc_pkt);

  if(crc_calc != crc_pkt) {
    return false;
  }

  pq_pkt->size -= 2; //type and subtype
  pq_pkt->size -= 2; //packet counter
  memcpy(pq_pkt->msg, &buf[7], pq_pkt->size);

  return true;
}

bool pack_PQ9_BUS(pq9_pkt *pq_pkt, uint8_t *buf, uint16_t *size) {

  if(!C_ASSERT(pq_pkt != NULL) == true) {
    return false;
  }

  if(!C_ASSERT(buf != NULL) == true) {
    return false;
  }

  if(!C_ASSERT(size != NULL) == true) {
    return false;
  }

#if(SYSTEM_APP_ID == PQ9_MASTER_APP_ID)
  if(pq_pkt->dest_id == PQ9_MASTER_APP_ID) {
    //return false;
  }
#else
  if(pq_pkt->dest_id != PQ9_MASTER_APP_ID) {
    //return false;
  }
#endif

  pq_pkt->src_id = SYSTEM_APP_ID;

  if(!C_ASSERT(pq_pkt->src_id != pq_pkt->dest_id) == true) {
    //return false;
  }

  *size = pq_pkt->size + 3; //header

  *size += 2; //type and subtype

  packet_counter++;

  buf[0] = pq_pkt->dest_id;
  buf[1] = pq_pkt->size;
  buf[2] = pq_pkt->src_id;
  cnv16_8(packet_counter, &buf[3]);
  buf[5] = pq_pkt->type;
  buf[6] = pq_pkt->subtype;

  memcpy(&buf[7], pq_pkt->msg, pq_pkt->size-2);

  uint16_t crc = calculate_crc_PQ9(buf, *size-2);
  cnv16_8(crc, &buf[*size-2]);

  return true;
}

crt_pkt(pq9_pkt *pq_pkt, SBSYS_id id, uint8_t type, uint8_t subtype, uint8_t size, uint8_t *flag) {

  pq_pkt->dest_id = id;
  pq_pkt->size = size + 2 + 2; //type and subtype + packet counter
  pq_pkt->src_id = SYSTEM_APP_ID;
  pq_pkt->type = type;
  pq_pkt->subtype = subtype;
  pq_pkt->notification_flag = flag;

}
