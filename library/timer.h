// header file for the timer functions
//

#ifndef NINCLUDE_TIMER_H
#define NINCLUDE_TIMER_H
void timer_init( void );
unsigned int now();
void await( unsigned int t );
void delay(unsigned int m_seconds);

//! @author Ferdi Stoeltie 1665045
//! @brief Function returns remaining time of timer index n
//! @param timer The timer that should return it's remaining time.
//! @warning Do not go over max timer (currently max 10 supported), 
//! so do not request a higher number.
//! Also, before calling this method the function timer_init() should be called!
unsigned int get_timer(int timer);

//! @author Ferdi Stoeltie 1665045
//! @brief activate a new timer that should be started. (timer 0..9)
//! @param index index of which timer should be activated.
//! @param duration Duration of timer that should be started.
//! @warning Do not go over max timer (currently max 10 supported), 
//! so do not request a higher number
//! Also, before calling this method the function timer_init() should be called!
void timer_activate(int index, unsigned int duration);

//! @author Ferdi Stoeltie 1665045
//! @brief Countsdown all active timers.
//! @warning If not called, timers will not countdown!
//! Also, before calling this method the function timer_init() should be called!
void timer_count();
#endif
