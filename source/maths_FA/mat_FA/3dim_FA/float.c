#include "float.h"

FMat3 addFMat3(FMat3 a, FMat3 b)
{
    FMat3 res = a;
    
    for (unsigned i = 0; i < 3; ++i)
    {
        for (unsigned j = 0; j < 3; ++j)
        {
            float* resAcc = accessFMat3(&res, i, j);
            float* bAcc = accessFMat3(&b, i, j);
            
            *resAcc += *bAcc;
        }
    }
    
    return res;
}

FMat3 scaleFMat3(FMat3 a, float b)
{
    FMat3 res = a;
    
    for (unsigned i = 0; i < 3; ++i)
    {
        for (unsigned j = 0; j < 3; ++j)
        {
            float* resAcc = accessFMat3(&res, i, j);
            
            *resAcc *= b;
        }
    }
    
    return res;    
}

FMat3 identityFMat3()
{
    FMat3 res = {};
    
    for (unsigned i = 0; i < 3; ++i)
    {
        float* resAcc = accessFMat3(&res, i, i);
        *resAcc = 1.0f;
    }
    
    return res;
}

float* accessFMat3(FMat3* m, unsigned x, unsigned y)
{
    float* res = 0;
    
    res = m->mem + x * 3 + y;
    
    return res;
}

FMat3 setFMat3ByElements(const float* data)
{
    FMat3 res;
    
    memcpy(res.mem, data, sizeof(res.mem));
    
    return res;
}

FMat3 setFMat3ByVectors(FVec3 a, FVec3 b, FVec3 c)
{
    FMat3 res;
    
    res.col1 = a;
    res.col2 = b;
    res.col3 = c;
    
    return res;
}

FMat3 mulFMat3(FMat3 a, FMat3 b)
{
    FMat3 res = {};
    
    for (unsigned i = 0; i < 3; ++i)
    {
        for (unsigned j = 0; j < 3; ++j)
        {
            float* curResElem = accessFMat3(&res, i, j);
            
            for (unsigned k = 0; k < 3; ++k)
            {
                float* curAElem = accessFMat3(&a, k, j);
                float* curBElem = accessFMat3(&b, i, k);
                
                *curResElem += *curAElem * *curBElem;
            }
        }
    }
    return res;
}

float detFMat3(FMat3 a)
{
    float res = a.mem[0] * a.mem[4] * a.mem[8]
        + a.mem[3] * a.mem[7] * a.mem[2]
        + a.mem[6] * a.mem[1] * a.mem[5]
        - a.mem[6] * a.mem[4] * a.mem[2]
        - a.mem[7] * a.mem[5] * a.mem[0]
        - a.mem[8] * a.mem[3] * a.mem[1];
    
    return res;
}

FMat3 inverseFMat3(FMat3 a, float det)
{
    FMat3 res;
    
    float oneOverDet = 1.0f / det;
    
    res.mem[0] = a.mem[4] * a.mem[8] - a.mem[5] * a.mem[7];
    res.mem[1] = a.mem[5] * a.mem[6] - a.mem[3] * a.mem[8];
    res.mem[2] = a.mem[3] * a.mem[7] - a.mem[4] * a.mem[6];
    res.mem[3] = a.mem[2] * a.mem[7] - a.mem[1] * a.mem[8];
    res.mem[4] = a.mem[0] * a.mem[8] - a.mem[2] * a.mem[6];
    res.mem[5] = a.mem[1] * a.mem[6] - a.mem[0] * a.mem[7];
    res.mem[6] = a.mem[1] * a.mem[5] - a.mem[2] * a.mem[4];
    res.mem[7] = a.mem[2] * a.mem[3] - a.mem[0] * a.mem[5];
    res.mem[8] = a.mem[0] * a.mem[4] - a.mem[1] * a.mem[3];
    
    res = scaleFMat3(res, oneOverDet);
    
    return res;
}

FMat3 transposeFMat3(FMat3 a)
{
    FMat3 res = a;
    
    res.col1.y = a.col2.x;
    res.col1.z = a.col3.x;
    res.col2.x = a.col1.y;
    res.col2.z = a.col3.y;
    res.col3.x = a.col1.z;
    res.col3.y = a.col2.z;
    
    return res;
}

FVec3 mulFMat3ByFVec3(FMat3 a, FVec3 b)
{
    FVec3 res = {};
    
    for (unsigned i = 0; i < 3; ++i)
    {
        float* resAcc = &res.mem[i];
        
        for (unsigned k = 0; k < 3 ; ++k)
        {
            float* matAcc = accessFMat3(&a, k, i);
            
            *resAcc += b.mem[k] * *matAcc;
        }
    }
    
    return res;    
}
