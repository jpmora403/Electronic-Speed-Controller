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
    AC0.CTRLA = AC_HYSMODE_SMALL_gc | 0x1;
    //Neg input = neutral, pos initialized to phase C
    AC0.MUXCTRL = AC_INITVAL_LOW_gc | AC_MUXNEG_AINN1_gc
                    | AC_MUXPOS_AINP6_gc;
    //enable interrupts
    AC0.INTCTRL = 0x1;
    
}

ISR(AC0_AC_vect) {
    if (state = STARTUP) {
        back_emf_sufficient = true;
        return;
    }
   commutate();

}
