#include "app.h"
#include "block_signal.h"

void main_task(intptr_t unused) {
    static bool is_initialized = false;
    if(! is_initialized ) {
        init_f("block_signal");
        // manual_switch_init();
        // train_detector_init();
        is_initialized = true;
    }

    block_signal_run();

    /*** for rotator test
    rotator_run();
    if(manual_switch_is_pushed()) {
        rotator_rotate();
    }
    ***/

    // for train_detector test
    // train_detector_is_detected();

    /*** for signal_display test
    signal_display_run();
    if(manual_switch_is_pushed()) {
        signal_type_t signal = signal_display_get_current_signal();
        switch(signal) {
        case SIGNAL_STOP:
            signal_display_set_operation_departure();
            break;
        case SIGNAL_DEPARTURE:
            signal_display_set_operation_stop();
            break;
        default:
            break;
        }
    }
    ***/

    ext_tsk();
}
