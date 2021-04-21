/*****************************************************/
/* For AKI-80 (TMPZ84C015BF-12 @12.288MHz)           */
/*---------------------------------------------------*/
/* 【SIO A】                                         */
/* 1) ボーレート : 9600bps                           */
/* 2) CTC        : CTC0ボーレートジェネレータに仕様  */
/* 3) 割込み     : 未使用、ポーリング                */
/*---------------------------------------------------*/
/* 【SIO B】                                         */
/* 未使用                                            */
/*****************************************************/

#include "sio.h"
#include "lib.h"

/**
 * @brief SIO初期化ドライバ
 * 
 */
void drv_sio_init( void )
{
    /* -------------------------------------------------------------------------------- */
    /* SIO A 初期化 */
    /* -------------------------------------------------------------------------------- */
    REG_SIO_A_CMD = SIO_CMD_RESET;                  // SIO A リセット

    // WR1
    REG_SIO_A_CMD = SIO_REG_WR1;
#ifdef SIO_INT_ENABLE
    REG_SIO_A_CMD = SIO_CMD_INT_ENABLE;             // 割込み許可
#else
    #ifdef SIO_TX_INT_DISABLE
        REG_SIO_A_CMD = SIO_CMD_TX_INT_DISABLE;     // 割込み許可(送信割込み不可）
    #endif

    #ifdef SIO_RX_INT_DISABLE
        REG_SIO_A_CMD = SIO_CMD_RX_INT_DISABLE;     // 割込み許可(受信割込み不可）
    #endif
#endif

    // WR3
    REG_SIO_A_CMD = SIO_REG_WR3;
    REG_SIO_A_CMD = SIO_CMD_RX_ENABLE;              // 受信 有効

    // WR4
    REG_SIO_A_CMD = SIO_REG_WR4;
    REG_SIO_A_CMD = SIO_CMD_CLOCK_X16_STOPBIT_1;    // ボーレート = Clock ×16 , ストップビット 1

    // WR5
    REG_SIO_A_CMD = SIO_REG_WR5;                    // WR5選択
#ifdef SIO_DTR_RTS_ENABLE
    REG_SIO_A_CMD = SIO_CMD_DTR_RTS_ENABLE;         // DTR,RTS 有効
#else
    REG_SIO_A_CMD = SIO_CMD_DTR_RTS_DISABLE;        // DTR,RTS 無効
#endif

#if 0
    /* -------------------------------------------------------------------------------- */
    /* SIO B 初期化 */
    /* -------------------------------------------------------------------------------- */
    REG_SIO_B_CMD = SIO_CMD_RESET;                  // リセット

    // WR1
    REG_SIO_B_CMD = SIO_REG_WR1;
    REG_SIO_B_CMD = SIO_CMD_STATUS_AFFECTS_VECTOR;  // Status Affects Vector

    // WR2
    REG_SIO_B_CMD = SIO_REG_WR2;
    REG_SIO_B_CMD = SIO_CMD_INT_VECTOR_LOWWER;       // 割込みベクタ（下位）
#endif
}

/**
 * @brief SIO A データレジスタに1byteデータセット
 * 
 * @param p_tx_buf 送信バッファポインタ
 * @param len      送信データ長
 */
void drv_sio_tx( uint8 *p_tx_buf, uint16 len)
{
    uint8 val;
    uint16 tx_size;

    // 送信データ長まですべて送信
    for(tx_size = 0; tx_size < len; tx_size++)
    {
        REG_SIO_A_CMD = SIO_REG_RR0;    // RR0選択
        val = REG_SIO_A_CMD;            // RR0読み込み

        // 送信バッファが空き待ち
        while( ! (val & RR0_BIT_2_TXEMPTY)  )
        {
            NOP();
        }

        DI();
        // SIO A データレジスタに1Byteデータ詰め込み
        REG_PIO_A_DAT = *p_tx_buf;
        p_tx_buf++;
        EI();
    }
}

/**
 * @brief SIO A データレジスタからデータ取得
 * 
 * @param p_rx_buf  受信バッファポインタ
 * @param len       受信データ長
 */
void drv_sio_rx( uint8 *p_rx_buf, uint16 len )
{
    uint8 val;

    REG_SIO_A_CMD = SIO_REG_RR0;    // RR0選択
    val = REG_SIO_A_CMD;            // RR0読み込み

    // 受信データがある間データ詰める
    while( val & RR0_BIT_0_RX_CAHRACTER_AVAILABLE ){
        // SIO A データレジスタからデータ取得
        *p_rx_buf = REG_PIO_A_DAT;
        p_rx_buf++;
        len++;
    }
}