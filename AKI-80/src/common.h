#ifndef _COMMON_H_
#define _COMMON_H_

/******************************/
#define ON      0x01
#define OFF     0x00
#define HIGH    0x01
#define LOW     0x00
#define TRUE    0x01
#define FALSE   0x00

#define int8    signed char
#define int16   signed short
#define int32   signed long
#define int64   signed long long
#define uint8   unsigned char
#define uint16  unsigned short
#define uint32  unsigned long
#define uint64  unsigned long long
/******************************/

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
/******************************/
#define EXTERN global
/******************************/
#endif  /* C_COMPILER and  */

#endif /* _COMMON_H_ */