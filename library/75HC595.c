#include "75HC595.h"
#include "timer.h"
#include "sw-uart.h"
unsigned int port;
unsigned int DS_pin;
unsigned int STCP_pin;
unsigned int SHCP_pin;

#define LOW 0
#define HIGH 1

void configure_pin_layout(unsigned int cfg_port, unsigned int cfg_DS_pin, 
unsigned int cfg_STCP_pin, unsigned int cfg_SHCP_pin)   {
    port        = cfg_port;
    DS_pin      = cfg_DS_pin;
    STCP_pin    = cfg_STCP_pin;
    SHCP_pin    = cfg_SHCP_pin;
	
	pin_configure_as_output(port, DS_pin);
    pin_configure_as_output(port, STCP_pin);
    pin_configure_as_output(port, SHCP_pin);
    //write_registers();
}
void write_registers(unsigned char* register_values, unsigned int size)   {
    int i = 0;
    pin_set(port, STCP_pin, LOW); 
    for(; i < size; i++)    {
        int j = 7;
        for(; j >= 0; j--)   {
            unsigned char pin_value = ( (char)0x80 & ( (*(register_values + i)) << j ) );
			pin_value = pin_value >> 7;
			//uart_put_char((char)(48 + pin_value));
            pin_set(port, SHCP_pin, LOW);
            pin_set(port, DS_pin, pin_value);
            pin_set(port, SHCP_pin, HIGH);
			delay(10);
        }
    }
	//uart_put_char('\n');
    pin_set(port, STCP_pin, HIGH);
}