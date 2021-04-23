#ifndef _SIO_Z84C015_H_
#define _SIO_Z84C015_H_

#include "tmpz84c015.h"
#include "common.h"

/* -------------------------------------------------------------------------------- */
/* Write Registers */
/* -------------------------------------------------------------------------------- */
/* WR0(Write Register 0) ...  リセット,CRC */
#define SIO_WR0                         0x00
/* WR1(Write Register 1) ...  割り込みモード設定 */
#define SIO_WR1                         0x01
/* WR2(Write Register 2) ...  割込み時に送信されるベクトルの設定 */
#define SIO_WR2                         0x02
/* WR3(Write Register 3) ...  受信パラメータ設定 */
#define SIO_WR3                         0x03
/* WR4(Write Register 4) ...  送受信パラメータ設定 */
#define SIO_WR4                         0x04
/* WR5(Write Register 5) ...  送信制御 */
#define SIO_WR5                         0x05
/* WR6(Write Register 6) ...  同期文字またはSDLCアドレスフィールドの設定 */
#define SIO_WR6                         0x06
/* WR7(Write Register 7) ...  同期文字またはSDLCフラグの設定*/
#define SIO_WR7                         0x07

/* -------------------------------------------------------------------------------- */
/* Read Registers */
/* -------------------------------------------------------------------------------- */
/* RR0(Read Register 0) ...  受信/送信バッファとピンのステータス */
#define SIO_RR0                         0x00
/* RR1(Read Register 1) ...  エラーステータスとフレーム終了コード */
#define SIO_RR1                         0x01
/* RR2(Read Register 2) ...  割り込みベクタの内容（チャネルBのみ） */
#define SIO_RR2                         0x02

/* -------------------------------------------------------------------------------- */
/* ライトレジスタビット                                                                    */
/* -------------------------------------------------------------------------------- */

/* WR0 */
/* --------------------------------------- */


/* WR1 (割込み有効・無効) */
/* --------------------------------------- */
#define WR1_BIT_4_RX_INT_MODE_H             BIT_4
#define WR1_BIT_3_RX_INT_MODE_L             BIT_3
#define WR1_BIT_2_STATUS_AFFECT_VECTOR      BIT_2
#define WR1_BIT_1_TX_INT_ENABLE             BIT_1
#define WR1_BIT_0_INT_ENABLE                BIT_0

/* WR2 (割込み要因・割込みベクタ) */
/* --------------------------------------- */
/* --- SIO A --- */
// 受信完了で割込み
#define SIO_A_WR2_BIT_3_2_RX_CHAR             (BIT_3 | BIT_2)
// SIOエラーで割込み
// SIOエラー ... パリティ(フロー制御) or オーバラン(受信) or フレーミングエラー（送信）
#define SIO_A_WR2_BIT_3_2_1_SIO_ERROR         (BIT_3 | BIT_2 | BIT_1)
// #DCD,#CTS,#SYNCのピンがアサートされたとき割込み
#define SIO_A_WR2_BIT_3_1_CHG_EX_STATUS       (BIT_3 | BIT_1)
// 送信完了で割込み
#define SIO_A_WR2_BIT_3_TX_BUF_EMPTY           BIT_3

/* --- SIO B --- */
// 受信完了で割込み
#define SIO_B_WR2_BIT_3_RX_CHAR             BIT_3
// SIOエラーで割込み
// SIOエラー ... パリティ(フロー制御) or オーバラン(受信) or フレーミングエラー（送信）
#define SIO_B_WR2_BIT_2_1_SIO_ERROR         (BIT_2 | BIT_1)
// #DCD,#CTS,#SYNCのピンがアサートされたとき割込み
#define SIO_B_WR2_BIT_2_CHG_EX_STATUS       BIT_2
// 送信完了で割込み
#define SIO_B_WR2_BIT_1_TX_BUF_EMPTY        BIT_1
/* --------------------------------------- */

/* WR3 (機能有効) */
/* --------------------------------------- */
// 受信データ長(D7,D6=1で8bit)
#define WR3_BIT_7_RX_CHAR_LENGTH_H          BIT_7
#define WR3_BIT_6_RX_CHAR_LENGTH_L          BIT_6
#define WR3_BIT_5_AUTO_ENABLE               BIT_5

