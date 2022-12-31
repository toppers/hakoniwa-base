//
//  rotator.c
//

#include "rotator.h"

typedef enum _rotator_state {
    RS_INIT,
    RS_CHECKER_OFF,    // checkerがOFFで回転中
    RS_CHECKER_ON,     // checkerがONで回転中
    RS_STOP,           // 停止中
    TNUM_ROTATOR_STATE
} rotator_state;

static char* state_msg[TNUM_ROTATOR_STATE] = {
    "RS_INIT", "RS_CHKR_OFF", "RS_CHKR_ON", "RS_STOP"
};

static rotator_state rs_state = RS_INIT;
static bool rs_is_entry = true;

#define ENTRY if(rs_is_entry){rs_is_entry=false;
#define DO }{
#define EVTCHK(f,s) if((f)){rs_state=(s);rs_is_entry=true;}
#define EXIT }if(rs_is_entry){
#define END }

static const sensor_port_t checker_port = EV3_PORT_2;
static const sensor_type_t checker_type = TOUCH_SENSOR;

bool checker_is_pushed(void) {
    return ev3_touch_sensor_is_pressed(checker_port);
}

#define ROTATOR_POWER 10
int rotator_power = ROTATOR_POWER;

static const motor_port_t motor_port = EV3_PORT_A;
static const motor_type_t motor_type = LARGE_MOTOR;

static bool rotator_rotating = false;

bool rotator_is_rotated(void) {
    return rs_state == RS_STOP;
}

void rotator_init(void) {
    ev3_sensor_config(checker_port, checker_type);
    ev3_motor_config(motor_port, motor_type);
    rotator_rotating = false;
}

void rotator_rotate(void) {
    rotator_rotating = true;
}

void rotator_stop(void) {
    rotator_rotating = false;
}

void rotator_run(void) {
    if( rs_is_entry ) {
        msg_f(state_msg[rs_state], 3);
    }

    switch(rs_state ) {
    case RS_INIT:
        ENTRY
            rotator_init();
        DO
        EVTCHK(true, RS_CHECKER_OFF)
        EXIT
        END
        break;
    case RS_CHECKER_OFF:
        ENTRY
            rotator_rotating = true;
            ev3_motor_set_power(motor_port, rotator_power);
        DO
        EVTCHK(checker_is_pushed(),RS_CHECKER_ON)
        EXIT
        END
        break;
    case RS_CHECKER_ON:
        ENTRY
            rotator_rotating = true;
            ev3_motor_set_power(motor_port, rotator_power);
        DO
        EVTCHK((!checker_is_pushed()),RS_STOP)
        EXIT
            ev3_motor_stop(motor_port, true);
        END
        break;
    case RS_STOP:
        ENTRY
            rotator_rotating = false;
        DO
        EVTCHK(rotator_rotating,RS_CHECKER_OFF)
        EXIT
        END
        break;
    default:
    case TNUM_ROTATOR_STATE:
        break;
    }
}
