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
#include "matrix4x4.h"
#include "vec3.h"
#include "ray.h"
#include "sys.h"

#define mapWidth 6
#define mapHeight 6

unsigned char frameBuffer[WIDTH * HEIGHT * 3] = {1};

vec3f pos;
vec3f dir;

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
    for(int x = 0; x < WIDTH; x++)
        SetPixel(x, 0, vec3f(255,255,255));
}

void Renderer::render()
{
    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, frameBuffer);
}
