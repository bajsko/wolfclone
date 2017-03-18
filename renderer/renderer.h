/*
 *  WOLFCLONE
 *  MODULE: Renderer
 *
 *  renderer.h
 *      Responsible of rendering the game
 *
 *  Created on 15-02-2017.
 *  Copyright C Klas Henriksson 2017. All rights reserved
 */

#ifndef renderer_h
#define renderer_h

#include <stdio.h>
#include "matrix4x4.h"
#include "vec3.h"
#include "ray.h"

class Renderer
{
private:
    void ComputeScreen();
public:
    Renderer(float f) {this->fov = f;}
    ~Renderer() {}
    
    void setup();
    void render();
    
    float fov;
    vec3f dir;
    vec3f pos;
};

#endif /* renderer_h */
