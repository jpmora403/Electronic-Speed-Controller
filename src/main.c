#include <io.h>
#include <interrupt.h>
#include "gpio.h"
#include "tcb.h"
#include "tce.h"
#include "wex.h"
#include "ac.h"

#define CLKSPD 200000000


int main() {

    //init peripherals
    gpio();
    tcb0();
    tce0();
    wex();
    ac0();

    //enable global interrupts
    CPU_SREG |= CPU_I_bp;

    return 0;
}
