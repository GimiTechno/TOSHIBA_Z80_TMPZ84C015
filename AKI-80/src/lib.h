#ifndef _LIB_H_
#define _LIB_H_

#include <stdio.h>

// APP Inc
#include "common.h"

// memset()

// NOP (inline)
void NOP();
#pragma inline NOP

void* lib_memset(void *a_buf, uint8 val,size_t size);
#define MEMSET  lib_memset

#endif /* _LIB_H_ */