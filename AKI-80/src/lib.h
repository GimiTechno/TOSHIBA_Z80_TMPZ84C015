#ifndef _LIB_H_
#define _LIB_H_

#include <stdio.h>

// APP Inc
#include "common.h"

// memset()
void* lib_memset(void *a_buf, u1 val,size_t size);
#define MEMSET  lib_memset

// strlen()
u2 lib_strlen( u1 *p_buf );
#define STRLEN  lib_strlen

#endif /* _LIB_H_ */