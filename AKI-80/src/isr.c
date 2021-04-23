#include "common.h"
#include "lib.h"

/**
 * @brief NMI
 * 
 */
#pragma int_retn_n
void ISR_NMI()
{
    NOP();
}
#pragma noint_retn_n

/**
 * @brief 外部割込みISR
 * 
 */
__interrupt void ISR_Ext_Int()
{
    NOP();
    NOP();
    NOP();
}