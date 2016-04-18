//! @file pins.h
//! @author Ferdi Stoeltie 1665045
//! @date 18-04-2016
//! @brief 

#ifndef PIN_CONFIGURE
#define PIN_CONFIGURE
#include "bmptk.h"
#include "routines.h"

#define PIN_INPUT_ERROR     0x01    // Error value for configuring pin as input
#define PIN_OUTPUT_ERROR    0x02    // Error value for configuring pin as output
#define PIN_SET_ERROR       0x04    // Error value for setting pin to either HIGH or LOW
#define PIN_GET_ERROR       0x08    // Error value for reading pin wheather pin is HIGH or LOW

#define MAX_PORT 4                  // Maximum number of port value that is supported (By LPC)
#define MAX_PIN 9                   // Maximum number of pin value that is supported (By LPC) NOTE: <-- should be changed to 11?


//! @author Ferdi Stoeltie 1665045
//! @brief Function provides an easy way to configure a given pin as input
//! @param port The port number (for current LPC, ranging from 1..4)
//! @param pin The pin to configure as input
//! @warning If a port/pin configuration is given that is invalid, 
//!             it will set PIN_INPUT_ERROR bit in PIN_CONFIGURATION_ERROR
void pin_configure_as_input(int port, int pin);

//! @author Ferdi Stoeltie 1665045
//! @brief Function provides an easy way to configure a given pin as output
//! @param port The port number (for current LPC, ranging from 1..4)
//! @param pin The pin to configure as output
//! @warning If a port/pin configuration is given that is invalid, 
//!             it will set PIN_OUTPUT_ERROR bit in PIN_CONFIGURATION_ERROR
void pin_configure_as_output(int port, int pin);

//! @author Ferdi Stoeltie 1665045
//! @brief Sets pin on port to either HIGH (1), or LOW (0)
//! @param port The port number (for current LPC, ranging from 1..4)
//! @param pin The pin to configure as output
//! @param val High (1), or Low(0). for turning the pin on/off
//! @warning If a port/pin configuration is given that is invalid, 
//!             or value is invalid, 
//!             it will set PIN_SET_ERROR bit in PIN_CONFIGURATION_ERROR
void pin_set(int port, int pin, unsigned char val);

unsigned char pin_get(int port, int pin);

static unsigned char is_valid_config(int port, int pin, int error);

static LPC_GPIO_TypeDef* get_gpio(int port);
int get_countdown();

int PIN_CONFIGURATION_ERROR;
#endif // PIN_CONFIGURE