//
//  signal_display.c
//

#include "signal_display.h"

typedef enum _signal_display_state {
    SD_INIT,
    SD_WAIT_FOR_STOP,     // 停止へ切替中
    SD_STOP,              // 停止現示中
    SD_WAIT_FOR_DEP,      // 進行へ切替中
    SD_DEPARTURE,         // 進行現示中
    TNUM_SIGNAL_DISPLAY_STATE
} signal_display_state;

static char* state_msg[TNUM_SIGNAL_DISPLAY_STATE] = {
    "SD_INIT",
    "SD_W_F_STOP", "SD_STOP",
    "SD_W_F_DEP", "SD_DEPARTURE"
};

static char* color_name[TNUM_COLOR] = {
    "NONE", "BLACK", "BLUE", "GREEN",
    "YELLOW", "RED", "WHITE", "BROWN"
};

static signal_display_state sd_state = SD_INIT;
static bool sd_is_entry = true;

#define ENTRY if(sd_is_entry){sd_is_entry=false;
#define DO }{
#define EVTCHK(f,s) if((f)){sd_state=(s);sd_is_entry=true;}
#define EXIT }if(sd_is_entry){
#define END }

static const sensor_port_t reader_sensor_port = EV3_PORT_3;
static const sensor_type_t reader_sensor_type = COLOR_SENSOR;

static colorid_t last_color = COLOR_NONE;

signal_type_t signal_display_get_current_signal(void) {
    signal_type_t ret = SIGNAL_NONE;
    switch(last_color) {
    case COLOR_RED:
        ret = SIGNAL_STOP;
        break;
    case COLOR_GREEN:
        ret = SIGNAL_DEPARTURE;
        break;
    default:
        ret = SIGNAL_NONE;
    }
    return ret;
}

typedef enum _signal_display_oparation_t {
    SOP_STOP, SOP_DEP
} signal_display_oparation_t;

static signal_display_oparation_t signal_operation = SOP_STOP;

void signal_display_set_operation_stop(void) {
    signal_operation = SOP_STOP;
}

void signal_display_set_operation_departure(void) {
    signal_operation = SOP_DEP;
}

bool signal_display_is_operation_req_stop(void) {
    return signal_operation == SOP_STOP;
}

bool signal_display_is_operation_req_departure(void) {
    return signal_operation == SOP_DEP;
}

void signal_display_init(void) {
    ev3_sensor_config(reader_sensor_port, reader_sensor_type);
    dly_tsk(500U * 1000U);
    sd_state = SD_INIT;
    signal_operation = SOP_STOP;
}

void signal_display_run(void) {
    if( sd_is_entry ) {
        msg_f(state_msg[sd_state], 2);
    }

    switch( sd_state ) {
    case SD_INIT:
        ENTRY
            signal_display_init();
        DO
        EVTCHK(true, SD_WAIT_FOR_STOP)
        EXIT
        END
        break;
    case SD_WAIT_FOR_STOP:
        ENTRY
            rotator_rotate();
            ev3_led_set_color(LED_ORANGE);
        DO
        EVTCHK(signal_display_is_operation_req_departure(),SD_WAIT_FOR_DEP)
        // manual EVTCHK
            if(rotator_is_rotated()) {
                last_color = ev3_color_sensor_get_color(reader_sensor_port);
                msg_f(color_name[last_color], 4);
                if( last_color == COLOR_RED) {
                    sd_state= SD_STOP;
                    sd_is_entry=true;
                } else {
                    sd_state= SD_WAIT_FOR_STOP;
                    sd_is_entry=true;
                }
            }
        EXIT
        END
        break;
    case SD_STOP:
        ENTRY
            rotator_stop();
            ev3_led_set_color(LED_RED);
        DO
        EVTCHK(signal_display_is_operation_req_departure(),SD_WAIT_FOR_DEP)
        EXIT
        END
        break;
    case SD_WAIT_FOR_DEP:
        ENTRY
            rotator_rotate();
            ev3_led_set_color(LED_ORANGE);
        DO
        EVTCHK(signal_display_is_operation_req_stop(),SD_WAIT_FOR_STOP)
        // manual EVTCHK
            if(rotator_is_rotated()) {
                last_color = ev3_color_sensor_get_color(reader_sensor_port);
                msg_f(color_name[last_color], 4);
                if( last_color == COLOR_GREEN) {
                    sd_state= SD_DEPARTURE;
                    sd_is_entry=true;
                } else {
                    sd_state= SD_WAIT_FOR_DEP;
                    sd_is_entry=true;
                }
            }
        EXIT
        END
        break;
    case SD_DEPARTURE:
        ENTRY
            rotator_stop();
            ev3_led_set_color(LED_GREEN);
        DO
        EVTCHK(signal_display_is_operation_req_stop(),SD_WAIT_FOR_STOP)
        EXIT
        END
        break;
    default:
    case TNUM_SIGNAL_DISPLAY_STATE:
        break;
    }

    rotator_run();

}
