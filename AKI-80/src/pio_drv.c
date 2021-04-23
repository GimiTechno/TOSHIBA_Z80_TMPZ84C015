#include "pio.h"

/**
 * @brief PIO 初期化
 * 
 */
void drv_pio_init( void )
{
    /* -------------------------------------------------------------------------------- */
    /* Port A */
    /* -------------------------------------------------------------------------------- */
    // 1) Interrupt Vector

    // 2) Mode Control
    PIO_A_CMD.REG.BYTE = PIO_CMD_PORT_MODE_3_BIT_IOMODE; /* Mode3 ... Bit I/O Mode */

    // 3) Data I/O Control

    // 4) Interrupt Control

    // 5) Mask Control


    /* -------------------------------------------------------------------------------- */
    /* Port B */
    /* -------------------------------------------------------------------------------- */
    // 1) Interrupt Vector

    // 2) Mode Control
    PIO_B_CMD.REG.BYTE = PIO_CMD_PORT_MODE_3_BIT_IOMODE; /* Mode3 ... Bit I/O Mode */

    // 3) Data I/O Control

    // 4) Interrupt Control

    // 5) Mask Control

    /* -------------------------------------------------------------------------------- */
}