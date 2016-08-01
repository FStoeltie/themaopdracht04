#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>
#include "pins.h"

void servo_init(int port, int pin);

void servo_pulse(int port, int pin, uint16_t position);

#endif // SERVO_H