/*
 *  WOLFCLONE
 *  MODULE: System
 *
 *  sys.h
 *      Contains useful system related functions-
 *      such as debug, logging and input
 *
 *  Created on 14-02-2017.
 *  Copyright C Klas Henriksson 2017. All rights reserved
 */


#ifndef sys_h
#define sys_h

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __APPLE__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdocumentation"
#endif
#include <GLFW/glfw3.h>
#ifdef __APPLE__
    #pragma clang pop
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
    
#define WIDTH 480
#define HEIGHT 480

#define ENGINE_NAME "BIG BAD WOLF ENGINE"
#define ENGINE_VERSION 0.1
    
//set this to false if SYS_dprintf should not print out [DEBUG] before message
#define SYS_PRINT_DEBUG_MARK 0
//set this to true if SYS_dlogf should include a timestamp
#define SYS_LOG_INCLUDE_TIMESTAMP 0
//set this to true if system should clamp mouse coordinates to window coordinates
#define SYS_CLAMP_MOUSE_COORDS 1

typedef struct mouse_info
{
    int x,y;
    bool buttons[8];
} mouse_info_t;
    
void SYS_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void SYS_MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void SYS_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

bool SYS_keydown(unsigned int i);
bool SYS_keyup(unsigned int i);

mouse_info_t SYS_mouse();

void SYS_dprintf(const char* format, ...);
int SYS_dlogf(const char* format, ...);

#ifdef __cplusplus
}
#endif
#endif /* sys_h */
