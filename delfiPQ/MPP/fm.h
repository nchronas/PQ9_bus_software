#ifndef __FM_H
#define __FM_H

#include <stdint.h>
#include "satellite.h"

bool fm_set_parameter(param_id pid, FM_fun_id fid, uint8_t *data);

void fm_get_parameter(param_id pid);

#endif
