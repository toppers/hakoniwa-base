#ifndef MANUAL_SWITCH_H_
#define MANUAL_SWITCH_H_
//
// manual_switch.h
//

#include "ev3api.h"
#include "stdbool.h"

extern void manual_switch_init(void);
extern bool manual_switch_is_pushed(void);

#endif // MANUAL_SWITCH_H_
