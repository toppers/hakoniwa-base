//
// manual_switch.c
//

#include "manual_switch.h"

static const sensor_port_t manual_switch_sensor_port = EV3_PORT_1;
static const sensor_type_t manual_switch_sensor_type = TOUCH_SENSOR;

static bool saved = false;

void manual_switch_init(void) {
    saved = false;
    ev3_sensor_config(manual_switch_sensor_port, manual_switch_sensor_type);
}

bool manual_switch_is_pushed(void) {
    return ev3_touch_sensor_is_pressed(manual_switch_sensor_port);
}
