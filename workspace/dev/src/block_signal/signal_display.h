#ifndef SIGNAL_DISPLAY_H_
#define SIGNAL_DISPLAY_H_
//
//  signal_display.h
//

#include "ev3api.h"
#include "stdbool.h"
#include "rotator.h"
#include "util.h"

// 信号の種類
// 当座は進行と停止だけ
typedef enum _signal_type_t {
    SIGNAL_NONE,       // 未定
    SIGNAL_STOP,       // 停止
    SIGNAL_DEPARTURE,  // 進行
    SIGNAL_REDUCE,     // 減速
    SIGNAL_CAUTION,    // 注意
    SIGNAL_ALERT,      // 警戒
    TNUM_SIGNAL
} signal_type_t;

extern void signal_display_init(void);
extern void signal_display_run(void);
extern void signal_display_set_operation_departure(void);
extern void signal_display_set_operation_stop(void);
extern signal_type_t signal_display_get_current_signal(void);

#endif
