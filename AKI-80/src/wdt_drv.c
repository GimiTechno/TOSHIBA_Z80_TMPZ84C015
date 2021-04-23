#include "wdt.h"

/**
 * @brief WDT初期化
 * 
 */
void drv_wdt_init(void)
{
    //
}

/**
 * @brief WDTクリア
 * 
 */
#pragma inline drv_wdt_clear
void drv_wdt_clear(void)
{
    WDTCR.REG.BYTE = WDT_CLEAR;
}

/**
 * @brief WDTスタート
 * 
 */
void drv_wdt_start(void)
{
    // WDT有効（Bit7セット）
    WDTER.REG.BIT.B7 = ON;
}

/**
 * @brief WDTストップ
 * 
 */
#pragma inline drv_wdt_stop
void drv_wdt_stop(void)
{
    // WDT無効（Bit7クリア）
    WDTER.REG.BIT.B7 = OFF;

    NOP();

    // WDT動作停止
    WDTCR.REG.BYTE = WDT_STOP;
}