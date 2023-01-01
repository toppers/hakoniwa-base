//
//  drive_unit.c
//

#include "drive_unit.h"

static int drive_unit_power = DRIVE_UNIT_POWER;

static const motor_port_t drive_unit_motor_port = EV3_PORT_A;
static const motor_type_t drive_unit_motor_type = MEDIUM_MOTOR;

void drive_unit_init(void) {
    ev3_motor_config(drive_unit_motor_port, drive_unit_motor_type);
    drive_unit_power = DRIVE_UNIT_POWER;
}

void drive_unit_set_power(int power) {
    drive_unit_power = power;
}

void drive_unit_stop(void) {
    // ev3_motor_stop(drive_unit_motor_port, true);
    // ev3_motor_stop(drive_unit_motor_port, false);
    ev3_motor_reset_counts(drive_unit_motor_port);
    ev3_motor_stop(drive_unit_motor_port, false);
    int32_t count = ev3_motor_get_counts(drive_unit_motor_port);
    ev3_motor_rotate(drive_unit_motor_port, count * 2, drive_unit_power, true);
}

void drive_unit_forward(void) {
    ev3_motor_set_power(drive_unit_motor_port, drive_unit_power);
}

void drive_unit_back(void) {
    ev3_motor_set_power(drive_unit_motor_port, -drive_unit_power);
}
