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

#define mapWidth 24
#define mapHeight 24

unsigned char frameBuffer[WIDTH * HEIGHT * 3] = {1};

int worldMap[mapWidth][mapHeight] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
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

}

void Renderer::setup()
{
    pos = vec2f(1,8);
    dir = vec2f(1,0).normalize();
    plane = vec2f(0,1.0f);
	rot = 0 * DEG_TO_RAD; //equal to (1,0)
    //tan(fov/2) = planey/dir
}

void Renderer::DrawVertical(int column, int upperBound, int lowerBound, vec3f color)
{
    if(column < 0 || column >= WIDTH) return;
    if(upperBound < lowerBound || upperBound >= HEIGHT) upperBound = HEIGHT-1;
    if(lowerBound > upperBound || lowerBound < 0) lowerBound = 0;
    
    for(int y = upperBound; y > lowerBound; y--)
    {
        SetPixel(column, y, color);
    }
}

void Renderer::ComputeScreen()
{
    
    memset(frameBuffer, 0, sizeof(frameBuffer));
    
    //Projection plane, originally 2x2 units;
    //size of one cube, 1x1(x1)

    clamp<float>(pos.x, 0, mapWidth);
    clamp<float>(pos.y, 0, mapHeight);
    
	//projection plane size: 2x2 units
	float lengthToProjPlane = 1 / tan(fov / 2); //ppsize/2/tan(fov/2) (right triangle)

    Vec2Util::debug_print(dir.normalize());
	vec2f projectionPlanePos = pos + dir * lengthToProjPlane;
    
    for(int x = 0; x < WIDTH; x++)
    {
        float xx = 2 * (float)x/(float)WIDTH - 1;
		vec2f rayPlaneWorldPos = projectionPlanePos + (plane * xx);
        vec2f rayDir = rayPlaneWorldPos - pos;
        rayDir.normalize();
        
        int mapX = (int)pos.x;
        int mapY = (int)pos.y;
        
        int stepX = 0;
        int stepY = 0;
        
        float sideDistX = 0;
        float sideDistY = 0;
        
        int hit = 0;
        int side = 0;
        
        vec2f deltaDist = vec2f(sqrtf(1 + (rayDir.y * rayDir.y)/(rayDir.x * rayDir.x)), sqrtf(1 + (rayDir.x * rayDir.x)/(rayDir.y * rayDir.y)));
        
        if(rayDir.x < 0)
        {
            sideDistX = (pos.x - mapX) * deltaDist.x;
            stepX = -1;
        } else if(rayDir.x > 0)
        {
            sideDistX = ((mapX + 1.0) - pos.x) * deltaDist.x;
            stepX = 1;
        }
        if(rayDir.y < 0)
        {
            sideDistY = (pos.y - mapY) * deltaDist.y;
            stepY = -1;
        } else if(rayDir.y > 0)
        {
            sideDistY = ((mapY + 1.0) - pos.y) * deltaDist.y;
            stepY = 1;
        }
        
        while(hit == 0)
        {
            if(sideDistX < sideDistY)
            {
                sideDistX += deltaDist.x;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDist.y;
                mapY += stepY;
                side = 1;
            }
            
            if(worldMap[mapX][mapY] > 0)
                hit = worldMap[mapX][mapY];
        }
        

            //actual height / distance from proj plane * distance to proj plane
        float perpWallDist = 0;
        vec2f sideDist(sideDistX, sideDistY);
        
        float wallDist = (vec2f(mapX - pos.x, mapY - pos.y)).lengthSquared();
        
        perpWallDist = (1/wallDist) * lengthToProjPlane;
    
        int lineHeight = perpWallDist * HEIGHT;
        int upperBound = lineHeight/2 + HEIGHT/2;
        int lowerBound = -lineHeight / 2 + HEIGHT/2;
        
        float far = 25;
        float col01 = wallDist / far;
        
        vec3f color = vec3f(255-col01*255,255-col01*255,255-col01*255); //very bad red
        
        /*switch (hit) {
            case 1:
                color = vec3f(120,0,0);
                break;
                
            case 2:
                color = vec3f(0,0,120);
                break;
                
            default:
                break;
        }*/
        
        DrawVertical(x, upperBound, lowerBound, color);
        
        
    }
    
}

float lastX = 0;
float mouseX = 0;

void Renderer::render(float dt)
{
    
    dir.normalize();
    
    if(SYS_keydown(GLFW_KEY_W))
        pos += dir * 0.2f;
    else if(SYS_keydown(GLFW_KEY_S))
        pos -= dir * 0.2f;
    
    lastX = mouseX;
    mouseX = SYS_mouse().x;
    
    float rotSpeed = 1.5f * dt;
    if(SYS_keydown(GLFW_KEY_D))
    {
        rotVec(dir, rotSpeed);
        rotVec(plane, rotSpeed);
    } else if(SYS_keydown(GLFW_KEY_A))
    {
        rotVec(dir, -rotSpeed);
        rotVec(plane, -rotSpeed);
    }
    
    Vec2Util::debug_print(pos);
    
    ComputeScreen();
    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, frameBuffer);
}
