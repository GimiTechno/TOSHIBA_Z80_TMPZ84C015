#include "lib.h"


void NOP()
{
    #asm
        nop
    #endasm
}

void* lib_memset(void *p_buf, uint8 val,size_t size)
{
    uint8 *p_tmp;

    p_tmp = (uint8 *)p_buf;
    while (size--)
    {
        *p_tmp = val;
        p_tmp++;
    }

    return p_buf;
}
