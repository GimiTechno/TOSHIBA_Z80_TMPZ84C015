#ifndef _WDT_H_
#define _WDT_H_

#include "tmpz84c015.h"
#include "common.h"

/*****************************************************/
/*******    WDTERレジスタ（WR, I/O Addr #F0）  *******/
/*****************************************************/

/* WDTER(Bit[7]) ... WDT許可ビット */
#define WDTER_BIT_7_WDTER_ENABLE            0x80    /* WDT動作有効 */
#define WDTER_BIT_7_WDTER_DISABLE           0x00    /* WDT動作無効 (レジスタ初期値) */

/* WDTPR(Bit[6:5]) ... WDT周期ビット */
#define WDTER_BIT_6_5_WDTPR_TCC_X2_16       0x00    /* TCC(クロック) x 2^16 経過でOVF  (レジスタ初期値)*/
#define WDTER_BIT_6_5_WDTPR_TCC_X2_18       0x20    /* TCC(クロック) x 2^18 経過でOVF */
#define WDTER_BIT_6_5_WDTPR_TCC_X2_20       0x40    /* TCC(クロック) x 2^20 経過でOVF */
#define WDTER_BIT_6_5_WDTPR_TCC_X2_22       0x60    /* TCC(クロック) x 2^22 経過でOVF */

/* HALTMR(Bit[4:3]) ... HALTモードビット */

/* Bit[2:0]) ... 0b011(0x03)固定 */
#define WDTER_BIT_2_1_0                     0x03

/*****************************************************/
/*******    WDTCRレジスタ（WO, I/O Addr #F1）  *******/
/*****************************************************/
/* WDTクリア */
// WDTCRレジスタに0x4Eを書き込むとWDTがクリアされる
#define WDT_CLEAR       0x4E

/* WDT動作停止 */
// 1) WDTERレジスタを無効(Bit7=0)にする
// 2) WDTCRレジスタに0xB1を書き込む
// 3) WDTが動作停止
#define WDT_STOP        0xB1

void drv_wdt_init(void);
void drv_wdt_clear(void);
void drv_wdt_start(void);
void drv_wdt_stop(void);

#define WDT_CLR()     drv_wdt_clear()

#endif /* _WDT_H_ */