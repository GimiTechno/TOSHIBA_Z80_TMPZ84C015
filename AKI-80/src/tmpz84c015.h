#ifndef _TMPZ84C015_H_
#define _TMPZ84C015_H_

#define __Interrput__

#define BIT_7   (1 << 7)      /* bit 7 */
#define BIT_6   (1 << 6)      /* bit 6 */
#define BIT_5   (1 << 5)      /* bit 5 */
#define BIT_4   (1 << 4)      /* bit 4 */
#define BIT_3   (1 << 3)      /* bit 3 */
#define BIT_2   (1 << 2)      /* bit 2 */
#define BIT_1   (1 << 1)      /* bit 1 */
#define BIT_0   (1 << 0)      /* bit 0 */

/*****************************************************/
/**********       I/O Addr Define          **********/
/*****************************************************/
// CTC
#define REG_CTC_0       (*(volatile uint16 *)0x10)      /*  */
#define REG_CTC_1       (*(volatile uint16 *)0x11)      /*  */
#define REG_CTC_2       (*(volatile uint16 *)0x12)      /*  */
#define REG_CTC_3       (*(volatile uint16 *)0x13)      /*  */

// SIO
#define REG_SIO_A_DAT   (*(volatile uint16 *)0x18)      /*  */
#define REG_SIO_A_CMD   (*(volatile uint16 *)0x19)      /*  */
#define REG_SIO_B_DAT   (*(volatile uint16 *)0x1A)      /*  */
#define REG_SIO_B_CMD   (*(volatile uint16 *)0x1B)      /*  */

// PIO
#define REG_PIO_A_DAT   (*(volatile uint16 *)0x1C)      /*  */
#define REG_PIO_A_CMD   (*(volatile uint16 *)0x1D)      /*  */
#define REG_PIO_B_DAT   (*(volatile uint16 *)0x1E)      /*  */
#define REG_PIO_B_CMD   (*(volatile uint16 *)0x1F)      /*  */

// WDT
#define REG_WDTER       (*(volatile uint16 *)0xF0)      /* WDTER ... WDT許可レジスタ */
#define REG_WDTCR       (*(volatile uint16 *)0xF1)      /* WDTCR ... WDT制御レジスタ */

// 割込み
#define REG_INTPR       (*(volatile uint16 *)0xF4)      /* INTPR ... 割込み優先順位レジスタ */
/*****************************************************/

/* INTPR */
#define INTPR_PR_A      0x00    /* 割込み優先順位A : CTC > SIO > PIO (レジスタ初期値) */
#define INTPR_PR_B      0x01    /* 割込み優先順位B : SIO > CTC > PIO */
#define INTPR_PR_C      0x02    /* 割込み優先順位C : CTC > PIO > SIO */
#define INTPR_PR_D      0x03    /* 割込み優先順位D : PIO > SIO > CTC */
#define INTPR_PR_E      0x04    /* 割込み優先順位E : PIO > CTC > SIO */
#define INTPR_PR_F      0x05    /* 割込み優先順位F : SIO > PIO > CTC */

/*********************************************/
/******  アセンブラ関連(All inline)  ******/
// NOP
void NOP();
// EI(割込み有効)
void EI();
// DI(割込みマスク)
void DI();
/*********************************************/

#endif /* _TMPZ84C015_H_ */