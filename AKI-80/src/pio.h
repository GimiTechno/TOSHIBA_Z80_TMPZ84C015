#ifndef _PIO_Z84C015_H_
#define _PIO_Z84C015_H_

#include "tmpz84c015.h"
#include "common.h"

/* ------------------------------------------ */
/* SIO Command Table */
/* ------------------------------------------ */
#define PIO_CMD_PORT_INPUT_MODE      0x4F   /* Port Input Mode */
#define PIO_CMD_PORT_OUTPUT_MODE     0x0F   /* Port Output Mode */

extern void drv_pio_init( void );

#endif /* _PIO_Z84C015_H_ */