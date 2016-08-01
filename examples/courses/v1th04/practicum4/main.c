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
int delaytime = 10000;
void spi_test() {
    timer_init();
    uart_init(); 
    configure_pin_layout(1, 4, 8, 9);
    uart_put_string( "Starting program...\n" );
    char rray[2] = {0x00, 0x00};
    for(;;) {
        int i = 0;
        char values = 0;
        for(i = 0; i < 255; i++) {
            rray[0] = i;
            write_registers(rray, 2);
            delay(delaytime);
        }
        values = 0;
        for(i = 0; i < 255; i++) {
            rray[1] = i;
            write_registers(rray, 2);
            delay(delaytime);
        }
        rray[0] = rray[1] = 0x00;
        write_registers(rray, 2);
        delay(delaytime);
    }
}
int main( void ){	
    spi_test();
}