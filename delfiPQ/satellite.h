#ifndef __SATELLITE_H
#define __SATELLITE_H

#include "satellite_ids.h"
#include <stdbool.h>
#include <stddef.h>

//#define C_ASSERT(e)    ((e) ? (true) : (services_error_handler(__FILE_ID__, __LINE__, #e)))
#define C_ASSERT(e)    ((e) ? (true) : (services_error_handler(1, 1, #e)))


#define PKT_TIMEOUT 60000 /*in mseconds*/
#define PKT_NORMAL  198   /*MAX_PKT_DATA*/

#define POOL_PKT_SIZE    4

#define MAX_APP_ID      20
#define MAX_SERVICES    20
#define MAX_SUBTYPES    26

#define TC_FM_TYPE    1
#define TC_HK_TYPE    3
#define TC_VER_TYPE   4
#define TC_EN_TYPE    5
#define TC_STATS_TYPE 6
#define TC_PING_TYPE 17
#define TC_TESTING_TYPE 21

#define TC_FM_GET_PARAMETER_SUBTYPE   1
#define TM_FM_PARAMETER_RESP_SUBTYPE  2
#define TC_FM_SET_PARAMETER_SUBTYPE   3

#define TC_HK_REQ_SUBTYPE  1
#define TM_HK_RESP_SUBTYPE 2
#define TM_HK_RF_SUBTYPE   6

#define TM_ACK_OK_SUBTYPE    2
#define TM_ACK_ERROR_SUBTYPE 4

#define TC_EN_REQ_SUBTYPE    1
#define TM_EN_RESP_SUBTYPE   2
#define TM_EN_EMPTY_SUBTYPE  5

#define TC_TST_FREEZE    6
#define TC_TST_STARTM    7
#define TC_TST_STOPM     8

#define TC_STATS_REQ_SUBTYPE    1
#define TM_STATS_RESP_SUBTYPE   2

#define TC_PING_REQ_SUBTYPE  1
#define TM_PING_RESP_SUBTYPE 2

typedef enum {
    EPS_APP_ID      = _EPS_APP_ID_,
    COMMS_APP_ID    = _COMMS_APP_ID_,
    OBC_APP_ID      = _OBC_APP_ID_,
    ADCS_APP_ID     = _ADCS_APP_ID_,
    MPP_APP_ID      = _MPP_APP_ID_,
    ADB_APP_ID      = _ADB_APP_ID_,
    GND_APP_ID      = _GND_APP_ID_,
    DBG_APP_ID      = _DBG_APP_ID_,
    EGSE_APP_ID     = _EGSE_APP_ID_,
    LAST_APP_ID     = _LAST_APP_ID_
}SBSYS_id;

typedef enum {
    EPS_DEV_ID              =  1,
    COMMS_DEV_ID            =  2,
    ADCS_DEV_ID             =  3,
    OBC_DEV_ID              =  4,
    ADB_DEV_ID              =  5,
    EPS_BUS_DEV_ID          =  6,
    ADB_BUS_DEV_ID          =  7,
    COMMS_BUS_DEV_ID        =  8,
    ADCS_BUS_DEV_ID         =  9,
    OBC_BUS_DEV_ID          = 10,
    EPS_DBG_DEV_ID          = 11,
    COMMS_DBG_DEV_ID        = 12,
    ADCS_DBG_DEV_ID         = 13,
    ADB_DBG_DEV_ID          = 14,
    OBC_DBG_DEV_ID          = 15,
    EPS_V1_MON_DEV_ID       = 16,
    EPS_V2_MON_DEV_ID       = 17,
    EPS_V3_MON_DEV_ID       = 18,
    EPS_V4_MON_DEV_ID       = 19,
    EPS_DC_MON_DEV_ID       = 20,
    EPS_UR_MON_DEV_ID       = 21,
    SOL_YP_MON_DEV_ID       = 22,
    SOL_YM_MON_DEV_ID       = 23,
    SOL_XP_MON_DEV_ID       = 24,
    SOL_XM_MON_DEV_ID       = 25,
    SOL_YP_TEMP_DEV_ID      = 26,
    SOL_YM_TEMP_DEV_ID      = 27,
    SOL_XP_TEMP_DEV_ID      = 28,
    SOL_XM_TEMP_DEV_ID      = 29,
    BATT_CHARGE_DEV_ID      = 30,
    EPS_FRAM_DEV_ID         = 31,
    ADB_MON_DEV_ID          = 32,
    ADB_TEMP_DEV_ID         = 33,
    OBC_MON_DEV_ID          = 34,
    OBC_TEMP_DEV_ID         = 35,
    OBC_FRAM_DEV_ID         = 36,
    ADCS_1_MON_DEV_ID       = 37,
    ADCS_2_MON_DEV_ID       = 38,
    ADCS_3_MON_DEV_ID       = 39,
    ADCS_4_MON_DEV_ID       = 40,
    ADCS_TEMP_DEV_ID        = 41,
    ADCS_FRAM_DEV_ID        = 42,
    EPS_POWERLINES_DEV_ID   = 43,
    EPS_INT_TEMP_DEV_ID     = 44,
    ADB_DEP_DEV_ID          = 45,
    ADB_INT_TEMP_DEV_ID     = 46,
    ADCS_INT_TEMP_DEV_ID    = 47,
    OBC_INT_TEMP_DEV_ID     = 48,
    COMMS_TEMP_DEV_ID       = 49,
    COMMS_ADC_DEV_ID        = 50,
    COMMS_RF_TX_DEV_ID      = 51,
    COMMS_RF_RX_DEV_ID      = 52,
    COMMS_RF_CTRL_DEV_ID    = 53,
    INT_WDG_DEV_ID          = 54,
    LAST_DEV_ID             = 55
}dev_id;

