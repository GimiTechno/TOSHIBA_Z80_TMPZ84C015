#ifndef _LIB_H_
#define _LIB_H_

#include <stdio.h>

// APP Inc
#include "common.h"

// memset()
void* lib_memset(void *a_buf, uint8 val,size_t size);
#define MEMSET  lib_memset

// strlen()
uint16 lib_strlen( uint8 *p_buf );
#define STRLEN  lib_strlen

#endif /* _LIB_H_ */