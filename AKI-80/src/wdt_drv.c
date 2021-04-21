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
    REG_WDTCR = WDT_CLEAR;
}

/**
 * @brief WDTスタート
 * 
 */
void drv_wdt_start(void)
{
    // WDT有効（Bit7セット）
    REG_WDTER |= BIT_7;
}

/**
 * @brief WDTストップ
 * 
 */
#pragma inline drv_wdt_stop
void drv_wdt_stop(void)
{
    // WDT無効（Bit7クリア）
    REG_WDTER &= ~BIT_7;

    NOP();

    // WDT動作停止
    REG_WDTCR = WDT_STOP;
}