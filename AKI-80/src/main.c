#include <stdio.h>
//#include <string.h>

// DRV Inc
#include "ctc.h"
#include "sio.h"
#include "pio.h"
#include "wdt.h"

// APP Inc
#include "common.h"
#include "lib.h"

/* マクロ */
#define DEBUG_Z80

/* 関数宣言 */
// XCC-Vコンパイラ専用
#if (C_COMPILER == COMPILER_XCC_V)
global main();
#endif

extern void* lib_memset(void *a_buf, uint8 val,size_t size);
extern void NOP();
static void app_hw_init(void);
static void app_init(void);

/* 変数宣言 */


/**
 * @brief H/W初期化
 * 
 */
static void app_hw_init(void)
{
    /* CTC 初期化 */
    drv_ctc_init();

    /* PIO 初期化 */
    drv_pio_init();

    /* SIO 初期化 */
    drv_sio_init();

    /* WDT 初期化 */
    drv_wdt_init();
}

/**
 * @brief アプリ初期化
 * 
 */
static void app_init(void)
{
    //
}

/**
 * @brief メインループ
 * 
 */
main()
{
    DI();
    app_hw_init();
    EI();

	// アプリ初期化処理
	app_init();

    // メインループ
    while (1)
    {
        sio_main();
    }

    return 0;
}