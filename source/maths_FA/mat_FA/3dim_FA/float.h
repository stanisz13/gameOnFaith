#ifndef FMAT3_FA_H
#define FMAT3_FA_H

#include "../../base_FA.h"
#include "../../vec_FA/3dim_FA/float.h"

typedef struct
{
    union
    {
        struct
        {
            FVec3 col1, col2, col3;
        };
        float mem[9];
    };
} FMat3;

float* accessFMat3(FMat3* m, unsigned x, unsigned y);

FMat3 setFMat3ByElements(const float* data);

FMat3 setFMat3ByVectors(FVec3 a, FVec3 b, FVec3 c);

FMat3 identityFMat3();

FMat3 addFMat3(FMat3 a, FMat3 b);

FMat3 scaleFMat3(FMat3 a, float b);

FMat3 mulFMat3(FMat3 a, FMat3 b);

float detFMat3(FMat3 a);

FMat3 inverseFMat3(FMat3 a, float det);

FMat3 transposeFMat3(FMat3 a);

FVec3 mulFMat3ByFVec3(FMat3 a, FVec3 b);

#endif