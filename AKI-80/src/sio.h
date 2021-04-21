#ifndef _SIO_Z84C015_H_
#define _SIO_Z84C015_H_

#include "tmpz84c015.h"
#include "common.h"

#define SIO_INT_ENABLE       /* 送受信割込み 有効 */
// #define SIO_DTR_RTS_ENABLE       /* DTR,RTS 有効 */

/* -------------------------------------------------------------------------------- */
/* Write Registers */
/* -------------------------------------------------------------------------------- */
/* WR0(Write Register 0) ...  リセット,CRC */
#define SIO_REG_WR0                         0x00
/* WR1(Write Register 1) ...  割り込みモード設定 */
#define SIO_REG_WR1                         0x01
/* WR2(Write Register 2) ...  割込み時に送信されるベクトルの設定 */
#define SIO_REG_WR2                         0x02
/* WR3(Write Register 3) ...  受信パラメータ設定 */
#define SIO_REG_WR3                         0x03
/* WR4(Write Register 4) ...  送受信パラメータ設定 */
#define SIO_REG_WR4                         0x04
/* WR5(Write Register 5) ...  送信制御 */
#define SIO_REG_WR5                         0x05
/* WR6(Write Register 6) ...  同期文字またはSDLCアドレスフィールドの設定 */
#define SIO_REG_WR6                         0x06
/* WR7(Write Register 7) ...  同期文字またはSDLCフラグの設定*/
#define SIO_REG_WR7                         0x07

/* -------------------------------------------------------------------------------- */
/* Read Registers */
/* -------------------------------------------------------------------------------- */
/* RR0(Read Register 0) ...  受信/送信バッファとピンのステータス */
#define SIO_REG_RR0                         0x00
/* RR1(Read Register 1) ...  エラーステータスとフレーム終了コード */
#define SIO_REG_RR1                         0x00
/* RR2(Read Register 2) ...  割り込みベクタの内容（チャネルBのみ） */
#define SIO_REG_RR2                         0x00

/* -------------------------------------------------------------------------------- */
/* SIO Command Table */
/* -------------------------------------------------------------------------------- */
#define SIO_CMD_RESET                       0x18
#define SIO_CMD_INT_ENABLE                  0x12
#define SIO_CMD_RX_INT_DISABLE              0x02
#define SIO_CMD_TX_INT_DISABLE              0x10
#define SIO_CMD_RX_ENABLE                   0xC1
#define SIO_CMD_DTR_RTS_ENABLE              0xEA
#define SIO_CMD_DTR_RTS_DISABLE             0x68
#define SIO_CMD_CLOCK_X16_STOPBIT_1         0x44
#define SIO_CMD_STATUS_AFFECTS_VECTOR       0x04
#define SIO_CMD_INT_VECTOR_LOWWER           0x50
#define SIO_CMD_TX_INT_RESET                0x28

#define RR0_TXEMPTY    0x04    // 第2ビットが送信バッファ空ビット

#define TX_BUF_SIZE    128    // 送信リングバッファサイズ
#define RX_BUF_SIZE    128    // 受信リングバッファサイズ
#define CMD_BUF_SIZE    30    // 送受信コマンド（パケット）サイズ

#define RX_OK           0x01  // 受信完了
#define RX_NOW          0x00  // 受信中
#define RX_NG           0xFF  // 受信バッファOVF(≒オーバラン)

extern void drv_sio_init( void );
extern void drv_sio_tx( uint8 * );
extern uint16 drv_sio_a_rx( void );

#define PIO_PRINT   drv_sio_tx

#endif /* _SIO_Z84C015_H_ */