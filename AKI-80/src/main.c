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
#define TX_BUF_SIZE    32    // 送信バッファサイズ
#define RX_BUF_SIZE    128    // 受信バッファサイズ

/* 関数宣言 */
// XCC-Vコンパイラ専用
#if (C_COMPILER == COMPILER_XCC_V)
global main();
#endif

extern void* lib_memset(void *a_buf, u1 val,size_t size);
extern void NOP();
static void app_hw_init(void);
static void app_init(void);
static void app_sio_main(void);

#ifdef DEBUG_Z80
static void port_test(void);
#endif


/* 変数宣言 */
static u1 s_tx_buf[TX_BUF_SIZE];     /* SIO TXバッファ */
static u1 s_rx_buf[RX_BUF_SIZE];     /* SIO RXバッファ */

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
#ifdef DEBUG_Z80
    u2 cnt;

    // SIO送受信バッファ初期化
    lib_memset(&s_tx_buf[0], 0x00 ,sizeof(s_tx_buf));
    lib_memset(&s_rx_buf[0], 0x00 ,sizeof(s_rx_buf));

    // SIO送信バッファにテストデータ詰め込み
    for(cnt = 0; cnt < (u1)sizeof(s_tx_buf); cnt++)
    {
        DI();
        s_tx_buf[cnt] = cnt;
        EI();
    }
#endif
}

/**
 * @brief SIO ポーリングメイン
 * 
 */
static void app_sio_main(void)
{
#ifdef DEBUG_Z80
    u2 rx_len;

    // 受信確認&データ受信
    drv_sio_rx(&s_rx_buf[0], rx_len);

    // 何も受信がなければ
    if(rx_len != 0)
    {
        // SIOドライバに送信バッファを渡して送信
        drv_sio_tx(&s_tx_buf[0], sizeof(s_tx_buf));
    }
#endif
}


#ifdef DEBUG_Z80
static void port_test(void)
{
#if 1
        PIO_A_DAT.REG.BIT.B7 = ~PIO_A_DAT.REG.BIT.B7;
        PIO_A_DAT.REG.BIT.B6 = ~PIO_A_DAT.REG.BIT.B6;
        PIO_A_DAT.REG.BIT.B5 = ~PIO_A_DAT.REG.BIT.B5;
        PIO_A_DAT.REG.BIT.B4 = ~PIO_A_DAT.REG.BIT.B4;
        PIO_A_DAT.REG.BIT.B3 = ~PIO_A_DAT.REG.BIT.B3;
        PIO_A_DAT.REG.BIT.B2 = ~PIO_A_DAT.REG.BIT.B2;
        PIO_A_DAT.REG.BIT.B1 = ~PIO_A_DAT.REG.BIT.B1;
        PIO_A_DAT.REG.BIT.B0 = ~PIO_A_DAT.REG.BIT.B0;

        PIO_B_DAT.REG.BIT.B7 = ~PIO_B_DAT.REG.BIT.B7;
        PIO_B_DAT.REG.BIT.B6 = ~PIO_B_DAT.REG.BIT.B6;
        PIO_B_DAT.REG.BIT.B5 = ~PIO_B_DAT.REG.BIT.B5;
        PIO_B_DAT.REG.BIT.B4 = ~PIO_B_DAT.REG.BIT.B4;
        PIO_B_DAT.REG.BIT.B3 = ~PIO_B_DAT.REG.BIT.B3;
        PIO_B_DAT.REG.BIT.B2 = ~PIO_B_DAT.REG.BIT.B2;
        PIO_B_DAT.REG.BIT.B1 = ~PIO_B_DAT.REG.BIT.B1;
        PIO_B_DAT.REG.BIT.B0 = ~PIO_B_DAT.REG.BIT.B0;
#else
        PIO_A_DAT.REG.BYTE = ~PIO_A_DAT.REG.BYTE;
        PIO_B_DAT.REG.BYTE = ~PIO_B_DAT.REG.BYTE;
#endif
}
#endif

/**
 * @brief メインループ
 * 
 */
main()
{
    u1 tmp;

    DI();
    app_hw_init();
    EI();

#ifdef WDT_ENABLE
        WDT_CLR();
#endif

	// アプリ初期化処理
	app_init();

    // メインループ
    while (1)
    {
        // SIO Main (Polling)
        app_sio_main();

#ifdef DEBUG_Z80
        // Port Test All Port Toggle
        port_test();
#endif

#ifdef WDT_ENABLE
        WDT_CLR();
#endif
    }
}