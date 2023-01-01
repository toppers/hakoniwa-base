#ifndef ROTATOR_H_
#define ROTATOR_H_
//
//  rotator.h
//

#include "ev3api.h"
#include "stdbool.h"
#include "util.h"

extern void rotator_init(void);
extern void rotator_run(void);
extern void rotator_rotate(void);
extern void rotator_stop(void);
extern bool rotator_is_rotated(void);

#endif // ROTATOR_H_
