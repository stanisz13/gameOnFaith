#ifndef FVEC4_FA_H
#define FVEC4_FA_H

#include "../../base_FA.h"

typedef struct
{
    union
    {
        struct
        {
            float x, y, z, w;
        };
        float mem[4];
    };
} FVec4;

FVec4 scaleFVec4(FVec4 v, float s);

FVec4 addFVec4(FVec4 v, FVec4 w);

FVec4 subFVec4(FVec4 v, FVec4 w);

FVec4 hadamardFVec4(FVec4 v, FVec4 w);

float dotProductFVec4(FVec4 v, FVec4 w);

float lengthSquaredFVec4(FVec4 v);

float lengthFVec4(FVec4 v);

FVec4 normalizeFVec4(FVec4 v);

FVec4 initFVec4(float a, float b, float c, float d);

#endif