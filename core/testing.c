#include "testing.h"
#include "satellite.h"

#include <stdbool.h>

bool master_loop_flag = true;

void testing_fn(uint8_t subtype) {

#ifdef DEBUG
  if(subtype == TC_TST_FREEZE) {
      master_loop_flag = false;
    while(1) {

    }
  } else if(subtype == TC_TST_STARTM) {
    master_loop_flag = true;
  } else if(subtype == TC_TST_STOPM) {
    master_loop_flag = false;
  }
#endif
}
