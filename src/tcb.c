/* This function initializes the AVR TCB timer to capture the incoming 
 * PWM signal and generate an event
 */


#include <esc.h>

void tcb0(void) {

    PORTA.PIN7CTRL = 1 << 3;
    PORTA.EVGENCTRLA = 7;
//    PORTA.DIRSET = 1 << 7;
    //Channel selection
    EVSYS.CHANNEL0 = 0x40;
    EVSYS.USERTCB0CAPT = EVSYS_USER_CHANNEL0_gc;

    //Configure TCB0
    TCB0.CTRLA = 0x1; 
    TCB0.CTRLB = 0x4;
    TCB0.EVCTRL = 0x1 | (1 << 6);
    TCB0.INTCTRL = 0x3;
    
}

ISR (TCB0_INT_vect) {
   if (TCB0.INTFLAGS & 0x2) {
        throttle = 0;
        mode = IDLE;
        TCB0.INTFLAGS = 0x2;
    }
    if (TCB0.INTFLAGS & 0x1) {
            mode = RUNNING;
            throttle = TCB0.CCMP;
        
    }
}


