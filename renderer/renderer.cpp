/*
 *  WOLFCLONE
 *  MODULE: Renderer
 *
 *  renderer.cpp
 *
 *  Created on 15-02-2017.
 *  Copyright C Klas Henriksson 2017. All rights reserved
 */

#include "renderer.h"
#include "sys.h"

#define mapWidth 6
#define mapHeight 6

unsigned char frameBuffer[WIDTH * HEIGHT * 3] = {1};

int worldMap[mapWidth][mapHeight] =
{
    {1,1,1,1,1,1},
    {1,0,0,0,0,1},
    {1,0,0,0,0,1},
    {1,0,0,0,0,1},
    {1,0,0,0,0,1},
    {1,1,1,1,1,1},
};

void SetPixel(int x, int y, vec3f color)
{
    frameBuffer[3 * ((HEIGHT-1-y) * WIDTH + x) + 0] = (unsigned char)color.x;
    frameBuffer[3 * ((HEIGHT-1-y) * WIDTH + x) + 1] = (unsigned char)color.y;
    frameBuffer[3 * ((HEIGHT-1-y) * WIDTH + x) + 2] = (unsigned char)color.z;
}

vec3f GetPixel(int x, int y)
{
    unsigned char r = frameBuffer[3 * ((HEIGHT-1-y) * WIDTH + x) + 0];
    unsigned char g = frameBuffer[3 * ((HEIGHT-1-y) * WIDTH + x) + 1];
    unsigned char b = frameBuffer[3 * ((HEIGHT-1-y) * WIDTH + x) + 2];
    return vec3f(r,g,b);
}

void Renderer::setup()
{
    pos = vec3f(1,1,0);
    dir = vec3f(1,0,0);
    //tan(fov/2) = planey/dir
}

void Renderer::ComputeScreen()
{
    //Projection plane, originally 2x2 units;
    //multiply x by aspect ratio
    //multiply y by tan(fov/2)
    float aspect = (float)WIDTH/(float)HEIGHT;
    float tanfov = (float)tan(fov/2);
    
    for(int x = 0; x < WIDTH; x++)
    {
        float xx = 2 * (float)x/(float)WIDTH -1;
    }
    
}

void Renderer::render()
{
    ComputeScreen();
    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, frameBuffer);
}
