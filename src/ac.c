/*This file initializes the AC0n input to NEUTRAL,
 * and initializes the AC0p input to BACK_EMFA.
 *
 * Enables medium hysteresis
 *
 * File also includes the ISR for the AC0 interrupt
 */

#include <io.h>
#include <interrupt.h>
#include "esc.h"

void ac0(void) {
    
    //Disable digital input buffer on pd0 and set as input
    PORTD.DIRCLR = 0b100101;
    PORTC.DIRCLR = 0x8;
    PORTD.PIN0CTRL = PORT_ISC_INPUT_DISABLE_gc;
    PORTD.PIN2CTRL = PORT_ISC_INPUT_DISABLE_gc;
    PORTD.PIN5CTRL = PORT_ISC_INPUT_DISABLE_gc;
    PORTC.PIN3CTRL = PORT_ISC_INPUT_DISABLE_gc;
    
    //small hysteresis & enable
    AC0.CTRLA = AC_HYSMODE_LARGE_gc | 0x1;
    AC0.MUXCTRL = AC_INITVAL_LOW_gc;
    //enable interrupts
//    AC0.INTCTRL = 0x1;
    
}

ISR(AC0_AC_vect) {
    printf("AC interrupt\n");
    AC0.STATUS |= 0x1;
    AC0.CTRLA &= ~(0x1);
    if (state == STARTUP) {
        back_emf_sufficient = true;
    } else
        commutate();
    AC0.CTRLA |= 0x1;

}
