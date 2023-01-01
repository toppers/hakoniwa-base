//
// train.c
//

#include "train_slow_stop.h"

typedef enum {
    TR_INIT,
    TR_EXIT,
    TR_WAIT_FOR_DEPARTURE1, // 運転開始待ち1
    TR_WAIT_FOR_DEPARTURE2, // 運転開始待ち2
    TR_FORWARDING,          // 前進中
    TR_SLOW_DOWN,           // 減速走行中
    TR_STOP,
    TNUM_TRAIN_STATE
} train_state;

static char* state_msg[TNUM_TRAIN_STATE] = {
    "INIT", "EXIT", "W_F_DEP1","W_F_DEP2",
    "FORWARDING", "SLOW_DOWN", "STOP"
};

static train_state tr_state = TR_INIT;
static bool tr_is_entry = true;


#define ENTRY if(tr_is_entry){tr_is_entry=false;
#define DO }{
#define EVTCHK(f,s) if((f)){tr_state=(s);tr_is_entry=true;}
#define EXIT }if(tr_is_entry){
#define END }

void train_init(void) {
    drive_unit_init();
    signal_reader_init();
    operation_switch_init();
    tr_state = TR_INIT;
    tr_is_entry = true;
}

bool train_signal_is_stop(void) {
    return signal_reader_get_signal() == SIGNAL_STOP;
}

bool train_signal_is_slow_down(void) {
    return signal_reader_get_signal() == SIGNAL_REDUCE;
}

bool train_signal_is_departure(void) {
    return signal_reader_get_signal() == SIGNAL_DEPARTURE;
}

void train_run(void) {
    if( tr_is_entry ) {
        msg_f(state_msg[tr_state], 2);
    }

    switch( tr_state ) {
    case TR_INIT:
        ENTRY
            train_init();
        DO
        EVTCHK(true,TR_WAIT_FOR_DEPARTURE1);
        EXIT
        END
        break;
    case TR_WAIT_FOR_DEPARTURE1:
        ENTRY
            ev3_led_set_color(LED_ORANGE);
            horn_warning();
        DO
        EVTCHK(operation_switch_is_pushed(),TR_WAIT_FOR_DEPARTURE2)
        EXIT
        END
        break;
    case TR_WAIT_FOR_DEPARTURE2:
        ENTRY
        DO
        EVTCHK((!operation_switch_is_pushed()),TR_FORWARDING)
        EXIT
        END
        break;
    case TR_FORWARDING:
        ENTRY
            ev3_led_set_color(LED_GREEN);
            horn_confirmation();
            drive_unit_set_power(DRIVE_UNIT_POWER);
            drive_unit_forward();
        DO
        EVTCHK(train_signal_is_slow_down(),TR_SLOW_DOWN)
        EVTCHK(train_signal_is_stop(),TR_STOP)
        EVTCHK(operation_switch_is_pushed(),TR_EXIT)
        EXIT
        END
        break;
    case TR_SLOW_DOWN:
        ENTRY
            ev3_led_set_color(LED_ORANGE);
            drive_unit_set_power(DRIVE_UNIT_SLOW_POWER);
            drive_unit_forward();
            horn_warning();
        DO
        EVTCHK(train_signal_is_stop(),TR_STOP)
        EVTCHK(train_signal_is_departure(),TR_FORWARDING)
        EVTCHK(operation_switch_is_pushed(),TR_EXIT)
        EXIT
        END
        break;
    case TR_STOP:
        ENTRY
            drive_unit_stop();
            ev3_led_set_color(LED_RED);
            horn_arrived();
        DO
        EVTCHK(train_signal_is_departure(),TR_FORWARDING)
        EVTCHK(operation_switch_is_pushed(),TR_EXIT)
        EXIT
        END
        break;
    case TR_EXIT:
        ENTRY
            drive_unit_stop();
            ev3_led_set_color(LED_ORANGE);
            horn_warning();
        DO
        EXIT
        END
        break;
    default:
    case TNUM_TRAIN_STATE:
        break;
    }
}
