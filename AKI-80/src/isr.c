#include "common.h"
#include "lib.h"
#include "interrupt.h"

// �O��������ISR
__interrupt void ext_int_isr()
{
    NOP();
    NOP();
    NOP();
}