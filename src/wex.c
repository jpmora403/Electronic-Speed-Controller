/*This file initializes the AVR WEX to output the 3 CMP channels
 * from TCE0 and 3 inverted signals with deadtime
 */

#include <io.h>

int wex(void) {

    //DTI on wo
    WEX0.CTRLA = 0x3;
    //DTI in clock cycles = (145ns turn off time + 70ns safety margin)
    //                      * 20Mhz = 4.3 => 5 clock cycles
    //5 clock cycles * 5 for lower sink current in version 1
    WEX0.DTBOTH = 25;

    WEX0.OUTOVEN = 0x1F;
    

    return 0;
}
