/*This function initalizes the AVR TCE timer to generate 3 PWM inputs
 * with a frequency of 24KHz and initializes the duty cycle to 0. 
 */

#include <io.h>

int tce0(void) {

    
    //Set pins as outputs
    PORTA.DIRSET = 1 | 1 << 2 | 1 << 3 |
                       1 << 4 | 1 << 5;
    
    TCE0.CTRLA = 0x01;
    TCE0.CTRLB = TCE_WGMODE_DSTOP_gc;
    TCE0.PER = 416; //24KHz switching
    //initial duty cycle of 0
    TCE0.CMP0 = 0;
    TCE0.CMP1 = 0;
    TCE0.CMP2 = 0;

    return 0;
} 
