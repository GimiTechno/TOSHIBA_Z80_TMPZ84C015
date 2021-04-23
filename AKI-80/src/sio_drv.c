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
    SIO_A_CMD.REG.BYTE = SIO_CMD_RESET;                  // SIO A リセット

    // WR1(割込み有効・無効)
    SIO_A_CMD.REG.BYTE = SIO_WR1;
#ifdef SIO_INT_ENABLE
    SIO_A_CMD.REG.BYTE |= (WR1_BIT_4_RX_INT_MODE_H    /* 受信割込み */
                            | WR1_BIT_1_TX_INT_ENABLE   /* 送信割込み */
                            | WR1_BIT_0_INT_ENABLE);     /* 外部割込み */
#else
    SIO_A_CMD.REG.BYTE &= ~(WR1_BIT_4_RX_INT_MODE_H /* 受信割込み */
                            | WR1_BIT_1_TX_INT_ENABLE   /* 送信割込み */
                            | WR1_BIT_0_INT_ENABLE);    /* 外部割込み */
#endif

    // WR2(割込み要因・割込みベクタ)
#ifdef SIO_INT_ENABLE
    SIO_A_CMD.REG.BYTE |= SIO_A_WR2_BIT_3_2_RX_CHAR; // 受信割込み
    SIO_B_CMD.REG.BYTE |= SIO_B_WR2_BIT_3_RX_CHAR;   //受信割込み
#endif

    // WR3
    SIO_A_CMD.REG.BYTE = SIO_WR3;
    SIO_A_CMD.REG.BYTE |= (WR3_BIT_7_RX_CHAR_LENGTH_H // 受信データ長8bit
                            | WR3_BIT_0_RX_ENABLE);   // 受信 有効

    // WR4
    SIO_A_CMD.REG.BYTE = SIO_WR4;
    SIO_A_CMD.REG.BYTE |= (WR4_BIT_6_CLOCK_MODE_L     // Clock = x16
                            | WR4_BIT_2_STOP_BIT_L);  // ストップビット 1

    // WR5
    SIO_A_CMD.REG.BYTE = SIO_WR5;                    // WR5選択
#ifdef SIO_DTR_RTS_ENABLE
    // 2021年現在、フロー制御はいらんからNOP
    // NOP
#else
    SIO_A_CMD.REG.BYTE |=  (WR5_BIT_6_TX_CHAR_LENGTH_H // 送信データ 8bit(bit6,5=1)
                            | WR5_BIT_5_TX_CHAR_LENGTH_L
                            | WR5_BIT_3_TX_ENABLE);   // 送信有効
#endif

#if 0
    /* -------------------------------------------------------------------------------- */
    /* SIO B 初期化 */
    /* -------------------------------------------------------------------------------- */
    SIO_B_CMD = SIO_CMD_RESET;                  // リセット
#endif
}

/**
 * @brief SIO A データレジスタに1byteデータセット
 * 
 * @param p_tx_buf 送信バッファポインタ
 * @param len      送信データ長
 */
u1 drv_sio_tx( u1 *p_tx_buf, u2 len)
{
    u1 ret = TX_OK;
    u1 val;
    u2 tx_size;

    // 送信データ長まですべて送信
    for(tx_size = 0; tx_size < len; tx_size++)
    {

#if 0 /* フレーミングエラー */
        // RR1選択
        SIO_A_CMD.REG.BYTE = SIO_RR1;
        // RR1 bit6(送信フレーミングエラー) 読み込み
        val = SIO_A_CMD.REG.BIT.B6;

        // フレーミングエラー発生時
        if(val != FALSE)
        {
            ret = TX_ERR;
            break;
        }
#endif
        ret = TX_OK;

        // RR0選択
        SIO_A_CMD.REG.BYTE = SIO_RR0;
        // RR0 bit2(送信バッファ空き状態フラグ) 読み込み
        val = SIO_A_CMD.REG.BIT.B2;

        // 送信バッファが空き待ち
        while(val != TRUE)
        {
            val = SIO_A_CMD.REG.BIT.B2;
        }

        DI();
        // SIO A データレジスタに1Byteデータ詰め込み
        PIO_A_DAT.REG.BYTE = *p_tx_buf;
        p_tx_buf++;
        EI();
    }

    return (ret);
}

/**
 * @brief SIO A データレジスタからデータ取得
 * 
 * @param p_rx_buf  受信バッファポインタ
 * @param len       受信データ長
 */
u1 drv_sio_rx( u1 *p_rx_buf, u2 len )
{
    u1 ret;
    u1 val;

    ret = RX_OK;

    // RR0選択
    SIO_A_CMD.REG.BYTE = SIO_RR0;
    // RR0 bit0(データ受信フラグ)読み込み
    val = SIO_A_CMD.REG.BIT.B0;

    // 受信データがある間データ詰める
    while( val != FALSE ){
        // SIO A データレジスタからデータ取得
        *p_rx_buf = PIO_A_DAT.REG.BYTE;
        p_rx_buf++;
        len++;

        // RR0選択
        SIO_A_CMD.REG.BYTE = SIO_RR0;
        // RR0 bit0(データ受信フラグ)読み込み
        val = SIO_A_CMD.REG.BIT.B0;
    }

    return (ret);
}