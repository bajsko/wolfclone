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

#include "sys.h"
#include "renderer.h"

int main(int argc, const char** argv)
{

	SYS_dprintf("Intiating %s version %.2f\n", ENGINE_NAME, ENGINE_VERSION);

    GLFWwindow* m_window;
    
    if(!glfwInit())
        return -1;
    
    float time = glfwGetTime();
    
    m_window = glfwCreateWindow(WIDTH, HEIGHT, "WolfClone", NULL, NULL);
    if(!m_window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(m_window);
    
	SYS_dprintf("Regestrating callbacks...");

    glfwSetKeyCallback(m_window, SYS_KeyCallback);
    glfwSetCursorPosCallback(m_window, SYS_MousePositionCallback);
    glfwSetMouseButtonCallback(m_window, SYS_MouseButtonCallback);
    
	SYS_dprintf("Done\n");

	SYS_dprintf("Creating renderer...");
    Renderer m_renderer(66 * DEG_TO_RAD);
    m_renderer.setup();
	SYS_dprintf("Done\n");
    
    glfwSwapInterval(1);
    
	SYS_dprintf("Initiation done\n");

    while(!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float oldTime = time;
        time = glfwGetTime();
        float dt = (time - oldTime);
        //SYS_dprintf("FPS: %f\n", 1 / dt);
        
        glDisable(GL_DEPTH_TEST);
        m_renderer.render(dt);
        glEnable(GL_DEPTH_TEST);
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glfwDestroyWindow(m_window);
    
    return 0;
}
