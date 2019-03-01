#ifndef FMAT4_FA_H
#define FMAT4_FA_H

#include "../../base_FA.h"
#include "../../vec_FA/3dim_FA/float.h"
#include "../../vec_FA/4dim_FA/float.h"

typedef struct
{
    union
    {
        struct
        {
            FVec4 col1, col2, col3, col4;
        };
        float mem[16];
    };
} FMat4;

float* accessFMat4(FMat4* m, unsigned x, unsigned y);

FMat4 setFMat4ByElements(const float* data);

FMat4 setFMat4ByVectors(FVec4 a, FVec4 b, FVec4 c, FVec4 d);

FMat4 identityFMat4();

FMat4 addFMat4(FMat4 a, FMat4 b);

FMat4 scaleFMat4(FMat4 a, float b);

FMat4 mulFMat4(FMat4 a, FMat4 b);

float detFMat4(FMat4 a);

FMat4 inverseFMat4(FMat4 a, float det);

FMat4 transposeFMat4(FMat4 a);

FVec4 mulFMat4ByFVec4(FMat4 a, FVec4 b);

FMat4 perspectiveFMat4(float near, float far,
                       float aRatio, float FOVradians);

FMat4 rotationFMat4(float angleRadians, FVec3 rotationAxis);

FMat4 translationFMat4(FVec3 v);

FMat4 scalingFMat4(FVec3 v);

FMat4 lookAt(FVec3 position, FVec3 target, FVec3 absoluteUp);


#endif