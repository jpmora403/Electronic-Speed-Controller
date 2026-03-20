#include <io.h>

#define CLKSPD 20000000   




int init(void) {
    //GPIOMUX
        //TCE0
        PORTMUX.TCEROUTEA = PORTMUX_TCE0_PORTA_gc;
    
    //TCB input capture intit
        //EVSYS initialization for wave capture on TCB
            PORTA.PIN7CTRL = PORT_ISC_INTDISABLE_gc;
            PORTA.EVGENCTRLA = PORT_EVGEN1SEL_PIN7_gc;
            //Channel selection
            EVSYS.CHANNEL0 = EVSYS_CHANNEL_PORTA_EV1_gc;
            EVSYS.USERTCB0CAPT = EVSYS_USER_CHANNEL0_gc;

        //Configure TCB0
        TCB0.CTRLB = TCB_CNTMODE_PW_gc;
        TCB0.EVCTRL = 0x01;

    //TCE pwm generator
        //Set pins as outputs
        PORTA.DIRSET = 1 | 1 << 2 | 1 << 3 |
                       1 << 4 | 1 << 5;
    
        TCE0.CTRLA = 0x01;
        TCE0.CTRLB = TCE_WGMODE_DSTOP_gc;
        TCE0.PER = 416; //24KHz switching
        //initial duty cycle of 0
        TCE0.CMP0 = 0;
        TCE0.CMP1 = 0;
        TCE0.CMP2 = 0;
   

    //WEX output
    //DTI on wo
    WEX0.CTRLA = 0x3;
    //DTI in clock cycles = (145ns turn off time + 70ns safety margin)
    //                      * 20Mhz = 4.3 => 5 clock cycles
    //5 clock cycles * 5 for lower sink current in version 1
    WEX0.DTBOTH = 25;

    WEX0.OUTOVEN = 0x1F;

    //Comparator init
    //Disable digital input buffer on pd0 and set as input
    PORTD.DIRCLR = 0b100101;
    PORTC.DIRCLR = 0x8;
    PORTD.PIN0CTRL = PORT_ISC_INPUT_DISABLE_gc;
    PORTD.PIN2CTRL = PORT_ISC_INPUT_DISABLE_gc;
    PORTD.PIN5CTRL = PORT_ISC_INPUT_DISABLE_gc;
    PORTC.PIN3CTRL = PORT_ISC_INPUT_DISABLE_gc;
    
    //medium hysteresis & enable
    AC0.CTRLA = AC_HYSMODE_MEDIUM_gc | 0x1;
    //Neg input = neutral, pos initialized to phase A
    AC0.MUXCTRL = AC_INITVAL_LOW_gc | AC_MUXNEG_AINN1_gc
                    | AC_MUXPOS_AINP0_gc;

    return 0;

}

