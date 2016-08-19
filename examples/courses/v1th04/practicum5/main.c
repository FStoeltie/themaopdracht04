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
#define SECOND 1000000
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
int bomb_i = 0, bomb_j = 0;
int c_countdown = 0;
char old_not_set = 0;
char setting_bomb = 0;
void set_bomb(int time) {
    uart_put_string("selected time is: ");
    uart_put_int_decimal(time);
    uart_put_string("\n");
    if(time > 99)   {
        time = 99;
    }
    int number_1 = time / 10;
    int number_2 = time - number_1 * 10;
    bomb_i = number_1;
    bomb_j = number_2;
}
void time_tick()    {
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
void set_digits(char digit01, char digit02)   {
    int i = 0;
    for(; i < 20; i++)  {
        rray[1] = 0x01 | 0x60;
        rray[0] = numbers[digit01];
        write_registers(rray, 2);
        delay(20);
    }

    
    rray[1] = 0x02 | 0x60;
    
    
    rray[0] = numbers[digit02];
    write_registers(rray, 2);
    delay(10);
}
void set_digit(char digit, char value)  {
        rray[1] = digit | 0x60;
        rray[0] = numbers[value];
        write_registers(rray, 2);

}
void beep(){
    unsigned int next = 0;
    unsigned int j = 0;
    #define PERIOD 1000*1000/440
    next = now();
    //for( j = 0; j < 220; j++ ){   //duur van een piep 440 = 1 seconden piep         
    next += ( PERIOD / 4.5 );  //toonhoogte     
    //while( now() < next );    
    
    pin_set(0, 7, 1);
    delay(600.13);
    next += ( PERIOD / 4.5 );                   
    //while( now() < next );      
    
    pin_set(0, 7, 0);
    delay(600.13); 
    //} 
}
void beep_swap(int beep_on){
    //unsigned int next = 0;
    //unsigned int j = 0;
    //#define PERIOD 1000*1000/440
    //next = now();
    //for( j = 0; j < 220; j++ ){   //duur van een piep 440 = 1 seconden piep         
    //next += ( PERIOD / 4.5 );  //toonhoogte     
    //while( now() < next );    
    
    pin_set(0, 7, beep_on);
    //delay(600.13);
    //} 
}
void count()    {
    int timeslice_1 = 10; // display must swap every 10 ms
    int timeslice_2 = 2;  // must vibrate beep sound every 2 ms
    int update_frequency = timeslice_1 / timeslice_2;

    int i = 0;
    rray[1] = 0xFF;
    bomb_i = 9;
    bomb_j = 9;
    int wait_time = now() + delay_time;
    unsigned int next = now();
    unsigned int next_2 = next;
    int swap_sound = 0;
    #define PERIOD 1000*1000/440
    int d_time = now() + 1000000;
    int beep_on_time = now() + 1000000 /2;
    int time = 490;
    int display_time = 10000;
    int beep_time_swap = time;
    int current_beep_time = now();
    int beep_is_on = 1;
    int beep_last_update = now();
    int swap_display_on_time = now() + display_time;
    
    int current_digit = 0;
    int current_digit_counter = now() + SECOND;
    int key_presses = now() + SECOND / 5;
    int slowpoke = 2;
    int beep_is_off = 0;
    int beep_is_off_timer = now() + SECOND / 5; 
    while(1)    {
        // Every second, update the time that is send to the display (bomb_j, bomb_i)
        if(now() > current_digit_counter)   {
            current_digit_counter = now() + SECOND;
            time_tick();
        }
        // Update the display every 10 ms and swap the active lights
        if(now() > swap_display_on_time) {
            if(current_digit == 0x02)  {
                current_digit = 0x01;
                set_digit(current_digit, bomb_i);
            }
            else {
                current_digit = 0x02;
                set_digit(current_digit, bomb_j);
            }
            
            swap_display_on_time = now() + display_time;
        }
        if(bomb_i > 0)    {
            // Beep on frequency
            if(now() > beep_on_time) {
                if(current_beep_time < now())   {
                    current_beep_time += (time + (1000 - 1000 / (bomb_i * 10 + bomb_j)));
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
            if(now() > beep_is_off_timer) {
                beep_is_off_timer = now() + SECOND / (10 - (bomb_j / 2));
                if(beep_is_off == 0)   {
                    beep_is_off = 1;
                }
                else
                {
                    beep_is_off = 0;
                }
            }
            if(beep_is_off == 0) {
                //if(now() > beep_on_time) {
                if(current_beep_time < now())   {
                    current_beep_time += (time + (1000 - 1000 / (bomb_i * 10 + bomb_j)));
                    if(beep_is_on == 0) {
                        beep_is_on = 1;
                    }  
                    else
                        beep_is_on = 0;    
                }
                beep_swap(beep_is_on);
            //}
            }
            
        }

        // Turn beeping sound on for half a second every second
        if(now() > d_time)    {
            d_time = now() + 1000000;
            beep_on_time = now() + 1000000 /slowpoke;
        }
        if(now() > key_presses) {
            
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
                   // uart_put_string("key pressed: ");
                    if(active_button >= '0' && active_button <= '9')
                    if(old_not_set == 1) {
                        c_countdown = active_button - 48;
                        //uart_put_int_decimal(c_countdown);
                        old_not_set = 0;
                    }
                    else {
                        c_countdown *= 10;
                        c_countdown += active_button - 48;
                        //uart_put_int_decimal(c_countdown);
                    }
                    
                   // uart_put_string("\n");
                }
            }  
            key_presses = now() + SECOND / 5; 
        }
        
            //set_digits(bomb_i, bomb_j);
    
        
        //delay(100000);
        /*int beep_time = delay_time / 2; // half a second

        if(now() > next)    {
            next = now();
            next += ( PERIOD / time_slice_2 );
            //always do timeslice_2
            if(update_frequency >= timeslice_1) {
                update_frequency -= timeslice_1;
            }
            
        }*/
        /*while(now() < next)    {
            pin_set(0, 7, swap_sound); 
        }
        
        {
            if(swap_sound == 1)
                swap_sound = 0;
            else
                swap_sound = 1;
            #define PERIOD 1000*1000/440
 
        }
        if(now() > wait_time)    {
            bomb_time();
            
            wait_time = now() + delay_time;
        }
            active_test = 0x60;
            char old_active_button = active_button;
            active_button = keypad_read();
            
            if(active_button == '*')    {
                setting_bomb = 1;         
            }        
            else if(setting_bomb) {
                if(active_button == '#')    {
                    setting_bomb = 0;
                    set_bomb(c_countdown);
                    c_countdown = 0;
                }
                else if(active_button != old_active_button)  {   // new button pressed
                    uart_put_string("key pressed: ");
                    if(active_button >= '0' && active_button <= '9')
                    if(old_not_set == 1) {
                        c_countdown = active_button - 48;
                        uart_put_int_decimal(c_countdown);
                        old_not_set = 0;
                    }
                    else {
                        c_countdown *= 10;
                        c_countdown += active_button - 48;
                        uart_put_int_decimal(c_countdown);
                    }
                    
                    uart_put_string("\n");
                }
            }   
            set_digits(bomb_i, bomb_j);
    }*/

/*        if(bomb_i == 0 && bomb_j == 0)   {
            uart_put_string("boom");
            
            beep2();
        }
        else    {
            beep();
        }
*/
    }
    //delay(10000);
    bomb_j = 9;
}


void beep2(){
    unsigned int next = 0;
    unsigned int j = 0, i = 0;
    #define PERIOD 1000*1000/440
    for(i = 0; i < 6; i++){
    next = now();
    for( j = 0; j < 220; j++ ){   //duur van een piep 440 = 1 seconden piep         
    next += ( PERIOD / 4.5 );  //toonhoogte     
    while( now() < next );    
    pin_set(0, 7, 1);

    next += ( PERIOD / 4.5 );                   
    while( now() < next );      
    pin_set(0, 7, 0); 
    } 
    delay(100000);
    }
}


void reading_matrix1()  {
    pin_configure_as_input(0, 4);
    pin_configure_as_input(0, 5);
    pin_configure_as_input(0, 6);
    
}
int delaytime = 5;
void spi_test() {
    timer_init();
    uart_init(); 
    configure_pin_layout(1, 4, 8, 9);
    pin_configure_as_output(0, 7);
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