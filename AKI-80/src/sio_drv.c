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

static volatile uint8    g_rx_buf[RX_BUF_SIZE];    // 受信リングバッファ
static volatile uint8    g_rx_cmd_buf[CMD_BUF_SIZE + 1];    // 受信コマンド（パケット）バッファ
static volatile uint16    g_rx_data_len;    // 受信リングバッファに格納されている有効なデータ数
static volatile uint8    *p_rx_buf_wr_ptr;    // 受信書き込み位置ポインタ
static volatile uint8    *p_rx_buf_rd_ptr;    // 受信読み込み位置ポインタ
static volatile uint8    *p_rx_cmd_buf_wr_ptr;    // 受信コマンド（パケット）バッファ書き込み位置ポインタ

static volatile uint8     g_tx_buf[TX_BUF_SIZE];    // 送信リングバッファ
static volatile uint8    *p_tx_buf_wr_ptr;    // 送信書き込み位置ポインタ
static volatile uint8    *p_tx_buf_rd_ptr;    // 送信読み込み位置ポインタg_rx_data_len
static volatile uint16    g_tx_data_len;        // 送信リングバッファに格納されている有効なデータ数

static void sio_drv_init( void );
static void sio_a_tx( void );

/**
 * @brief DRV Init
 * 
 */
static void sio_drv_init( void )
{
    // 受信リングバッファ初期化
    p_rx_buf_wr_ptr = &g_tx_buf[0];
    p_rx_buf_rd_ptr = &g_rx_buf[0];
    g_rx_data_len = 0;    // 受信データ数を０で初期化
    p_rx_cmd_buf_wr_ptr = g_rx_cmd_buf;

    // 送信リングバッファ初期化
    p_tx_buf_wr_ptr = &g_tx_buf[0];
    p_tx_buf_rd_ptr = &g_tx_buf[0];
    g_tx_data_len = 0;
}

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

    sio_drv_init();
}

/**
 * @brief SIO A データレジスタに1byteデータセット
 * 
 */
static void sio_a_tx( void )
{
    uint8 val;

    // 送信バッファの空きをチェック
    REG_SIO_A_CMD = SIO_REG_RR0;    // RR0選択
    val = REG_SIO_A_CMD;            // RR0読み込み

    // 送信バッファが空でないときは（すぐに割込みが発生するはずなので）
    if( ! (val & RR0_TXEMPTY) ) {
        return;
    }else{
        // 送信データが存在するとき
        if( g_tx_data_len > 0 ) {
            REG_SIO_A_DAT = *p_tx_buf_rd_ptr;
            p_tx_buf_rd_ptr++;

            // リングバッファ処理
            if( p_tx_buf_rd_ptr >= (&g_tx_buf[0] + RX_BUF_SIZE) ) {
                // リードポインタをバッファ先頭
                p_tx_buf_rd_ptr = &g_tx_buf[0];
            }
            g_tx_data_len--;    // １文字送信したので-1
        }
    }
}

/**
 * @brief ドライバ SIO A 送信 I/F
 * 
 * @param p_tx_buf : 送信バッファポインタ
 */
void drv_sio_tx( uint8 *p_tx_buf )
{
    uint8 *p_tx_buf_ptr;
    uint16 len;

    p_tx_buf_ptr = p_tx_buf;
    len = STRLEN( p_tx_buf_ptr );

    // EI();

    while( len >= (TX_BUF_SIZE - g_tx_data_len) )
    {
        // バッファが空くNOPで待ち
        NOP();
    }

    /* -------------------------------------------------------------------------------- */
    // 割込みマスク
    DI();
    /* -------------------------------------------------------------------------------- */
    // 送信コマンド文字列があるとき
    while( *p_tx_buf_ptr )
    {
        *p_tx_buf_wr_ptr = *p_tx_buf_ptr;
        p_tx_buf_wr_ptr++;
        p_tx_buf_ptr++;

        g_tx_data_len++;

        // リングバッファ処理
        if( p_tx_buf_wr_ptr >= (&g_tx_buf[0] + TX_BUF_SIZE) ) {
            // バッファ先頭にライトポインタをセット
            p_tx_buf_wr_ptr = &g_tx_buf[0];
        }
    }
    sio_a_tx();
    /* -------------------------------------------------------------------------------- */
    // 割込み許可
    EI();
    /* -------------------------------------------------------------------------------- */
}

