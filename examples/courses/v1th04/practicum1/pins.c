#include "pins.h"
PIN_CONFIGURATION_ERROR = 0;
void pin_configure_as_input(int port, int pin){

    if(!is_valid_config(port, pin, PIN_INPUT_ERROR))   {
        return;   
    }
    // If given port or pin number is greater than supported:
    /*if(port > MAX_PORT || pin > MAX_PIN) {
        // Set bit in PIN_CONFIGURATION_ERROR and return
        PIN_CONFIGURATION_ERROR |= PIN_INPUT_ERROR;
        return;
    }*/
    // Get port_number, port 0 = 0x00000, port 1 = 0x10000, port 2 = 0x20000, port 3 = 0x30000
    //int port_number = 0x10000 * port;
    // Cast to correct GPIO structure (1 - 4)
    //LPC_GPIO_TypeDef* LPC_selected = ((LPC_GPIO_TypeDef   *) (LPC_AHB_BASE  + port_number) );
    // Configure as input
    get_gpio(port)->DIR &= ~ (0x01 << pin);
}
void pin_configure_as_output(int port, int pin){
    
    if(!is_valid_config(port, pin, PIN_OUTPUT_ERROR))   {
        return;   
    }
    // If given port or pin number is greater than supported:
/*    if(port > MAX_PORT || pin > MAX_PIN) {
        // Set bit in PIN_CONFIGURATION_ERROR and return
        PIN_CONFIGURATION_ERROR |= PIN_OUTPUT_ERROR;
        return;
    }*/
    // Get port_number, port 0 = 0x00000, port 1 = 0x10000, port 2 = 0x20000, port 3 = 0x30000
    //int port_number = 0x10000 * port;
    // Cast to correct GPIO structure (1 - 4)
    //LPC_GPIO_TypeDef* LPC_selected = ((LPC_GPIO_TypeDef   *) (LPC_AHB_BASE  + port_number) );
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
    // Get port_number, port 0 = 0x00000, port 1 = 0x10000, port 2 = 0x20000, port 3 = 0x30000
    //int port_number = 0x10000 * port;
    // Cast to correct GPIO structure (1 - 4)
    //LPC_GPIO_TypeDef* LPC_selected = ((LPC_GPIO_TypeDef   *) (LPC_AHB_BASE  + port_number) );
    //LPC_selected->DATA |= 0x10;
    if(val == 1)    {
         get_gpio(port)->DATA |= (1 << pin);
    }
    else
    {
        get_gpio(port)->DATA  &= ~ (1 << pin);
    }

}
unsigned char pin_get(int port, int pin){
    
    if(!is_valid_config(port, pin, PIN_OUTPUT_ERROR))   {
        return;   
    }
    
    // If given port or pin number is greater than supported:
    /*if(port > MAX_PORT || pin > MAX_PIN) {
        // Set bit in PIN_CONFIGURATION_ERROR and return
        PIN_CONFIGURATION_ERROR |= PIN_OUTPUT_ERROR;
        return;
    }*/
    // Get port_number, port 0 = 0x00000, port 1 = 0x10000, port 2 = 0x20000, port 3 = 0x30000
    //int port_number = 0x10000 * port;
    // Cast to correct GPIO structure (1 - 4)
    //LPC_GPIO_TypeDef* LPC_selected = ((LPC_GPIO_TypeDef   *) (LPC_AHB_BASE  + port_number) );
    return (  get_gpio(port)->DATA & ( 1 << pin ) ) == 0;
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

int get_countdown(){
    return 800000;
}