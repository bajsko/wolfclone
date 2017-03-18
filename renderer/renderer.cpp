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

inline void rotVec(vec2f& v, float rads)
{
	float x = v.x;
	float y = v.y;
	v.x = x * cos(rads) - y * sin(rads);
	v.y = y * cos(rads) + x * sin(rads);

	v.x = roundf(v.x);
	v.y = roundf(v.y);
}

void Renderer::setup()
{
    pos = vec2f(0,0);
    dir = vec2f(1,0).normalize();
	rot = 0; //equal to (1,0)
    //tan(fov/2) = planey/dir
}

void Renderer::ComputeScreen()
{
    //Projection plane, originally 2x2 units;
    //multiply x by aspect ratio
    //multiply y by tan(fov/2)
    float aspect = (float)WIDTH/(float)HEIGHT;
    float tanfov = (float)tan(fov/2);

	//projection plane size: 2x2 units
	float lengthToProjPlane = 1 / tan(fov / 2); //ppsize/2/tan(fov/2) (right triangle)
	vec2f plane(0, 1);

	rotVec(dir, rot);
	rotVec(plane, rot);

	vec2f projectionPlanePos = pos + dir * lengthToProjPlane;
    
    for(int x = 0; x < WIDTH; x++)
    {
        float xx = 2 * (float)x/(float)WIDTH -1;
		xx = 0;
		vec2f rayPlaneWorldPos = projectionPlanePos + plane * xx;
		vec2f rayDir = (rayPlaneWorldPos - pos).normalize();



    }
    
}

void Renderer::render()
{
    ComputeScreen();
    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, frameBuffer);
}