/**
 * @brief  ドライバ SIO A 受信 I/F
 * 
 * @return uint16 : TRUE(0x01) ... 受信OK
 *                  FALSE(0x00) ... 受信中
 */
uint16 drv_sio_a_rx( void )
{
    uint8    delimiter_buf[3];
    uint8    data;
    uint16    ret = RX_OK;

    /* -------------------------------------------------------------------------------- */
    // 割込みマスク
    DI();
    /* -------------------------------------------------------------------------------- */
    // 受信データがないとき
    if( ! g_rx_data_len ) {
        EI();
        return 0 ;
    }else{
        while( g_rx_data_len > 0 )
        {
            g_rx_data_len--;    // １バイト読みだしたので-1
            EI();
            data = *p_rx_buf_rd_ptr;
            p_rx_buf_rd_ptr++;

            // リングバッファ処理
            if( p_rx_buf_rd_ptr >= (&g_rx_buf[0] + RX_BUF_SIZE) ) {
                p_rx_buf_rd_ptr = &g_rx_buf[0];
            }

            // デリミタ
            if( ! data || (data == '\r') || (data == '\n') ) {
                if( data ) {    // 改行コード(\d or \n)のとき
                    {    // --- 確認用データ送信
                        delimiter_buf[0] = '\r';        // CR(\r)
                        delimiter_buf[1] = '\n';        // LF(\n)
                        delimiter_buf[2] = '\0';        // 文字列終端（\0）
                        drv_sio_tx( delimiter_buf );
                    }    // ---

                    *p_rx_cmd_buf_wr_ptr = '\r';        // CR(\r)
                    p_rx_cmd_buf_wr_ptr++;

                    *p_rx_cmd_buf_wr_ptr = '\n';        // LF(\n)
                    p_rx_cmd_buf_wr_ptr++;

                    *p_rx_cmd_buf_wr_ptr = '\0';        // 文字列終端（\0）
                    p_rx_cmd_buf_wr_ptr++;

                } else {
                    *p_rx_cmd_buf_wr_ptr = '\0';        // 文字列終端（\0）
                    p_rx_cmd_buf_wr_ptr++;
                }
                ret = (uint16)(p_rx_cmd_buf_wr_ptr - &g_rx_cmd_buf) - 1;
                p_rx_cmd_buf_wr_ptr = &g_rx_cmd_buf[0];    // 書き込み位置をバッファの先頭へ
                break;        // １コマンド（パケット）受信完了
            } else {    // 終端以外の普通の文字のとき
                {    // --- 確認用データ送信
                    uint8    delimiter_buf[2];
                    delimiter_buf[0] = data;
                    delimiter_buf[1] = '\0';
                    drv_sio_tx( delimiter_buf );
                }    // ---

                if( p_rx_cmd_buf_wr_ptr >= (&g_rx_cmd_buf[0] + (CMD_BUF_SIZE - 2)) ) {    // コマンド受信バッファが最後の２バイトのとき

                    *p_rx_cmd_buf_wr_ptr = '\n';        // LF(\n)
                    p_rx_cmd_buf_wr_ptr++;

                    *p_rx_cmd_buf_wr_ptr = '\0';        // 文字列終端（\0）
                    p_rx_cmd_buf_wr_ptr++;

                    ret = -(uint16)((p_rx_cmd_buf_wr_ptr - g_rx_cmd_buf) - 1);
                    p_rx_cmd_buf_wr_ptr = &g_rx_cmd_buf[0];
                    break;        // １コマンド（パケット）受信完了

                } else {    // コマンド受信バッファにまだ余裕があるとき
                    *p_rx_cmd_buf_wr_ptr = data;
                    p_rx_cmd_buf_wr_ptr++;
                    ret = 0;
                }
            }
            DI();
        }
    }
    /* -------------------------------------------------------------------------------- */
    // 割込み許可
    EI();
    /* -------------------------------------------------------------------------------- */

    return( ret );
}

/**
 * @brief SIO疎通確認(期待値:ローカルエコー)
 * 
 */
void sio_main( void )
{
    uint16 ret;

    ret = drv_sio_a_rx();

    if( ret > 0 ){    // コマンド（パケット）を受信したとき
        PIO_PRINT( g_rx_cmd_buf );    // 受信データを送信
    }else if( ret < 0 ){
        PIO_PRINT( "\r\n" );
        PIO_PRINT( "ERR:Too Many CMD.\r\n" );
    }else{
        /* NOP */
    }
}