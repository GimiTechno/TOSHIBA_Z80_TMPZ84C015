#ifndef _COMMON_H_
#define _COMMON_H_

#include "typedef.h"
#include "tmpz84c015.h"

/* ------------------------------------------ */
/*                 データ定義                  */
/* ------------------------------------------ */
typedef enum
{
    CPU_Z80 = 0x00,
    CPU_H8,
    CPU_AVR,
    CPU_PIC,
    CPU_STM32,
    CPU_ESP32,
    CPU_LPC
}E_CPU;

typedef enum
{
    COMPILER_XCC_V = 0x00,
    COMPILER_BCD_C,
    COMPILER_HIGHTECH_C,
    COMPILER_SDCC
}E_COMPILER;

#define CPU_TYPE    CPU_Z80
#define C_COMPILER  COMPILER_XCC_V

// Z80 GAIO社 XCC-Vコンパイラ
#if (C_COMPILER == COMPILER_XCC_V) && (CPU_TYPE == CPU_Z80)
    #define EXTERN global
#endif  /* C_COMPILER and CPU_TYPE */

#endif /* _COMMON_H_ */