#define WR3_BIT_4_ENTER_HUNT_PHASE          BIT_4
#define WR3_BIT_3_RX_CRC                    BIT_3
#define WR3_BIT_2_ADDR_SERCH_MODE           BIT_2
#define WR3_BIT_1_SYNC_CHAR                 BIT_1

// 受信有効
#define WR3_BIT_0_RX_ENABLE                 BIT_0

/* WR4 （制御） */
/* --------------------------------------- */
// クロック(0b11=x64, 0b10=x32,0b01=x16,0b00=x1)
#define WR4_BIT_7_CLOCK_MODE_H              BIT_7
#define WR4_BIT_6_CLOCK_MODE_L              BIT_6

// 同期モード(8bit同期でいいのでこのビットは無視)
#define WR4_BIT_5_SYNC_MODE_H               BIT_5
#define WR4_BIT_4_SYNC_MODE_L               BIT_4

// ストップビット(ストップビット1 = Bit2 .. 1)
#define WR4_BIT_3_STOP_BIT_H                BIT_3
#define WR4_BIT_2_STOP_BIT_L                BIT_2

// パリティ odd = 1, even = 0
#define WR4_BIT_1_PARITY_ENABLE_H           BIT_1
// パリティ有効
#define WR4_BIT_0_PARITY_ENABLE             BIT_0

/* WR5 */
/* --------------------------------------- */
#define WR5_BIT_7_DTR                       BIT_7

// 送信データ長(Bit6,5 = 1 ... 8bit)
#define WR5_BIT_6_TX_CHAR_LENGTH_H          BIT_6
#define WR5_BIT_5_TX_CHAR_LENGTH_L          BIT_5

#define WR5_BIT_4_BREAK                     BIT_4
// 送信有効
#define WR5_BIT_3_TX_ENABLE                 BIT_3
#define WR5_BIT_2_CRC16_SDLC                BIT_2
#define WR5_BIT_1_RTS                       BIT_1
#define WR5_BIT_0_CRC_ENABLE                BIT_0

/* WR6 */
/* --------------------------------------- */
// どうでもいいレジスタ(同期)

/* WR7 */
/* --------------------------------------- */
// どうでもいいレジスタ(同期)

/* -------------------------------------------------------------------------------- */
/* リードレジスタビット                                                                    */
/* -------------------------------------------------------------------------------- */
// RR0 (正常系の状態)
/* --------------------------------------- */
#define RR0_BIT_7_BREAK_ABOTR               BIT_7
#define RR0_BIT_6_TX_UNDERRUN_EOM           BIT_6
#define RR0_BIT_5_CTS                       BIT_5
#define RR0_BIT_4_SYNC_ZERO_HUNT            BIT_4
#define RR0_BIT_3_DCD                       BIT_3
// 送信バッファ空
#define RR0_BIT_2_TX_BUF_EMPTY              BIT_2
// 保留中の割込みあり
#define RR0_BIT_1_INTR_PENDING              BIT_1
// データ受信あり
#define RR0_BIT_0_RX_CHAR                   BIT_0

// RR1 (異常系の状態)
/* --------------------------------------- */
#define RR0_BIT_6_TX_FLAMING_ERR           BIT_6
#define RR0_BIT_5_RX_OVERRUN_ERR           BIT_5
#define RR0_BIT_4_PARITY_ERR               BIT_4

// RR2
/* --------------------------------------- */

/* -------------------------------------------------------------------------------- */
/* SIO Command Table */
/* -------------------------------------------------------------------------------- */
#define SIO_CMD_RESET                       0x18

/* -------------------------------------------------------------------------------- */

typedef enum {
    // 正常系
    TX_OK = 0x00,      // 送信完了
    RX_OK,             // 受信完了

    // 異常系
    TX_ERR = 0xFE,     // 送信エラー（フレーミングエラー）
    RX_ERR,            // 受信エラー(オーバラン)
} E_SIO_STATE;

void drv_sio_init( void );
u1 drv_sio_tx( u1 *p_tx_buf, u2 len );
u1 drv_sio_rx( u1 *p_rx_buf, u2 len );

#endif /* _SIO_Z84C015_H_ */