typedef enum {
    /* EPS */
    bus1_current_threshold_param_id    =  0,
    bus2_current_threshold_param_id    =  1,
    bus3_current_threshold_param_id    =  2,
    bus4_current_threshold_param_id    =  3,

    EPS_boot_counter_param_id          =  4,

    bus1_power_switch_state_param_id   =  5,
    bus2_power_switch_state_param_id   =  6,
    bus3_power_switch_state_param_id   =  7,
    bus4_power_switch_state_param_id   =  8,
    bus_power_switches_param_id        =  9,

    testing_2_param_id                 =  10,
    testing_4_param_id                 =  11,

    bus1_current_param_id              =  12,
    bus2_current_param_id              =  13,
    bus3_current_param_id              =  14,
    bus4_current_param_id              =  15,

    bus1_voltage_param_id              =  16,
    bus2_voltage_param_id              =  17,
    bus3_voltage_param_id              =  18,
    bus4_voltage_param_id              =  19,

    sol1_current_param_id              =  20,
    sol2_current_param_id              =  21,
    sol3_current_param_id              =  22,
    sol4_current_param_id              =  23,

    sol1_voltage_param_id              =  24,
    sol2_voltage_param_id              =  25,
    sol3_voltage_param_id              =  26,
    sol4_voltage_param_id              =  27,

    sol1_temp_param_id                 =  28,
    sol2_temp_param_id                 =  29,
    sol3_temp_param_id                 =  30,
    sol4_temp_param_id                 =  31,

    batt_voltage_param_id              =  32,
    batt_temp_param_id                 =  33,
    batt_capacity_param_id             =  34,

    internal_current_param_id          =  35,
    internal_voltage_param_id          =  36,

    unregulated_current_param_id       =  37,
    unregulated_voltage_param_id       =  38,

    eps_uptime_param_id                =  39,

    eps_sensor_status_param_id         =  40,

    eps_int_temp_param_id              =  41,

    eps_testing_4_rw_param_id          =  42,

    bus1_power_switch_enabled_param_id =  43,
    bus2_power_switch_enabled_param_id =  44,
    bus3_power_switch_enabled_param_id =  45,
    bus4_power_switch_enabled_param_id =  46,

    adb_int_temp_param_id              =  47,
    adb_sensor_status_param_id         =  48,
    adb_deb_param_id                   =  49,

    adcs_int_temp_param_id             =  50,
    adcs_sensor_status_param_id        =  51,
    ADCS_boot_counter_param_id         =  52,

    obc_int_temp_param_id              =  53,
    obc_sensor_status_param_id         =  54,
    OBC_boot_counter_param_id          =  55,

    red_uptime_param_id                =  56,

    comms_uptime_param_id              =  57,
    comms_sensor_status_param_id       =  58,

    SBSYS_reset_cmd_int_wdg_param_id   =  59,
    SBSYS_reset_clr_int_wdg_param_id   =  60,

    SBSYS_sensor_loop_param_id         =  61,
    Master_command_loop_param_id       =  62,

    LAST_param_id                      =  63
}param_id;

typedef enum {
    TEST_VAULT_ID           =  0,
    LAST_VAULT_ID           =  1
}vault_id;

typedef enum {
    TEST_MON_ID             =  0,
    LAST_MON_ID             =  1
}mon_id;

typedef enum {
    P_OFF       = 0,
    P_ON        = 1,
    SET_VAL     = 2,
    LAST_FUN_ID = 3
}FM_fun_id;

typedef enum {
    HEALTH_REP      = 1,
    LAST_STRUCT_ID  = 2
}HK_struct_id;

typedef enum {
    SATR_OK                    = 0,
    SATR_ERROR                 = 1,
    SATR_EOT                   = 2,
    SATR_PKT_INIT              = 3,

    /*LAST*/
    SATR_LAST                  = 3
}SAT_returnState;

typedef enum {
    RS_POOL_ID              =  0,
    RF_POOL_ID              =  1,
    LAST_POOL_ID            =  2
}pool_id;

#endif
