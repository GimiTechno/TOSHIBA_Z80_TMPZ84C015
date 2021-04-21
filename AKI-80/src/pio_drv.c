#include "pio.h"

/**
 * @brief PIO 初期化
 * 
 */
void drv_pio_init( void )
{
    // Port A
    REG_PIO_A_CMD = PIO_CMD_PORT_INPUT_MODE;   /* Port A = Input */
    // Port B
    REG_PIO_B_CMD = PIO_CMD_PORT_OUTPUT_MODE;   /* Port B = Output */
}