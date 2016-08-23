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
#define SECOND   1000000
#define TIMER_DONE 0
#define DIGIT_ONE 0x01
#define DIGIT_TWO 0x02
int active_test = 0x00;
int active_test2;
char rray[2] = {0x00, 0x00};
char active_button = 0;
char numbers[10] = {0x18, 0xBB, 0x94, 0x91, 0x33, 0x51, 0x50, 0x9B, 0x10, 0x11}; //7 segment dual digit display
char read_one_key(int column, int row)  {
    if(row == 1)    {
        active_test = 0xE0;
    }
    else    if(row == 2)    {
        active_test = 0xD0;
    }
    else    if(row == 3)    {
        active_test = 0xB0;
    }
    else    if(row == 4)    {
        active_test = 0x10;
    }

    rray[1] &= 0x0F;
    rray[1] |= active_test; 
    write_registers(rray, 2);
    
    if(!pin_get(0, column + 3)) {
        return 1;
    }
    return 0;
    
}
char keypad_read()  {
    // No else if, because return is fine
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
int bomb_i = 0, bomb_j = 0;
int c_countdown = 0;
char old_not_set = 0;
char setting_bomb = 0;
void set_bomb(int time) {
    if(time > 99)   {
        time = 99;
    }
    int number_1 = time / 10;
    int number_2 = time - number_1 * 10;
    bomb_i = number_1;
    bomb_j = number_2;
}
void bomb_tick()    {
    if(bomb_j == 0) {
        if(bomb_i == 0);
        else    {
            bomb_j = 9;
            --bomb_i;
        }
    }
    else    {
        --bomb_j;
    }
}
void set_digit(char digit)  {
    
    rray[1] = digit + 1 | 0x60;
    int value;
    if(digit == DIGIT_ONE)  {
        value = bomb_j;
    }   
    else    {
        value = bomb_i;
    }
    rray[0] = numbers[value];
    
    write_registers(rray, 2);
}
void beep_swap(int beep_on){
    pin_set(0, 7, beep_on);
}

void count()    {    
    bomb_i = 0;
    bomb_j = 9;
    int time = 350;

    int beep_is_on = 1;

    int current_digit = 0;

    int slowpoke = 2;
    int beep_is_off = 0;

    while(1)    {
        timer_count();
        int test = 0;
        test != test;
        // Update the display every 10 ms and swap the active lights
        if(get_timer(0) == TIMER_DONE)   {
            ++current_digit;
            current_digit = current_digit % 2;
            set_digit(current_digit);
            timer_activate(0, 10000);
        }
        // Every second, update the time that is send to the display (bomb_j, bomb_i)
        if(get_timer(1) == TIMER_DONE)   {
            //uart_put_string("putting stuff here\n");
            timer_activate(1, SECOND);
            bomb_tick();
        }
        if(bomb_i > 0)    {
            // Beep on frequency
            if(get_timer(2) == TIMER_DONE) {
                if(get_timer(3) == TIMER_DONE)   {
                    timer_activate(3, (time + (1000 - 1000 / (bomb_i * 10 + bomb_j))));
                    if(beep_is_on == 0) {
                        beep_is_on = 1;
                    }  
                    else
                        beep_is_on = 0;    
                }
                beep_swap(beep_is_on);
            }
        } else if(bomb_j > 0) {
            slowpoke = 5;
            // Beep on frequency
            if(get_timer(4) == TIMER_DONE) {
                timer_activate(4, SECOND / (15 - (bomb_j / 2)));
                if(beep_is_off == 0)   {
                    beep_is_off = 1;
                }
                else
                {
                    beep_is_off = 0;
                }
            }
            if(beep_is_off == 0) {
                if(get_timer(3) == TIMER_DONE)   {
                    timer_activate(3, (time + (500 - 500 / (bomb_i * 10 + bomb_j))));
                    if(beep_is_on == 0) {
                        beep_is_on = 1;
                    }  
                    else
                        beep_is_on = 0;    
                }
                beep_swap(beep_is_on);
            }
        }

        // Turn beeping sound on for half a second every second
        if(get_timer(5) == TIMER_DONE)  {
            timer_activate(5, SECOND);
            timer_activate(2, 1000000 /slowpoke);
        }
        if(get_timer(6) == TIMER_DONE) {
            active_test = 0x60;
            char old_active_button = active_button;
            
            // Read * on keypad only, otherwise it will cost too much performance and lights will not blink properly!
            if(read_one_key(1, 4))  {
                setting_bomb = 1;
            }     
            else if(setting_bomb) {
                active_button = keypad_read();
                if(active_button == '#')    {
                    setting_bomb = 0;
                    set_bomb(c_countdown);
                    c_countdown = 0;
                }
                else if(active_button != old_active_button)  {   // new button pressed
                    if(active_button >= '0' && active_button <= '9')
                    if(old_not_set == 1) {
                        c_countdown = active_button - 48;
                        old_not_set = 0;
                    }
                    else {
                        c_countdown *= 10;
                        c_countdown += active_button - 48;
                    } 
                }
            } 
            timer_activate(6, SECOND / 5); 
        }
    }
}
int delaytime = 5;
void spi_test() {
    timer_init();
    uart_init(); 
    configure_pin_layout(1, 4, 8, 9);
    pin_configure_as_output(0, 7);
    pin_set(0, 7, 1);
    pin_set(0, 6, 0);
    uart_put_string( "Starting program...\n" );
    char rray[2] = {0x00, 0x00};
    write_registers(rray, 2);
    for(;;) {
        count();
    }
}
int main( void ){	
    spi_test();
}