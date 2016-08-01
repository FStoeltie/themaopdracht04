// blink a LED on pin PIO1_4
//
// This is a very simple blink-a-LED application.
// It aims to show direct use of the hardware rather than
// good programming practices (like abstracting from the GPIO pin
// used and using a timer for the delay).
//
// It uses the CMSIS header file to access the direction
// and value registers for pin GPIO1_4.
// It uses a busy-wait for the delay, which can be affected
// by the compiler and optimization settings used.
//
// Note that after a reset the GPIO1_4 pin is automatically
// configured as GPIO, hence there is no need to configure
// the pin. Some other pins are NOT configured to GPIO by a reset,
// hence blinking on such a pin requires the additional step of
// configuring the pin as GPIO.
//

// includes the cmsis definitions for the LPC1114
#include "bmptk.h"
#include "timer.h"
#include "sw-uart.h"

#include "pins.h"
#include "75HC595.h"
int delay_time = 1000000;
int active_test = 0x00;
int active_test2;
char rray[2] = {0x00, 0x00};
char active_button = 0;
char numbers[10] = {0x18, 0xBB, 0x94, 0x91, 0x33, 0x51, 0x50, 0x9B, 0x10, 0x11}; //0xFC
char read_one_key(int column, int row)  {
    if(row == 1)    {
        active_test = 0xE0;
    }
    else    if(row == 2)    {
        active_test = 0xD0;
    }
    else    if(row == 3)    {
        active_test = 0xB0;
        //active_test = 0xD0;
    }
    else    if(row == 4)    {
        active_test = 0x10;
    }
    //active_test = 0x00;
    rray[1] &= 0x0F;
    rray[1] |= active_test; 
    //rray[1] = 0x00; 
    write_registers(rray, 2);
    //delay(10);
    
    if(!pin_get(0, column + 3)) {
        return 1;
    }
    return 0;
    
}
char keypad_read()  {
    if(read_one_key(1, 1))  {
        return '1';
    }
    if(read_one_key(1, 2))  {
        return '4';
    }
    if(read_one_key(1, 3))  {
        return '7';
    }
    if(read_one_key(1, 4))  {
        return '*';
    }
    if(read_one_key(2, 1))  {
        return '2';
    }
    if(read_one_key(2, 2))  {
        return '5';
    }
    if(read_one_key(2, 3))  {
        return '8';
    }
    if(read_one_key(2, 4))  {
        return '0';
    }
    if(read_one_key(3, 1))  {
        return '3';
    }
    if(read_one_key(3, 2))  {
        return '6';
    }
    if(read_one_key(3, 3))  {
        return '9';
    }
    if(read_one_key(3, 4))  {
        return '#';
    }
    return 0;
}
void set_timer(int number)    {
    
}
int c_countdown = 0;
char old_not_set = 0;
void count()    {
    
    
    int i = 0;
    rray[1] = 0xFF;
    for(; i <= 9; i++)   {
        int j = 0;
        for(; j <= 9; j++)  {
            int wait_time = now() + delay_time;
            while(now() < wait_time)    {
                active_test = 0x60;
                char old_active_button = active_button;
                active_button = keypad_read();
                
                if(active_button != old_active_button)  {   // new button pressed
                    if(old_not_set == 0) {
                        c_countdown = active_button - 48;
                       
                    }
                    else {
                        c_countdown *= 10;
                        i = c_countdown;
                        j = active_button - 48;
                        c_countdown += active_button - 48;
                        
                        
                    }
                }
                
                /*if(active_test == 0x10) {
                    active_test = ~0x20;
                    int i = 4;
                    for(; i <= 7; i++)  {
                        if(!pin_get(0, i))   {
                            uart_put_string( "pressed a button...\n" );
                        }
                    }
                }
                else if(active_test == 0x20)    {
                    active_test = ~0x40;
                    int i = 4;
                    for(; i <= 7; i++)  {
                        if(!pin_get(0, i))   {
                            uart_put_string( "pressed a button...\n" );
                        }
                    }
                }
                else {
                    active_test = ~0x10;
                    int i = 4;
                    for(; i <= 7; i++)  {
                        if(!pin_get(0, i))   {
                            uart_put_string( "pressed a button...\n" );
                        }
                    }
                }*/
                rray[1] = 0x01 | active_test;
                delay(10);
                rray[0] = numbers[i];
                write_registers(rray, 2);
                
                rray[1] = 0x02 | active_test;
                delay(10);
                
                rray[0] = numbers[j];
                write_registers(rray, 2);
                
            }
        }
    }
}
void reading_matrix1()  {
    pin_configure_as_input(0, 4);
    pin_configure_as_input(0, 5);
    pin_configure_as_input(0, 6);
    pin_configure_as_input(0, 7);
}
int delaytime = 5;
void spi_test() {
    timer_init();
    uart_init(); 
    configure_pin_layout(1, 4, 8, 9);
    
    pin_set(0, 7, 1);
    pin_set(0, 6, 0);
    uart_put_string( "Starting programsdf...\n" );
    char rray[2] = {0x00, 0x00};
    char numbers[10] = {0x18, 0xBB, 0x94, 0x91, 0x33, 0x51, 0x50, 0x9B, 0x10, 0x11}; //0xFC
    write_registers(rray, 2);
    for(;;) {
        count();
    }
}
int main( void ){	
    spi_test();
}