#ifndef _PIO_Z84C015_H_
#define _PIO_Z84C015_H_

#include "tmpz84c015.h"
#include "common.h"

// PIO Port駆動
#define PORT_HIGH    0x00                           /* Port High ... 0x00 = output */
#define PORT_LOW     0x01                           /* Port Low  ... 0x01 = input  */

/* ------------------------------------------ */
/* PIO Command Table */
/* ------------------------------------------ */
#define PIO_CMD_PORT_MODE_0_OUTPUT_MODE     0x0F    /* Mode0 ... Byte Output Mode */
#define PIO_CMD_PORT_MODE_1_INPUT_MODE      0x4F    /* Mode1 ... Byte Input Mode  */
#define PIO_CMD_PORT_MODE_2_BYTE_IO_MODE    0x8F    /* Mode2 ... Byte I/O Mode    */
#define PIO_CMD_PORT_MODE_3_BIT_IOMODE      0xCF    /* Mode3 ... Bit I/O Mode     */

void drv_pio_init( void );

#endif /* _PIO_Z84C015_H_ */