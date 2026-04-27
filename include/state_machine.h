#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

//Ctrl signals
extern volatile bool back_emf_sufficient;
extern volatile int min_throttle;
extern volatile bool no_back_emf;
extern volatile int retry_counter;

extern void (*state_function)(void);

#endif
