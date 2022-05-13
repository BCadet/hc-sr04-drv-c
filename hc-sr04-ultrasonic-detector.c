#include "hc-sr04-ultrasonic-detector.h"

void hc_sr04_wait(struct hc_sr04_dev *dev, uint8_t us)
{
    uint32_t now = dev->tick();
    while(dev->tick() < now + us);
}

void hc_sr04_trigger(struct hc_sr04_dev *dev)
{
    dev->trigger(1);
    hc_sr04_wait(dev, 10);
    dev->trigger(0);
    dev->state = HC_SR04_TRIGGERED;
}

void hc_sr04_event(struct hc_sr04_dev *dev, uint8_t event_state)
{
    switch(dev->state)
    {
        case HC_SR04_IDLE:
        case HC_SR04_ECHO_FINISH:
        case HC_SR04_ERROR:
        return;

        case HC_SR04_TRIGGERED:
            if(event_state == 1)
            {
                dev->echo_start = dev->tick();
                dev->state = HC_SR04_ECHO_START;
            }
            else
            {
                dev->state = HC_SR04_ERROR;
            }
        break;
        
        case HC_SR04_ECHO_START:
            if(event_state == 0)
            {
                dev->echo_end = dev->tick();
                dev->state = HC_SR04_ECHO_FINISH;
            }
            else
            {
                dev->state = HC_SR04_ERROR;
            }
        break;
    }
}

uint8_t hc_sr04_get_distance(struct hc_sr04_dev *dev, float *dist)
{
    if(dev->state == HC_SR04_ECHO_FINISH)
    {
        uint32_t delta = dev->echo_end - dev->echo_start;
        *dist = (float)(delta) / 58.0f;
    }
    return dev->state;
}