#include "float.h"

FMat4 addFMat4(FMat4 a, FMat4 b)
{
    FMat4 res = a;
    
    for (unsigned i = 0; i < 4; ++i)
    {
        for (unsigned j = 0; j < 4; ++j)
        {
            float* resAcc = accessFMat4(&res, i, j);
            float* bAcc = accessFMat4(&b, i, j);
            
            *resAcc += *bAcc;
        }
    }
    
    return res;
}

FMat4 scaleFMat4(FMat4 a, float b)
{
    FMat4 res = a;
    
    for (unsigned i = 0; i < 4; ++i)
    {
        for (unsigned j = 0; j < 4; ++j)
        {
            float* resAcc = accessFMat4(&res, i, j);
            
            *resAcc *= b;
        }
    }
    
    return res;    
}

FMat4 identityFMat4()
{
    FMat4 res = {};
    
    for (unsigned i = 0; i < 4; ++i)
    {
        float* resAcc = accessFMat4(&res, i, i);
        *resAcc = 1.0f;
    }
    
    return res;
}

float* accessFMat4(FMat4* m, unsigned x, unsigned y)
{
    float* res= 0;
    
    res = m->mem + x * 4 + y;
    
    return res;
}

FMat4 setFMat4ByElements(const float* data)
{
    FMat4 res;
    
    memcpy(res.mem, data, sizeof(res.mem));
    
    return res;
}

FMat4 setFMat4ByVectors(FVec4 a, FVec4 b, FVec4 c, FVec4 d)
{
    FMat4 res;
    
    res.col1 = a;
    res.col2 = b;
    res.col3 = c;
    res.col4 = d;
    
    return res;
}

FMat4 mulFMat4(FMat4 a, FMat4 b)
{
    FMat4 res = {};
    
    for (unsigned i = 0; i < 4; ++i)
    {
        for (unsigned j = 0; j < 4; ++j)
        {
            float* curResElem = accessFMat4(&res, i, j);
            
            for (unsigned k = 0; k < 4; ++k)
            {
                float* curAElem = accessFMat4(&a, k, j);
                float* curBElem = accessFMat4(&b, i, k);
                
                *curResElem += *curAElem * *curBElem;
            }
        }
    }
    return res;
}

float detFMat4(FMat4 a)
{
    float res;
    
    float SubFactor00 = a.col3.mem[2] * a.col4.mem[3] - a.col4.mem[2] * a.col3.mem[3];
    float SubFactor01 = a.col3.mem[1] * a.col4.mem[3] - a.col4.mem[1] * a.col3.mem[3];
    float SubFactor02 = a.col3.mem[1] * a.col4.mem[2] - a.col4.mem[1] * a.col3.mem[2];
    float SubFactor03 = a.col3.mem[0] * a.col4.mem[3] - a.col4.mem[0] * a.col3.mem[3];
    float SubFactor04 = a.col3.mem[0] * a.col4.mem[2] - a.col4.mem[0] * a.col3.mem[2];
    float SubFactor05 = a.col3.mem[0] * a.col4.mem[1] - a.col4.mem[0] * a.col3.mem[1];
    
    FVec4 detCof = initFVec4(
        a.col2.mem[1] * SubFactor00 - a.col2.mem[2] * SubFactor01 + a.col2.mem[3] * SubFactor02,
        -(a.col2.mem[0] * SubFactor00 - a.col2.mem[2] * SubFactor03 + a.col2.mem[3] * SubFactor04),
        a.col2.mem[0] * SubFactor01 - a.col2.mem[1] * SubFactor03 + a.col2.mem[3] * SubFactor05,
        -(a.col2.mem[0] * SubFactor02 - a.col2.mem[1] * SubFactor04 + a.col2.mem[2] * SubFactor05)
        );
    
    res = (a.col1.mem[0] * detCof.x + a.col1.mem[1] * detCof.y +
           a.col1.mem[2] * detCof.z + a.col1.mem[3] * detCof.w);
    
    return res;
}

