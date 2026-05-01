#include "esc.h"

void wait_20us(int _20_us) {
    for (int i = 0; i < _20_us; i++)
        _NOP();
}

