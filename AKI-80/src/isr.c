#include "common.h"
#include "lib.h"
#include "interrupt.h"

// ŠO•”Š„‚İISR
__interrupt void ext_int_isr()
{
    NOP();
    NOP();
    NOP();
}