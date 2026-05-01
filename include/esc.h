#ifndef ESC_H
#define ESC_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include "printf.h"
#include "state_machine.h"
#include "wait.h"

#define BUFFER_SIZE 64
#define CLKSPD 20000000UL 
#define MAX_THROTTLE_CYCLES  2000UL
#define MIN_THROTTLE_CYCLES  1000UL
#define LOW_C TCE0.CMP0
#define LOW_B TCE0.CMP1
#define LOW_A TCE0.CMP2

typedef enum {
    AB,
    AC,
    BC,
    BA,
    CA,
    CB,

} step_t;

typedef enum {
    IDLE,
    STARTUP,
    RUNNING,
    STALL

} state_t;

typedef struct {
    int head;
    int tail;
    char data[BUFFER_SIZE];
} ring_buffer;

extern volatile step_t current_step;
extern volatile state_t state;
extern volatile uint16_t throttle;

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

void usart_init(void);
void _putchar(char character);
bool buffer_is_empty(void);
bool buffer_is_full(void);

#endif
