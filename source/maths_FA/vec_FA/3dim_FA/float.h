#ifndef FVEC3_FA_H
#define FVEC3_FA_H

#include "../../base_FA.h"

typedef struct
{
    union
    {
        struct
        {
            float x, y, z;
        };
        float mem[3];
    };
} FVec3;

FVec3 scaleFVec3(FVec3 v, float s);

FVec3 addFVec3(FVec3 v, FVec3 w);

FVec3 subFVec3(FVec3 v, FVec3 w);

FVec3 hadamardFVec3(FVec3 v, FVec3 w);

float dotProductFVec3(FVec3 v, FVec3 w);

FVec3 crossProductFVec3(FVec3 a, FVec3 b);

float lengthSquaredFVec3(FVec3 v);

float lengthFVec3(FVec3 v);

FVec3 normalizeFVec3(FVec3 v);

FVec3 initFVec3(float a, float b, float c);

#endif