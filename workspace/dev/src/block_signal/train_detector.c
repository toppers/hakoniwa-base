//
// train_detector.c
//

#include "train_detector.h"

static const sensor_port_t train_detector_sensor_port = EV3_PORT_4;
static const sensor_type_t train_detector_sensor_type = ULTRASONIC_SENSOR;

#define TD_THRESHOLD 10
static int train_detector_threshold = TD_THRESHOLD;

void train_detector_set_threshold(int threshold) {
  train_detector_threshold = threshold;
}

static int8_t dist_old = 255;

void train_detector_init(void) {
  ev3_sensor_config(train_detector_sensor_port, train_detector_sensor_type);
  dist_old = 0;
}

// このdetectorを使うには cyc0 の周期は100ms以上にする
bool train_detector_is_detected(void) {
    int8_t distance = ev3_ultrasonic_sensor_get_distance(train_detector_sensor_port);

    if( dist_old != distance ) {
        fmt_f("dist=%d", distance, 5);
    }
    dist_old = distance;
    return distance < train_detector_threshold;
}

/***
// int train_detector_detect_count = 0;
***/
/***
  static uint16_t detected = 0;
  static uint16_t detected_old = 0;

  if( distance < train_detector_threshold ) {
    detected = (detected << 1) | 1;
  } else {
    detected = (detected << 1) | 0;
  }
  if( dist_old != distance ) {
    fmt_f("dist=%d", distance, 4);
  }
  if( detected_old != detected ) {
    fmt_f("detected=%04X", detected, 5);
  }
  dist_old = distance;
  detected_old = detected;
  return detected;
***/
