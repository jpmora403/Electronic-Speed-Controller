#include "esc.h"

volatile bool back_emf_sufficient;
volatile int min_throttle;
volatile bool no_back_emf;
volatile int retry_counter;

void idle () {
    state = IDLE;
    throttle = 0;
    LOW_A = LOW_B = LOW_C = 0;
    back_emf_sufficient = false;
    min_throttle = 10;
    no_back_emf = false;
    PORTC.OUTCLR = 1 << 1;
    AC0.INTCTRL = 0;

    while (1) {
        if (throttle > 20) {
            state_function = startup;
            break;
        }
        printf("state: %d\n", state);
    }
}

void startup() {
    state = STARTUP;
    //Disable tcb and ac interrupts for forced commutation
    TCB0.INTCTRL = 0;
    AC0.INTCTRL = 0;
    PORTC.OUTSET = 1 << 1; //gate driver Enable
    current_step = AB;
    throttle = 20;
    back_emf_sufficient = false;
    int wait_time = 10000; //50 clk cycles == 1ms
    while (!back_emf_sufficient) {
        commutate();
        wait_20us(wait_time);
        wait_time -= 10;
    }
    state_function = running;
    back_emf_sufficient = false;
    TCB0.INTCTRL = 0x3;
}

void running() {
    state = RUNNING;

    while (1) {
        if (throttle < 20 ) {
            state_function = idle;
            break;
        }
        if (no_back_emf) {
            state_function = stall;
           break;
        }
        printf("state: %d\n", state);
    }

}

void stall() {
    state = STALL;
    PORTC.OUTCLR = 1 << 1;   
    state_function = idle;
    retry_counter ++;
}



