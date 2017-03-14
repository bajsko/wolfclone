/*
 *  WOLFCLONE
 *  MODULE: System
 *
 *  main.cpp
 *      Main entrypoint for the application.
 *      Responsible of creating a OpenGL context and polling-
 *      window activity.
 *
 *  Created on 14-02-2017.
 *  Copyright C Klas Henriksson 2017. All rights reserved
 */

#include <stdio.h>

#ifdef __APPLE__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdocumentation"
#endif

#include <GLFW/glfw3.h>

#ifdef __APPLE__
    #pragma clang pop
#endif

#define WIDTH 640
#define HEIGHT 480

#include "sys.h"

int main(int argc, const char** argv)
{
    GLFWwindow* m_window;
    
    if(!glfwInit())
        return -1;
    
    m_window = glfwCreateWindow(WIDTH, HEIGHT, "WolfClone", NULL, NULL);
    if(!m_window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(m_window);
    
    while(!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(m_window);
    
    return 0;
}
