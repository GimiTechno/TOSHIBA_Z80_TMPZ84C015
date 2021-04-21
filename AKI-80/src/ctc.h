#ifndef _CTC_Z84C015_H_
#define _CTC_Z84C015_H_

#include "tmpz84c015.h"
#include "common.h"

/* ------------------------------------------ */
/* CTC Command Table */
/* ------------------------------------------ */
#define CTC_CMD_PSR_1DIV16        0x07  /* タイマモード ( プリスケーラ 1/16 ) */
#define CTC_CMD_CLOCK_DIV_1P5     0x05   /* クロック分周1/5*/

extern void drv_ctc_init( void );

#endif /* _CTC_Z84C015_H_ */