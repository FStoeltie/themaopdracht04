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
#include "pins.h"	
#include "servo.h"
#include "timer.h"
void disable_others()  {
    int prep_port, prep_pin;
    for(prep_pin = 4; prep_pin < 8; prep_pin++)  {
        //if(prep_pin > 4)
        //    prep_port = 1;
        pin_set(prep_port, prep_pin, 0);
    }
    pin_set(1, 4, 0);
    pin_set(1, 5, 0);
    pin_set(1, 8, 0);
    pin_set(1, 9, 0);
   
}
void week1()    {
    // must be volatile to prevent optimization of the wait loops
   volatile int i;
   
   // make PIO1_4 an output
   //LPC_GPIO1->DIR = LPC_GPIO1->DIR | 0x10; 
   int prep_port = 0, prep_pin;

   for(prep_pin = 4; prep_pin < 8; prep_pin++)  {
        //if(prep_pin > 4)
        //    prep_port = 1;
        pin_configure_as_output(prep_port, prep_pin);
   }
   pin_configure_as_output(1, 4);
   pin_configure_as_output(1, 5);
   pin_configure_as_output(1, 8);
   pin_configure_as_output(1, 9);
   
   int current_led = 0;
   // loop forever
   while( 1 ){
       #define count_down 40000
            for(current_led = 4; current_led < 8; current_led++)    {
                for( i = 0; i < count_down; i++ ){ 
                }
                disable_others();
                    pin_set(0, current_led, 1);
                for( i = 0; i < count_down; i++ ){
                }
            }
            
            for(current_led = 4; current_led < 6; current_led++)    {
                for( i = 0; i < count_down; i++ ){ 
                }
                disable_others();
                    pin_set(1, current_led, 1);
                for( i = 0; i < count_down; i++ ){
                }
            }
            for(current_led = 8; current_led < 10; current_led++)    {
                for( i = 0; i < count_down; i++ ){ 
                }
                disable_others();
                    pin_set(1, current_led, 1);
                for( i = 0; i < count_down; i++ ){
                }
            }
	}     
}		
void week2_servo()  {
    
}
int main( void ){	
    unsigned int n;
    servo_init(1, 5);
    timer_init();

    for(;;){
            for(n = 600; n < 2200; n = n + 10)  {
            servo_pulse(1, 5, n);
            //servo_pulse( 1, 5, 2500 );
            await(now() + 50 * 700);
        }
        
        
       /* await( now() + 50 * 1000 );
        servo_pulse( 1, 4, 1000 );
        await( now() + 50 * 1000 );
        servo_pulse( 1, 4, 1500 );
        await( now() + 50 * 1000 );*/
       /* for( n = 500; n < 2500; n = n + 10 ){
            servo_pulse( 1, 4, 500 );
            await( now() + 50 * 1000 );
        }   */       
    }

   
}