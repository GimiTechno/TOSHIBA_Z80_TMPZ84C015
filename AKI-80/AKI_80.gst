; MODULE_NAME = STARTUP
_ERRNO REAL 8000:0 2
; MODULE_NAME = Z84c015
_DI REAL 391:2 6
_EI REAL 391:0 6
_NOP REAL 391:4 6
; MODULE_NAME = app_lib
_LIB_MEMSET REAL 2b6:0 b2
_LIB_STRLEN REAL 2b6:55 b2
; MODULE_NAME = ctc_drv
_DRV_CTC_INIT REAL 4cd:0 c
; MODULE_NAME = isr
_ISR_EXT_INT REAL 368:11 29
_ISR_NMI REAL 368:0 29
; MODULE_NAME = main
_MAIN REAL 33:25b 283
; MODULE_NAME = pio_drv
_DRV_PIO_INIT REAL 4d9:0 9
; MODULE_NAME = sio_drv
_DRV_SIO_INIT REAL 397:0 11b
_DRV_SIO_RX REAL 397:be 11b
_DRV_SIO_TX REAL 397:3c 11b
; MODULE_NAME = wdt_drv
_DRV_WDT_CLEAR REAL 4b2:1 1b
_DRV_WDT_INIT REAL 4b2:0 1b
_DRV_WDT_START REAL 4b2:7 1b
_DRV_WDT_STOP REAL 4b2:d 1b
