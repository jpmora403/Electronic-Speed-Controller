#include <io.h>
#include <interrupt.h>
#include <stdint.h>
#include "esc.h"

#define MAX_THROTTLE_CYCLES  2000UL
#define MIN_THROTTLE_CYCLES  1000UL
#define LOW_C TCE0.CMP0
#define LOW_B TCE0.CMP1
#define LOW_A TCE0.CMP2

//Speed resolution is 416 (log(416) in bits)

//Global variables
volatile uint16_t throttle = 0; //In units of clock cycles
volatile step_t current_step;
volatile state_t state = IDLE;
volatile void (*state_function)(void);

int main() {

    //init peripherals
    gpio();
    tcb0();
    tce0();
    wex();
    ac0();
    usart_init();

    //enable global interrupts
    CPU_SREG |= CPU_I_bp;

    //Disable clk prescaler
    CPU_CCP = 0xD8;
    CLKCTRL.MCLKCTRLB = 0x0;

    state_function = idle;

    while (retry_counter != 4) {
        state_function();
        printf("state: %d\n", state);
    }
    
    while(1) {
        PORTC.OUTCLR = 1 << 1;
    }

}

void commutate() {
    //Lock updates
    TCE0.CTRLESET |= 0x2;

    switch (current_step) {
        case (AB):
            LOW_A = 416 - throttle;
            LOW_B = throttle;
            LOW_C = 0;
            AC0.MUXCTRL |= AC_MUXPOS_AINP6_gc;
            current_step = AC;
            break;
        case (AC):
            LOW_A = 416 - throttle;
            LOW_B = 0;
            LOW_C = throttle;
            AC0.MUXCTRL |= AC_MUXPOS_AINP4_gc;
            current_step = BC;
            break;
        case (BC):
            LOW_A = 0;
            LOW_B = 416 - throttle;
            LOW_C = throttle;
            AC0.MUXCTRL |= AC_MUXPOS_AINP0_gc;
            current_step = BA;
            break;
        case (BA):
            LOW_A = throttle;
            LOW_B = 416 - throttle;
            LOW_C = 0;
            AC0.MUXCTRL |= AC_MUXPOS_AINP6_gc;
            current_step = CA;
            break;
        case (CA):
            LOW_A = throttle;
            LOW_B = 0;
            LOW_C = 416 - throttle;
            AC0.MUXCTRL |= AC_MUXPOS_AINP4_gc;
            current_step = CB;
            break;
        case (CB):
            LOW_A = throttle;
            LOW_B = 416 - throttle;
            LOW_C = 0;
            AC0_MUXCTRL |= AC_MUXPOS_AINP0_gc;
            current_step = AB;
            break;
    }
    TCE0.CTRLECLR |= 0x2;

}


