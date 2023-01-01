#ifndef TRAIN_DETECTOR_H_
#define TRAIN_DETECTOR_H_

#include "ev3api.h"
#include "stdbool.h"
#include "util.h"

extern void train_detector_init(void);
extern void train_detector_set_threshold(int threshold);
extern bool train_detector_is_detected(void);

#endif // TRAIN_DETECTOR_H_