FMat4 inverseFMat4(FMat4 a, float det)
{
    FMat4 res;
    
    float oneOverDet = 1.0f / det;
    
    res.mem[0] = a.mem[9] * a.mem[14] * a.mem[7]
        - a.mem[13] * a.mem[10] * a.mem[7]
        + a.mem[13] * a.mem[6] * a.mem[11]
        - a.mem[5] * a.mem[14] * a.mem[11]
        - a.mem[9] * a.mem[6] * a.mem[15]
        + a.mem[5] * a.mem[10] * a.mem[15];
    
    res.mem[1] = a.mem[13] * a.mem[10] * a.mem[3]
        - a.mem[9] * a.mem[14] * a.mem[3]
        - a.mem[13] * a.mem[2] * a.mem[11]
        + a.mem[1] * a.mem[14] * a.mem[11]
        + a.mem[9] * a.mem[2] * a.mem[15]
        - a.mem[1] * a.mem[10] * a.mem[15];
    
    res.mem[2] = a.mem[5] * a.mem[14] * a.mem[3]
        - a.mem[13] * a.mem[6] * a.mem[3]
        + a.mem[13] * a.mem[2] * a.mem[7]
        - a.mem[1] * a.mem[14] * a.mem[7]
        - a.mem[5] * a.mem[2] * a.mem[15]
        + a.mem[1] * a.mem[6] * a.mem[15];
    
    res.mem[3] = a.mem[9] * a.mem[6] * a.mem[3]
        - a.mem[5] * a.mem[10] * a.mem[3]
        - a.mem[9] * a.mem[2] * a.mem[7]
        + a.mem[1] * a.mem[10] * a.mem[7]
        + a.mem[5] * a.mem[2] * a.mem[11]
        - a.mem[1] * a.mem[6] * a.mem[11];
    
    res.mem[4] = a.mem[12] * a.mem[10] * a.mem[7]
        - a.mem[8] * a.mem[14] * a.mem[7]
        - a.mem[12] * a.mem[6] * a.mem[11]
        + a.mem[4] * a.mem[14] * a.mem[11]
        + a.mem[8] * a.mem[6] * a.mem[15]
        - a.mem[4] * a.mem[10] * a.mem[15];
    
    res.mem[5] = a.mem[8] * a.mem[14] * a.mem[3]
        - a.mem[12] * a.mem[9] * a.mem[3]
        + a.mem[12] * a.mem[2] * a.mem[11]
        - a.mem[0] * a.mem[14] * a.mem[11]
        - a.mem[8] * a.mem[2] * a.mem[15]
        + a.mem[0] * a.mem[10] * a.mem[15];
    
    res.mem[6] = a.mem[12] * a.mem[6] * a.mem[3]
        - a.mem[4] * a.mem[14] * a.mem[3]
        - a.mem[12] * a.mem[2] * a.mem[7]
        + a.mem[0] * a.mem[14] * a.mem[7]
        + a.mem[4] * a.mem[2] * a.mem[15]
        - a.mem[0] * a.mem[6] * a.mem[15];
    
    res.mem[7] = a.mem[4] * a.mem[10] * a.mem[3]
        - a.mem[8] * a.mem[6] * a.mem[3]
        + a.mem[8] * a.mem[2] * a.mem[7]
        - a.mem[0] * a.mem[10] * a.mem[7]
        - a.mem[4] * a.mem[2] * a.mem[11]
        + a.mem[0] * a.mem[6] * a.mem[11];
    
    res.mem[8] = a.mem[8] * a.mem[13] * a.mem[7]
        - a.mem[12] * a.mem[9] * a.mem[7]
        + a.mem[12] * a.mem[5] * a.mem[11]
        - a.mem[4] * a.mem[13] * a.mem[11]
        - a.mem[8] * a.mem[5] * a.mem[15]
        + a.mem[4] * a.mem[9] * a.mem[15];
    
    res.mem[9] = a.mem[12] * a.mem[9] * a.mem[3]
        - a.mem[8] * a.mem[13] * a.mem[3]
        - a.mem[12] * a.mem[1] * a.mem[11]
        + a.mem[0] * a.mem[13] * a.mem[11]
        + a.mem[8] * a.mem[1] * a.mem[15]
        - a.mem[0] * a.mem[9] * a.mem[15];
    
    res.mem[10] = a.mem[4] * a.mem[13] * a.mem[3]
        - a.mem[12] * a.mem[5] * a.mem[3]
        + a.mem[12] * a.mem[1] * a.mem[7]
        - a.mem[0] * a.mem[13] * a.mem[7]
        - a.mem[4] * a.mem[1] * a.mem[15]
        + a.mem[0] * a.mem[5] * a.mem[15];
    
    res.mem[11] = a.mem[8] * a.mem[5] * a.mem[3]
        - a.mem[4] * a.mem[9] * a.mem[3]
        - a.mem[8] * a.mem[1] * a.mem[7]
        + a.mem[0] * a.mem[9] * a.mem[7]
        + a.mem[4] * a.mem[1] * a.mem[11]
        - a.mem[0] * a.mem[5] * a.mem[11];
    
    res.mem[12] = a.mem[12] * a.mem[9] * a.mem[6]
        - a.mem[8] * a.mem[13] * a.mem[6]
        - a.mem[12] * a.mem[5] * a.mem[10]
        + a.mem[4] * a.mem[13] * a.mem[10]
        + a.mem[8] * a.mem[5] * a.mem[14]
        - a.mem[4] * a.mem[9] * a.mem[14];
    
    res.mem[13] = a.mem[8] * a.mem[13] * a.mem[2]
        - a.mem[12] * a.mem[9] * a.mem[2]
        + a.mem[12] * a.mem[1] * a.mem[10]
        - a.mem[0] * a.mem[13] * a.mem[10]
        - a.mem[8] * a.mem[1] * a.mem[14]
        + a.mem[0] * a.mem[9] * a.mem[14];
    
    res.mem[14] = a.mem[12] * a.mem[5] * a.mem[2]
        - a.mem[4] * a.mem[13] * a.mem[2]
        - a.mem[12] * a.mem[1] * a.mem[6]
        + a.mem[0] * a.mem[13] * a.mem[6]
        + a.mem[4] * a.mem[1] * a.mem[14]
        - a.mem[0] * a.mem[5] * a.mem[14];
    
    res.mem[15] = a.mem[4] * a.mem[9] * a.mem[2]
        - a.mem[8] * a.mem[5] * a.mem[2]
        + a.mem[8] * a.mem[1] * a.mem[6]
        - a.mem[0] * a.mem[9] * a.mem[6]
        - a.mem[4] * a.mem[1] * a.mem[10]
        + a.mem[0] * a.mem[5] * a.mem[10];
    
    res = scaleFMat4(res, oneOverDet);
    
    return res;
}

