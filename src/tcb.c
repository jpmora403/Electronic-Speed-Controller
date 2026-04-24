/* This function initializes the AVR TCB timer to capture the incoming 
 * PWM signal and generate an event
 */


#include <esc.h>

void tcb0(void) {

    PORTA.PIN7CTRL = 0;
    PORTA.EVGENCTRLA = 7;
    PORTA.DIRSET = 1 << 7;
    //Channel selection
    EVSYS.CHANNEL0 = EVSYS_CHANNEL_PORTA_EV1_gc;
    EVSYS.USERTCB0CAPT = EVSYS_USER_CHANNEL0_gc;

    //Configure TCB0
    TCB0.CTRLA = 0x1;
    TCB0.CTRLB = 0x4;
    TCB0.EVCTRL = 0x1;
    TCB0.INTCTRL = 0x3;
    
}

ISR (TCB0_INT_vect) {

    if (TCB0.INTFLAGS & 0x2) {
        mode = IDLE;
        TCB0.INTFLAGS |= 0x20;
    }else {
        if (mode == IDLE) 
            mode = STARTUP;
        else {
            mode = RUNNING;
            uint16_t temp = TCB0.CCMP - 1000;
            throttle = (temp * 416) / 1000;
        }
    }
    usart_putchar('9');
    usart_putchar('\n');

}


