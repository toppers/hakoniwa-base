#ifndef BLOCK_SIGNAL_H_
#define BLOCK_SIGNAL_H_
//
// block_signal.h
//

#include "ev3api.h"
#include "stdbool.h"

#include "util.h"
#include "timer.h"
#include "horn.h"
#include "signal_display.h"
#include "train_detector.h"
#include "manual_switch.h"

extern void block_signal_init(void);
extern void block_signal_run(void);

#endif // BLOCK_SIGNAL_H_