FMat4 transposeFMat4(FMat4 a)
{
    FMat4 res = a;
    
    res.col1.y = a.col2.x;
    res.col1.z = a.col3.x;
    res.col1.w = a.col4.x;
    res.col2.x = a.col1.y;
    res.col2.z = a.col3.y;
    res.col2.w = a.col4.y;
    res.col3.x = a.col1.z;
    res.col3.y = a.col2.z;
    res.col3.w = a.col4.z;
    res.col4.x = a.col1.w;
    res.col4.y = a.col2.w;
    res.col4.z = a.col3.w;
    
    return res;
}

FVec4 mulFMat4ByFVec4(FMat4 a, FVec4 b)
{
    FVec4 res = {};
    
    for (unsigned i = 0; i < 4; ++i)
    {
        float* resAcc = &res.mem[i];
        
        for (unsigned k = 0; k < 4 ; ++k)
        {
            float* matAcc = accessFMat4(&a, k, i);
            
            *resAcc += b.mem[k] * *matAcc;
        }
    }
    
    return res;
}

FMat4 perspectiveFMat4(float near, float far,
                       float aRatio, float FOVradians)
{
    FMat4 res = {};
    
    float tanHalfFovY = tan(FOVradians / 2.0f);
    
#if 0
    mat<4, 4, T, defaultp> Result(static_cast<T>(0));
    Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
    Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
    Result[2][2] = - (zFar + zNear) / (zFar - zNear);
    Result[2][3] = - static_cast<T>(1);
    Result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
    
#endif
    
    res.col1.mem[0] = 1.0f / (aRatio * tanHalfFovY);
    res.col2.mem[1] = 1.0f / tanHalfFovY;
    
    res.col3.mem[2] = - (far + near) / (far - near);
    res.col3.mem[3] = -1.0f;
    res.col4.mem[2] = - (2.0f * far * near) / (far - near); 
    
    return res;
}

