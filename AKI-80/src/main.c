#include <stdio.h>
//#include <string.h>

// APP Inc
#include "common.h"
#include "lib.h"

/* �}�N�� */
#define DEBUG_Z80
#define TX_BUF_SIZE	8
#define RX_BUF_SIZE	8

/* �֐��錾 */
// XCC-V�R���p�C����p
#if (C_COMPILER == COMPILER_XCC_V)
global main();
#endif

extern void* lib_memset(void *a_buf, uint8 val,size_t size);
extern void NOP();
static void app_init(void);

/* �ϐ��錾 */
// const uint8 *g_msgbuf = "TMPZ84C015BF-8 KBC-Z05";
uint8 g_txbuf[TX_BUF_SIZE] = {0};
uint8 g_rxbuf[RX_BUF_SIZE] = {0};

static void app_init(void)
{
	MEMSET(&g_txbuf[0],0x00,sizeof(g_txbuf));
	MEMSET(&g_rxbuf[0],0x00,sizeof(g_rxbuf));
}

main()
{
    //uint32 cnt;

	// ����������
	app_init();

    // ���C�����[�v
    while (1)
    {
        NOP();
#ifdef DEBUG_Z80
        //cnt++;
#endif
    }

    return 0;
}