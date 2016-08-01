#include "pins.h"

unsigned int PIN_CONFIGURATION_ERROR = 0x00;
void pin_configure_as_input(int port, int pin){
    // Validate port and pin, and if not: set error bit (PIN_INPUT_ERROR) and return
    if(!is_valid_config(port, pin, PIN_INPUT_ERROR))   {
        return;   
    }
    // Configure as input
    get_gpio(port)->DIR &= ~ (0x01 << pin);
}
void pin_configure_as_output(int port, int pin){
    // Validate port and pin, and if not: set error bit (PIN_OUTPUT_ERROR) and return
    if(!is_valid_config(port, pin, PIN_OUTPUT_ERROR))   {
        return;   
    }
    // Configure as output
    get_gpio(port)->DIR |= (0x01 << pin);
}
void pin_set(int port, int pin, unsigned char val){
     
    // If given port or pin number is greater than supported, or val is greater than 1:
     if(port > MAX_PORT || pin > MAX_PIN || val > 1) {
        // Set bit in PIN_CONFIGURATION_ERROR and return
        PIN_CONFIGURATION_ERROR |= PIN_SET_ERROR;
        return;
    }
    // Check if value is high and if so, set pin to HIGH (if not already HIGH)
    if(val == HIGH)    {
         get_gpio(port)->DATA |= (HIGH << pin);
    }
    // Else set pin to LOW
    else
    {
        get_gpio(port)->DATA  &= ~ (HIGH << pin);
    }

}
unsigned char pin_get(int port, int pin){
    // Validate port and pin, and if not: set error bit (PIN_GET_ERROR) and return
    if(!is_valid_config(port, pin, PIN_GET_ERROR))   {
        return;   
    }
    //return ( LPC_GPIO1->DATA & ( 1 << pin ) ) == 0;
    // Return value of pin, where 1 is HIGH and 0 is LOW    
    return !(  get_gpio(port)->DATA & ( HIGH << pin ) ) == 0;
}

static unsigned char is_valid_config(int port, int pin, int error) {
    // If given port or pin number is greater than supported:
    if(port > MAX_PORT || pin > MAX_PIN) {
        // Set bit in PIN_CONFIGURATION_ERROR and return
        PIN_CONFIGURATION_ERROR |= error;
        return 0;
    }
    return 1;
}

static LPC_GPIO_TypeDef* get_gpio(int port) {
    // Get port_number, port 0 = 0x00000, port 1 = 0x10000, port 2 = 0x20000, port 3 = 0x30000
    int port_number = 0x10000 * port;
    // Cast to correct GPIO structure (1 - 4)
    LPC_GPIO_TypeDef* LPC_selected = ((LPC_GPIO_TypeDef   *) (LPC_AHB_BASE  + port_number) );
    return LPC_selected;
}
