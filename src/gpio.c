#include <io.h>

int gpio(void) {

    //GPIOMUX
    PORTMUX.TCEROUTEA = PORTMUX_TCE0_PORTA_gc;

    return 0;
}
