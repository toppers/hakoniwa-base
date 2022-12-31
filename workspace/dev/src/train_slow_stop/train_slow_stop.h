#ifndef TRAIN_SLOW_STOP_H_
#define TRAIN_SLOW_STOP_H_
//
// train_slow_stop.h
//

#include "ev3api.h"
#include "stdbool.h"

#include "util.h"
#include "horn.h"
#include "drive_unit.h"
#include "signal_reader.h"
#include "operation_switch.h"

extern void train_init(void);
extern void train_run(void);

#endif // TRAIN_SLOW_STOP_H_
