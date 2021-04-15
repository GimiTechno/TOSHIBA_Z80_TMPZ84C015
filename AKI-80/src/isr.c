#include "common.h"
#include "lib.h"
#include "interrupt.h"

// 外部割込みISR
__interrupt void ext_int_isr()
{
    NOP();
    NOP();
    NOP();
}