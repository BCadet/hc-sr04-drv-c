#ifndef HC_SR04_ULTRASONIC_DETECTOR_H
#define HC_SR04_ULTRASONIC_DETECTOR_H

#include <stdint.h>

typedef uint32_t (*hc_sr04_tick_fptr)(void);
typedef void (*hc_sr04_trigger_fptr)(uint8_t state);

enum hc_sr04_state {
    HC_SR04_IDLE,
    HC_SR04_TRIGGERED,
    HC_SR04_ECHO_START,
    HC_SR04_ECHO_FINISH,
    HC_SR04_ERROR,
};

struct hc_sr04_dev {
    enum hc_sr04_state state;

    uint32_t echo_start;
    uint32_t echo_end;

    hc_sr04_tick_fptr tick;
    hc_sr04_trigger_fptr trigger;
};

#endif /* HC_SR04_ULTRASONIC_DETECTOR_H */
