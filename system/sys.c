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

static unsigned int m_windowWidth;
static unsigned int m_windowHeight;

static bool m_keys[255];
static bool m_mouseButtons[8];
static int m_mouseX;
static int m_mouseY;

void SYS_SetWindowDimensions(unsigned int width, unsigned int height)
{
    m_windowWidth = width;
    m_windowHeight = height;
}

void SYS_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
        m_keys[key] = true;
    else if(action == GLFW_RELEASE)
        m_keys[key] = false;
}

void SYS_MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    m_mouseX = (int)xpos;
    m_mouseY = (int)ypos;
    
#if SYS_CLAMP_MOUSE_COORDS
    if(m_mouseX < 0)
        m_mouseX = 0;
    else if(m_mouseX > m_windowWidth)
        m_mouseX = m_windowWidth;
    
    if(m_mouseY < 0)
        m_mouseY = 0;
    else if(m_mouseY > m_windowHeight)
        m_mouseY = m_windowHeight;
#endif
}

void SYS_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
        m_mouseButtons[button] = true;
    else if(action == GLFW_RELEASE)
        m_mouseButtons[button] = false;
}

bool SYS_keydown(unsigned int i)
{
    if(i >= 255)
        return false;
    
    return m_keys[i];
}

bool SYS_keyup(unsigned int i)
{
    if(i >= 255)
        return false;
    
    return m_keys[i];
}

mouse_info_t SYS_mouse()
{
    mouse_info_t m;
    m.x = m_mouseX;
    m.y = m_mouseY;
    m.buttons[0] = m_mouseButtons[GLFW_MOUSE_BUTTON_LEFT];
    m.buttons[1] = m_mouseButtons[GLFW_MOUSE_BUTTON_RIGHT];
    return m;
}

void SYS_dprintf(const char* format, ...)
{
    va_list list;
    va_start(list, format);
    
#if SYS_PRINT_DEBUG_MARK
    printf("%s ", "[DEBUG]");
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
