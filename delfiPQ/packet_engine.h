#ifndef __PACKET_ENGINE_H
#define __PACKET_ENGINE_H

#include "satellite.h"

//needs to redifine
//#define MAX_PKT_LEN         210 /*ECSS_HEADER_SIZE + ECSS_DATA_HEADER_SIZE + MAX_PKT_DATA + ECSS_CRC_SIZE*/

//#define MAX_PKT_DATA        198
//#define TC_MAX_PKT_SIZE     210
//#define TC_MIN_PKT_SIZE     11 //12  /*ECSS_HEADER_SIZE + ECSS_DATA_HEADER_SIZE + ECSS_CRC_SIZE*/

//#define MAX_PKT_SIZE        210


#define UART_BUF_SIZE       300

void PQ9_master();

void PQ9_primary();

void PQ9_beta();

#endif
