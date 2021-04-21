#include "lib.h"

/**
 * @brief 自前 memset()
 * 
 * @param p_buf 初期化するバッファ
 * @param val 初期化値
 * @param size 初期化サイズ
 * @return void* 
 */
void* lib_memset(void *p_buf, uint8 val,size_t size)
{
    uint8 *p_tmp;

    p_tmp = (uint8 *)p_buf;
    while (size--)
    {
        *p_tmp = val;
        p_tmp++;
    }

    return p_buf;
}

/**
 * @brief 自前 strlen()
 * 
 * @param p_buf lengthのバッファ
 * @return uint16 バッファのlength
 */
uint16 lib_strlen( uint8 *p_buf )
{
    uint16    len;
    uint8    *p_str;

    len = 0;
    p_str = p_buf;
    while( *p_str++ ) {
        len++;
        if( len < 0 ) return( -1 );    // 負数になったとは異常なので-1でリターン
    }

    return( len );
}
