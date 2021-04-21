#include "tmpz84c015.h"

/**
 * @brief 割込み許可
 * 
 */
#pragma inline EI
void EI()
{
#if (C_COMPILER == COMPILER_XCC_V)
    #asm
        ei
    #endasm
#endif
}

/**
 * @brief 割込みマスク
 * 
 */
#pragma inline DI
void DI()
{
#if (C_COMPILER == COMPILER_XCC_V)
    #asm
        di
    #endasm
#endif
}

/**
 * @brief NOP
 * 
 */
#pragma inline NOP
void NOP()
{
#if (C_COMPILER == COMPILER_XCC_V)
    #asm
        nop
    #endasm
#endif
}