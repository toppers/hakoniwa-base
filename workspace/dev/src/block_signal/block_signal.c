//
// block_signal.c
//

#include "block_signal.h"

typedef enum _block_signal_state {
    BS_INIT,
    BS_TO_STOP,     // 停止表示へ変更中
    BS_STOPPED,     // 停止を現時中
    BS_TO_DEP,      // 進行表示へ変更中
    BS_DEPARTURE,   // 進行を現時中
    TNUM_BLOCK_SIGNAL_STATE
} block_signal_state;

static char* state_msg[TNUM_BLOCK_SIGNAL_STATE] = {
    "BS_INIT", "BS_TO_STOP", "BS_STOPPED",
    "BS_TP_DEP", "BS_DEPARTURE"
};

static block_signal_state bs_state = BS_INIT;
static bool bs_is_entry = true;

#define ENTRY if(bs_is_entry){bs_is_entry=false;
#define DO }{
#define EVTCHK(f,s) if((f)){bs_state=(s);bs_is_entry=true;}
#define EXIT }if(bs_is_entry){
#define END }

bool signal_display_is_stop(void) {
    return signal_display_get_current_signal() == SIGNAL_STOP;
}

bool signal_display_is_departure(void) {
    return signal_display_get_current_signal() == SIGNAL_DEPARTURE;
}

void block_signal_init(void) {
    manual_switch_init();
    train_detector_init();
    dly_tsk(3000U * 1000U);
    horn_confirmation();
    bs_state = BS_INIT;
    bs_is_entry = true;
}

void block_signal_run(void) {
    if( bs_is_entry ) {
        msg_f(state_msg[bs_state], 1);
    }

    switch( bs_state ) {
    case BS_INIT:
        ENTRY
            block_signal_init();
        DO
        EVTCHK(true,BS_TO_STOP)
        EXIT
        END
        break;
    case BS_TO_STOP:
        ENTRY
            signal_display_set_operation_stop();
        DO
        EVTCHK(signal_display_is_stop(),BS_STOPPED)
        // EVTCHK(司令室からの指示を受け取った(),BS_STOPPED)
        EXIT
        END
        break;
    case BS_STOPPED:
        ENTRY
        DO
        EVTCHK(manual_switch_is_pushed(),BS_TO_DEP)
        // EVTCHK(司令室からの指示を受け取った(),BS_TO_DEP)
        EXIT
        END
        break;
    case BS_TO_DEP:
        ENTRY
            signal_display_set_operation_departure();
        DO
        EVTCHK(signal_display_is_departure(),BS_DEPARTURE)
        // EVTCHK(司令室からの指示を受け取った(),BS_DEPARTURE)
        END
        break;
    case BS_DEPARTURE:
        ENTRY
        DO
        EVTCHK(manual_switch_is_pushed(),BS_TO_STOP)
        EVTCHK(train_detector_is_detected(),BS_TO_STOP)
        // EVTCHK(司令室からの指示を受け取った(),BS_TO_STOP)
        EXIT
        END
        break;
    default:
    case TNUM_BLOCK_SIGNAL_STATE:
        break;
    }

    signal_display_run(); // 信号表示部のステートマシンの実行
}
