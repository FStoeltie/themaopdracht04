#include "servo.h"
#include "timer.h"
void servo_init(int port, int pin)    {
    // Configure and validate pins
   pin_configure_as_output(port, pin);
   pin_set(port, pin, LOW);
}

void servo_pulse(int port, int pin, uint16_t position)    {
         pin_set(port, pin, HIGH);

         await( now() + position  );   

       pin_set(port, pin, LOW);
/*  
    // Pulse servo
     /* 
         pulsen 0.5...2.5 ms
         elke 10...30 ms signaal versturen van puls



   unsigned int delay = 8000;
   unsigned int start = now();
   unsigned int goal = 800000;
   unsigned int time_difference = 0;
   while(time_difference < goal)   {
      time_difference = now() - start;

      await( now() + 2500  );   
      await(now() + delay);
   }
   start = now();
   time_difference = 0;
   while(time_difference < goal)   {
      time_difference = now() - start;

      pin_set(port, pin, HIGH);
      pin_set(port, pin, LOW);
      await(now() + delay);
   }
*/
   
}


