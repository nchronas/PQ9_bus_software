#include "fm.h"

#include "hal_functions.h"
#include "hal_subsystem.h"
#include "subsystem.h"

bool fm_set_parameter(param_id pid, FM_fun_id fid, uint8_t *data) {

    bool res = false;

    if(fid == P_ON || pid == P_OFF) {
      res = set_parameter(pid, fid);
    } else if(pid == SET_VAL) {
      res = set_parameter(pid, *data);
    }

    return res;
}

void fm_get_parameter(param_id pid) {


}
