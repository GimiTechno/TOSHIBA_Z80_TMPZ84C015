#include "ctc.h"

/**
 * @brief CTC 初期化
 * 
 */
void drv_ctc_init( void )
{
    /* CTC 0 */
#if 0
    // SIO Aのボーレートジェネレータ（9600bps生成）として初期化
    CTC_0.REG.BYTE = CTC_CMD_PSR_1DIV16;         /* タイマモード ( プリスケーラ 1/16 ) */
    CTC_0.REG.BYTE = CTC_CMD_CLOCK_DIV_1P5;      /* クロック分周1/5 (153.6KHz　=　9600bps) */
#endif

    /* CTC 1 */

    /* CTC 2 */
    CTC_2.REG.BYTE = CTC_CMD_PSR_1DIV16; //
    CTC_2.REG.BYTE = 0x04; // 9.8304MHz


    /* CTC 3 */

}