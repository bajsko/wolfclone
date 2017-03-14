/*
 *  WOLFCLONE
 *  MODULE: System
 *
 *  sys.h
 *      Contains useful system related functions-
 *      such as debug printing, logging etc..
 *
 *  Created on 14-02-2017.
 *  Copyright C Klas Henriksson 2017. All rights reserved
 */


#ifndef sys_h
#define sys_h

#include <stdio.h>
#include <stdlib.h>

//set this to false if SYS_dprintf should not print out [D] before message
#define SYS_PRINT_DEBUG_MARK 1
//set this to true if SYS_dlogf should include a timestamp
#define SYS_LOG_INCLUDE_TIMESTAMP 0

void SYS_dprintf(const char* format, ...);
int SYS_dlogf(const char* format, ...);

#endif /* sys_h */
