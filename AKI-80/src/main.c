#include <stdio.h>
//#include <string.h>

// APP Inc
#include "common.h"
#include "lib.h"

/* マクロ */
#define DEBUG_Z80
#define TX_BUF_SIZE	8
#define RX_BUF_SIZE	8

/* 関数宣言 */
// XCC-Vコンパイラ専用
#if (C_COMPILER == COMPILER_XCC_V)
global main();
#endif

extern void* lib_memset(void *a_buf, uint8 val,size_t size);
extern void NOP();
static void app_init(void);

/* 変数宣言 */
// const uint8 *g_msgbuf = "TMPZ84C015BF-8 KBC-Z05";
uint8 g_txbuf[TX_BUF_SIZE] = {0};
uint8 g_rxbuf[RX_BUF_SIZE] = {0};

static void app_init(void)
{
	MEMSET(&g_txbuf[0],0x00,sizeof(g_txbuf));
	MEMSET(&g_rxbuf[0],0x00,sizeof(g_rxbuf));
}

main()
{
    //uint32 cnt;

	// 初期化処理
	app_init();

    // メインループ
    while (1)
    {
        NOP();
#ifdef DEBUG_Z80
        //cnt++;
#endif
    }

    return 0;
}