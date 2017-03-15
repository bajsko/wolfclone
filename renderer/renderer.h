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

class Renderer
{
public:
    Renderer() {}
    ~Renderer() {}
    
    void setup();
    void render();
};

#endif /* renderer_h */
