/* This function initializes the AVR TCB timer to capture the incoming 
 * PWM signal and generate an event
 */


#include <io.h>

int tcb0(void) {

    PORTA.PIN7CTRL = PORT_ISC_INTDISABLE_gc;
    PORTA.EVGENCTRLA = PORT_EVGEN1SEL_PIN7_gc;
    //Channel selection
    EVSYS.CHANNEL0 = EVSYS_CHANNEL_PORTA_EV1_gc;
    EVSYS.USERTCB0CAPT = EVSYS_USER_CHANNEL0_gc;

    //Configure TCB0
    TCB0.CTRLB = TCB_CNTMODE_PW_gc;
    TCB0.EVCTRL = 0x01;
    
    return 0;
}
