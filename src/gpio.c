#include <io.h>

void gpio(void) {

    //GPIOMUX
    PORTMUX.TCEROUTEA = PORTMUX_TCE0_PORTA_gc;

    //ENABLE output
    PORTC.DIRSET = 1 << 1;



}
