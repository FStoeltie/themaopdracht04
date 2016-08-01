#ifndef H_75HC595
#define H_75HC595
#include "pins.h"

extern unsigned int port;
extern unsigned int DS_pin;
extern unsigned int STCP_pin;
extern unsigned int SHCP_pin;


void configure_pin_layout(unsigned int port, unsigned int DS_pin, unsigned int STCP_pin, unsigned int SHCP_pin);
void write_registers(unsigned char* register_values, unsigned int size);
#endif //    H_75HC595