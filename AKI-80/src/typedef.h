#ifndef _TYPEDEFINE_H_
#define _TYPEDEFINE_H_

/* ------------------------------------------ */
/* Type Define */
/* ------------------------------------------ */
// Signed
#ifndef int8
    #define int8    signed char
    #define s1      int8
#endif
#ifndef int16
    #define int16   signed short
    #define s2      int16
#endif
#ifndef int32
    #define int32   signed long
    #define s4      int32
#endif
#ifndef int64
    #define int64   signed long long
    #define s8      int64
#endif
/* ------------------------------------------ */
// Unsigned
#ifndef uint8
    #define uint8   unsigned char
    #define u1      uint8
#endif
#ifndef uint16
    #define uint16  unsigned short
    #define u2      uint16
#endif
#ifndef uint32
    #define uint32  unsigned long
    #define u4      uint32
#endif
#ifndef uint64
    #define uint64  unsigned long long
    #define u8      uint64
#endif
/* ------------------------------------------ */
// ON/OFF
#ifndef ON
    #define ON      0x01
#endif
#ifndef OFF
    #define OFF     0x00
#endif
/* ------------------------------------------ */
// High/Low
#ifndef HIGH
    #define HIGH    0x01
#endif
#ifndef LOW
    #define LOW     0x00
#endif
/* ------------------------------------------ */
// I/O
#ifndef IN
    #define IN      0x00
#endif
#ifndef OUT
    #define OUT     0x01
#endif
/* ------------------------------------------ */
// True/False
#ifndef TRUE
    #define TRUE    0x01
#endif
#ifndef FALSE
    #define FALSE   0x00
#endif
/* ------------------------------------------ */
// Bit[31:24]
#define BIT_31   (1 << 31)      /* bit 31 */
#define BIT_30   (1 << 30)      /* bit 30 */
#define BIT_29   (1 << 29)      /* bit 29 */
#define BIT_28   (1 << 28)      /* bit 28 */
#define BIT_27   (1 << 27)      /* bit 27 */
#define BIT_26   (1 << 26)      /* bit 26 */
#define BIT_25   (1 << 25)      /* bit 25 */
#define BIT_24   (1 << 24)      /* bit 24 */
// Bit[23:16]
#define BIT_23   (1 << 23)      /* bit 23 */
#define BIT_22   (1 << 22)      /* bit 22 */
#define BIT_21   (1 << 21)      /* bit 21 */
#define BIT_20   (1 << 20)      /* bit 20 */
#define BIT_19   (1 << 19)      /* bit 19 */
#define BIT_18   (1 << 18)      /* bit 18 */
#define BIT_17   (1 << 17)      /* bit 17 */
#define BIT_16   (1 << 16)      /* bit 16 */
// Bit[15:8]
#define BIT_15   (1 << 15)      /* bit 15 */
#define BIT_14   (1 << 14)      /* bit 14 */
#define BIT_13   (1 << 13)      /* bit 13 */
#define BIT_12   (1 << 12)      /* bit 12 */
#define BIT_11   (1 << 11)      /* bit 11 */
#define BIT_10   (1 << 10)      /* bit 10 */
#define BIT_9    (1 << 9)       /* bit 9  */
#define BIT_8    (1 << 8)       /* bit 8  */
// Bit[7:0]
#define BIT_7    (1 << 7)       /* bit 7  */
#define BIT_6    (1 << 6)       /* bit 6  */
#define BIT_5    (1 << 5)       /* bit 5  */
#define BIT_4    (1 << 4)       /* bit 4  */
#define BIT_3    (1 << 3)       /* bit 3  */
#define BIT_2    (1 << 2)       /* bit 2  */
#define BIT_1    (1 << 1)       /* bit 1  */
#define BIT_0    (1 << 0)       /* bit 0  */

struct reg_t {
    union {
        u1 BYTE;
        struct {
            u1 B7:1;  /*    Bit 8     */
            u1 B6:1;  /*    Bit 7     */
            u1 B5:1;  /*    Bit 6     */
            u1 B4:1;  /*    Bit 5     */
            u1 B3:1;  /*    Bit 4     */
            u1 B2:1;  /*    Bit 3     */
            u1 B1:1;  /*    Bit 2     */
            u1 B0:1;  /*    Bit 1     */
        } BIT;
    } REG;
};

#endif  /* _TYPEDEFINE_H_ */