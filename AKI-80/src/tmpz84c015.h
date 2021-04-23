#ifndef _TMPZ84C015_H_
#define _TMPZ84C015_H_

#include "common.h"

/* ------------------------------------------ */
/*            コンパイルスイッチ               */
/* ------------------------------------------ */
#define DEBUG_Z80            /* デバッグ、テストロジック有効 */
// #define INT_ENABLE           /* 割込み有効 */
#define WDT_ENABLE           /* WDT有効 */

#ifdef INT_ENABLE
    #define CTC_INT_ENABLE   /* PIO 割り込み有効 */
    #define SIO_INT_ENABLE   /* SIO 割り込み有効 */
    #define PIO_INT_ENABLE   /* PIO 割り込み有効 */
#endif

/* ------------------------------------------ */
/*                  H/W関連                   */
/* ------------------------------------------ */

/*****************************************************/
/**********       I/O Addr Define          **********/
/*****************************************************/
// CTC
#define CTC_0       (*(volatile struct reg_t *)0x10)      /* CTC0 */
#define CTC_1       (*(volatile struct reg_t *)0x11)      /* CTC1 */
#define CTC_2       (*(volatile struct reg_t *)0x12)      /* CTC2 */
#define CTC_3       (*(volatile struct reg_t *)0x13)      /* CTC3 */

// SIO
#define SIO_A_DAT   (*(volatile struct reg_t *)0x18)      /* SIO A Data    */
#define SIO_A_CMD   (*(volatile struct reg_t *)0x19)      /* SIO A Command */
#define SIO_B_DAT   (*(volatile struct reg_t *)0x1A)      /* SIO B Data    */
#define SIO_B_CMD   (*(volatile struct reg_t *)0x1B)      /* SIO B Command */

// PIO
#define PIO_A_DAT   (*(volatile struct reg_t *)0x1C)      /* PIO A Data    */
#define PIO_A_CMD   (*(volatile struct reg_t *)0x1D)      /* PIO A Command */
#define PIO_B_DAT   (*(volatile struct reg_t *)0x1E)      /* PIO B Data    */
#define PIO_B_CMD   (*(volatile struct reg_t *)0x1F)      /* PIO B Command */

// WDT
#define WDTER       (*(volatile struct reg_t *)0xF0)      /* WDTER ... WDT許可レジスタ */
#define WDTCR       (*(volatile struct reg_t *)0xF1)      /* WDTCR ... WDT制御レジスタ */

// 割込み
#define INTPR       (*(volatile struct reg_t *)0xF4)      /* INTPR ... 割込み優先順位レジスタ */
/*****************************************************/

/* INTPR */
#define INTPR_PR_A      0x00    /* 割込み優先順位A : CTC > SIO > PIO (初期値) */
#define INTPR_PR_B      0x01    /* 割込み優先順位B : SIO > CTC > PIO         */
#define INTPR_PR_C      0x02    /* 割込み優先順位C : CTC > PIO > SIO         */
#define INTPR_PR_D      0x03    /* 割込み優先順位D : PIO > SIO > CTC         */
#define INTPR_PR_E      0x04    /* 割込み優先順位E : PIO > CTC > SIO         */
#define INTPR_PR_F      0x05    /* 割込み優先順位F : SIO > PIO > CTC         */

#define __Interrput__

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