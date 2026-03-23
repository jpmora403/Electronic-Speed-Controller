#ifndef ESC_H
#define ESC_H

#include <avr/io.h>
#include <avr/interrupt.h>


typedef enum {
    AB,
    AC,
    BC,
    BA,
    CA,
    CB,
    STOP

} step_t;

typedef enum {
    IDLE,
    STARTUP,
    RUNNING,
    STALL

} mode_t;

extern volatile step_t current_step;
extern volatile mode_t mode;
volatile uint16_t throttle = 0;

void ac0(void);
void gpio(void);
void tcb0(void);
void tce0(void);
void wex(void);
void idle(void);
void startup(void);
void running(void);
void commutate(void);
void stall(void);

void get_speed(void);


#endif
