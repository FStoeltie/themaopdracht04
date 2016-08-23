// implementation of the timer functions
//

#include "timer.h"
#include "bmptk.h"
#define TIMER_AMOUNT 10
unsigned int array_size[TIMER_AMOUNT] = { 0 };
void timer_init( void ){
   LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);     // enable clock for CT32B0
   LPC_TMR32B0->CTCR = 0x00;                // use AHB clock
   LPC_TMR32B0->PR   = 11;                  // 12 MHz -> 1 count/usec
   LPC_TMR32B0->TC   = 0;                   // start at 0
   LPC_TMR32B0->TCR  = 0x01;                // enable the timer
}

unsigned int now(){
   return LPC_TMR32B0->TC;
}

void await( unsigned int t ){
   while( t > now() ){
   }
}

void delay(unsigned int m_seconds)  {
    unsigned int current_time = now();
    while(current_time + m_seconds > now());
}

// Returns remaining time of timer. 0 means either completed or not set.
unsigned int get_timer(int n)  {
    // Requesting invalid timer, only timers 0..9 are available
    if(n > TIMER_AMOUNT - 1)   {
        return 0;
    }
    else    {
        return array_size[n];
    }
}

void timer_activate(int index, unsigned int duration)    {
    array_size[index] = duration;   // start clock with current timestamp and added time
    //array_size[index + 10] = duration;       // index + 5 holds the value of the time that needs to be added every time
}
void timer_count()  {
    static int old_time = 0;
    uint16_t time_diff = now() - old_time;
    old_time = now();
    int i = 0;
    // For all timers (max 5)
    for(; i < TIMER_AMOUNT; i++)   {
        // Check if timer is activated and timer minus time difference between latest update is less than 0 (<= 0 means timer is done)
        if((int)(array_size[i] - time_diff) <= 0)   {
            array_size[i] = 0;  // timer done
        }
        else    {
            array_size[i] -= time_diff;
        }
    }
}