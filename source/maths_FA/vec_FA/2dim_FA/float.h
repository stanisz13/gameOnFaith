#ifndef FVEC2_FA_H
#define FVEC2_FA_H

#include "../../base_FA.h"

typedef struct
{
    union
    {
        struct
        {
            float x, y;
        };
        float mem[2];
    };
} FVec2;

FVec2 scaleFVec2(FVec2 v, float s);

FVec2 addFVec2(FVec2 v, FVec2 w);

FVec2 subFVec2(FVec2 v, FVec2 w);

FVec2 hadamardFVec2(FVec2 v, FVec2 w);

float dotProductFVec2(FVec2 v, FVec2 w);

float lengthSquaredFVec2(FVec2 v);

float lengthFVec2(FVec2 v);

FVec2 normalizeFVec2(FVec2 v);

FVec2 initFVec2(float a, float b);

#endif