FMat4 rotationFMat4(float angleRadians, FVec3 rotationAxis)
{
    FMat4 res;
    
    float lSq = lengthSquaredFVec3(rotationAxis);
    float diff = lSq - 1.0f; 
    
    if (diff > EPSILON)
    {
        rotationAxis = normalizeFVec3(rotationAxis);
    }
    
    float s = sin(angleRadians);
    float c = cos(angleRadians);
    
    float oneMinusC = 1.0f - c;
    
    res.col1.x = c + rotationAxis.x * rotationAxis.x * oneMinusC;
    res.col1.y = rotationAxis.x * rotationAxis.y * oneMinusC + rotationAxis.z * s;
    res.col1.z = rotationAxis.z * rotationAxis.x * oneMinusC - rotationAxis.y * s;
    res.col1.w = 0.0f;
    
    res.col2.x = rotationAxis.x * rotationAxis.y * oneMinusC - rotationAxis.z * s;
    res.col2.y = c + rotationAxis.y * rotationAxis.y * oneMinusC;
    res.col2.z = rotationAxis.z * rotationAxis.y * oneMinusC + rotationAxis.x * s;
    res.col2.w = 0.0f;
    
    res.col3.x = rotationAxis.x * rotationAxis.z * oneMinusC + rotationAxis.y * s;
    res.col3.y = rotationAxis.y * rotationAxis.z * oneMinusC - rotationAxis.x * s;
    res.col3.z = c + rotationAxis.z * rotationAxis.z * oneMinusC;
    res.col3.w = 0.0f;
    
    res.col4.x = 0.0f;
    res.col4.y = 0.0f;
    res.col4.z = 0.0f;
    res.col4.w = 1.0f;
    
    return res;
}

FMat4 translationFMat4(FVec3 v)
{
    FMat4 res = identityFMat4();
    
    res.col4.x = v.x;
    res.col4.y = -v.y;
    res.col4.z = v.z;
    
    return res;
}

FMat4 scalingFMat4(FVec3 v)
{
    FMat4 res = {};
    
    res.col1.x = v.x;
    res.col2.y = v.y;
    res.col3.z = v.z;
    res.col4.w = 1.0f;
    
    return res;
}

FMat4 lookAt(FVec3 position, FVec3 target, FVec3 absoluteUp)
{
    FMat4 res;
    
    FVec3 dir = normalizeFVec3(subFVec3(target, position));
    FVec3 right = normalizeFVec3(crossProductFVec3(dir, absoluteUp));
    FVec3 up = crossProductFVec3(right, dir);
    
    //NOTE(Stanisz13): 3 WEEKS OF DEBUGGING JUST TO FIND THIS!??!!??!
    // I EVEN MODIFIED GLM CODE TO DEBUG WHAT IT DOES WHAAATTTTT
    up.y *= -1.0f;
    
    res.col1.x = right.x;
    res.col1.y = up.x;
    res.col1.z = -dir.x;
    res.col1.w = 0.0f;
    
    res.col2.x = right.y;
    res.col2.y = up.y;
    res.col2.z = -dir.y;
    res.col2.w = 0.0f;
    
    res.col3.x = right.z;
    res.col3.y = up.z;
    res.col3.z = -dir.z;
    res.col3.w = 0.0f;
    
    res.col4.x = -dotProductFVec3(right, position);
    res.col4.y = -dotProductFVec3(up, position);
    res.col4.z = dotProductFVec3(dir, position);
    res.col4.w = 1.0f;
    
    return res;
}
