#ifndef FMAT2_FA_H
#define FMAT2_FA_H

#include "../../base_FA.h"
#include "../../vec_FA/2dim_FA/float.h"

typedef struct
{
    union
    {
        struct
        {
            FVec2 col1, col2;
        };
        float mem[4];
    };
    
} FMat2;

float* accessFMat2(FMat2* m, unsigned x, unsigned y);

FMat2 setFMat2ByElements(const float* data);

FMat2 setFMat2ByVectors(FVec2 a, FVec2 b);

FMat2 identityFMat2();

FMat2 addFMat2(FMat2 a, FMat2 b);

FMat2 scaleFMat2(FMat2 a, float b);

FMat2 mulFMat2(FMat2 a, FMat2 b);

float detFMat2(FMat2 a);

FMat2 inverseFMat2(FMat2 a, float det);

FMat2 transposeFMat2(FMat2 a);

FVec2 mulFMat2ByFVec2(FMat2 a, FVec2 b);

#endif