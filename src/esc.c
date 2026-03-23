#include <io.h>
#include <interrupt.h>
#include <stdint.h>
#include "esc.h"

#define CLKSPD 20000000UL
#define MAX_THROTTLE_CYCLES = 2000UL
#define MIN_THROTTLE_CYCLES = 1000UL

//Speed resolution is 416 (log(416) in bits)

//Global variables
volatile uint16_t throttle = 0; //In units of clock cycles
volatile step_t current_step = STOP;
volatile mode_t mode = IDLE;

int main() {

    //init peripherals
    gpio();
    tcb0();
    tce0();
    wex();
    ac0();

    //enable global interrupts
    CPU_SREG |= CPU_I_bp;

    while (1) {
        
        switch (mode) {
            case IDLE: idle(); break;
            case STARTUP: startup(); break;
            case RUNNING: running(); break;
            case STALL: stall(); break;
        }

    }

    return 0;
}

void idle() {
    while (mode == IDLE) {
        TCE0.CMP0 = 0;
        TCE0.CMP1 = 0;
        TCE0.CMP2 = 0;
    }
    return;
}

void startup() {
    //Disable ac interrupts for forced commutation
    AC0.INTCTRL = 0;

    current_step = AB;
    

}

void running() {
    while (mode == RUNNING) {
        if (mode == STALL)
            return;
    }

}

void stall() {

    return;

}

void commutate() {
    //Lock updates
    TCE0.CTRLESET |= 0x2;

    switch (current_step) {
        case (AB):
            TCE0.CMP0 = 416 - throttle;
            TCE0.CMP1 = throttle;
            TCE0.CMP2 = 0;
            AC0.MUXCTRL |= AC_MUXPOS_AINP6_gc;
            TCE0.CTRLECLR |= 0x2;
            break;
        case (AC):
            TCE0.CMP0 = 416 - throttle;
            TCE0.CMP1 = 0;
            TCE0.CMP2 = throttle;
            AC0.MUXCTRL |= AC_MUXPOS_AINP4_gc;
            TCE0.CTRLECLR |= 0x2;
            break;
        case (BC):
            TCE0.CMP0 = 0;
            TCE0.CMP1 = 416 - throttle;
            TCE0.CMP2 = throttle;
            AC0.MUXCTRL |= AC_MUXPOS_AINP0_gc;
            TCE0.CTRLECLR |= 0x2;
            break;
        case (BA):
            TCE0.CMP0 = throttle;
            TCE0.CMP1 = 416 - throttle;
            TCE0.CMP2 = 0;
            AC0.MUXCTRL |= AC_MUXPOS_AINP6_gc;
            TCE0.CTRLECLR |= 0x2;
            break;
        case (CA):
            TCE0.CMP0 = throttle;
            TCE0.CMP1 = 0;
            TCE0.CMP2 = 416 - throttle;
            AC0.MUXCTRL |= AC_MUXPOS_AINP4_gc;
            TCE0.CTRLECLR |= 0x2;
            break;
        case (CB):
            TCE0.CMP0 = throttle;
            TCE0.CMP1 = 416 - throttle;
            TCE0.CMP2 = 0;
            AC0_MUXCTRL |= AC_MUXPOS_AINP0_gc;
            TCE0.CTRLECLR |= 0x2;
            break;
    }

}


