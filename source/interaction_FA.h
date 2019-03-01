#ifndef INTERACTION_FA_H
#define INTERACTION_FA_H

#include "maths_FA/vec_FA/2dim_FA/float.h"

typedef struct
{
    unsigned left;
    unsigned right;
    unsigned middle;
    int wheel; //NOTE(Stanisz13): sign depending on scroll direction
    
    //NOTE(Stanisz13): From Xlib - left top corner is (0, 0), bottom right corner is (screenW, screenH);
    FVec2 pos;
    
    float sensitivity;
} MouseState;


#endif