#include "app.h"
#include "train_slow_stop.h"

void main_task(intptr_t unused) {
    static bool is_initialized = false;
    if(! is_initialized ) {
        init_f("train_slow_stop");
    is_initialized = true;
    }

    train_run();
    ext_tsk();
}
