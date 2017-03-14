/*
 *  WOLFCLONE
 *  MODULE: System
 *
 *  sys.c
 *
 *  Created on 14-02-2017.
 *  Copyright C Klas Henriksson 2017. All rights reserved
 */

#include <stdarg.h>
#include <string.h>
#include "sys.h"

void SYS_dprintf(const char* format, ...)
{
    va_list list;
    va_start(list, format);
    
#if SYS_PRINT_DEBUG_MARK
    //todo
    vprintf(format, list);
#else
    vprintf(format, list);
#endif
    
    va_end(list);
}

int SYS_dlogf(const char* format, ...)
{
    //todo maybe do not open/close every function call..
    //todo add SYS_LOG_INCLUDE_TIMESTAMP support
    FILE* file = fopen("log.txt", "a");
    if(!file)
        return -1; //just fail
    
    va_list list;
    va_start(list, format);
    int r = vfprintf(file, format, list);
    va_end(list);
    
    fclose(file);
    
    if(r < 0)
        return -1;
    
    return 0;
}
