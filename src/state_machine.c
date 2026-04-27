#include "esc.h"

volatile bool back_emf_sufficient;
volatile int min_throttle;
volatile bool no_back_emf;
volatile int retry_counter;

void idle () {
    state = IDLE;

    back_emf_sufficient = false;
    min_throttle = 10;
    no_back_emf = false;
    PORTC.OUTCLR = 1 << 1;

    while (1) {
        if (throttle > 10) {
            state_function = startup;
            break;
        }
    }
}

void startup() {
    state = STARTUP;
    //Disable tcb and ac interrupts for forced commutation
    TCB0.INTCTRL = 0;
    PORTC.OUTSET = 1 << 1; //gate driver Enable
    throttle = 10;
    current_step = AB;
    back_emf_sufficient = false;
    while (~(back_emf_sufficient)) {
        for (int i = 0; i < 5; i++) {
            commutate();
        }
        throttle += 10;
    }
    min_throttle = throttle;
    state_function = running;
    back_emf_sufficient = false;
    TCB0.INTCTRL = 0x3;
}

void running() {
    state = RUNNING;

    while (1) {
        if (throttle < (min_throttle + 10)) {
            state_function = idle;
            break;
        }
        if (no_back_emf) {
            state_function = stall;
           break;
        }
    }

}

void stall() {
    state = STALL;
    PORTC.OUTCLR = 1 << 1;   
    state_function = idle;
    retry_counter ++;
}



