#include "esc.h"

static volatile ring_buffer buffer; 

void usart_init() {
    cli();

    PORTMUX.USARTROUTEA = PORTMUX_USART0_ALT3_gc;
    PORTD.DIRSET |= 1 << 4;

    USART0.BAUD = (uint16_t)((CLKSPD * 64.0) / (16.0 * 115200) + 0.5);

    USART0.CTRLB |= 1 << 6;

    sei();
}

void _putchar(char c) {
    //Disable DRE interrupts for safety
    USART0.CTRLA = 0x0;

    if (buffer_is_full()) {
        USART0.CTRLA = 1 << 5;
        return;
    }
    else {
        buffer.data[buffer.head] = c;
        //check for wrap around if (buffer.head == BUFFER_SIZE - 1)
        if (buffer.head == BUFFER_SIZE - 1)
            buffer.head = 0;
        else
            buffer.head++;
    }

    //Re-enable interrupts
    USART0.CTRLA = 1 << 5;
}

ISR (USART0_DRE_vect) {
    if (buffer_is_empty()) 
        USART0.CTRLA = 0;
    else {
        USART0.TXDATAL = buffer.data[buffer.tail];
        //Check for wrap around
        if (buffer.tail == BUFFER_SIZE - 1)
            buffer.tail = 0;
        else
            buffer.tail++;
    }
    

}

bool buffer_is_empty() {
    return (buffer.tail == buffer.head);
}

bool buffer_is_full() {
    if (buffer.tail == 0)
        if (buffer.head == BUFFER_SIZE - 1)
            return true;
        else
            return false;
    else
        if (buffer.head == buffer.tail - 1)
            return true;
        else return false;
}
