#include "system.h"

volatile static uint32_t gSystick = 0;

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TA_0_ISR(void)
{
   gSystick++;
}


void system_systickInit(){
    timer_init(Timer_A0, 1000);
}

uint32_t system_getSysticks(void){
    __istate_ts s = __get_interrupt_state();
    __disable_interrupt();
    uint32_t systick = gSystick;
    __set_interrupt_state(s);
    return systick;
}

void system_sleep(uint32_t millis){
   volatile uint32_t start = system_getSysticks();
   while((start+millis) > system_getSysticks());
   start = 0;
}
