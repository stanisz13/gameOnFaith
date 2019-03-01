#include "float.h"

FMat2 addFMat2(FMat2 a, FMat2 b)
{
    FMat2 res = a;
    
    for (unsigned i = 0; i < 2; ++i)
    {
        for (unsigned j = 0; j < 2; ++j)
        {
            float* resAcc = accessFMat2(&res, i, j);
            float* bAcc = accessFMat2(&b, i, j);
            
            *resAcc += *bAcc;
        }
    }
    
    return res;
}

FMat2 scaleFMat2(FMat2 a, float b)
{
    FMat2 res = a;
    
    for (unsigned i = 0; i < 2; ++i)
    {
        for (unsigned j = 0; j < 2; ++j)
        {
            float* resAcc = accessFMat2(&res, i, j);
            
            *resAcc *= b;
        }
    }
    
    return res;    
}

FMat2 identityFMat2()
{
    FMat2 res = {};
    
    for (unsigned i = 0; i < 2; ++i)
    {
        float* resAcc = accessFMat2(&res, i, i);
        *resAcc = 1.0f;
    }
    
    return res;
}

float* accessFMat2(FMat2* m, unsigned x, unsigned y)
{
    float* res = 0;
    
    res = m->mem + x * 2 + y;
    
    return res;
}

FMat2 setFMat2ByElements(const float* data)
{
    FMat2 res;
    
    memcpy(res.mem, data, sizeof(res.mem));
    
    return res;
}

FMat2 setFMat2ByVectors(FVec2 a, FVec2 b)
{
    FMat2 res;
    
    res.col1 = a;
    res.col2 = b;
    
    return res;
}

FMat2 mulFMat2(FMat2 a, FMat2 b)
{
    FMat2 res = {};
    
    for (unsigned i = 0; i < 2; ++i)
    {
        for (unsigned j = 0; j < 2; ++j)
        {
            float* curResElem = accessFMat2(&res, i, j);
            for (unsigned k = 0; k < 2; ++k)
            {
                float* curAElem = accessFMat2(&a, k, j);
                float* curBElem = accessFMat2(&b, i, k);
                *curResElem += *curAElem * *curBElem;
            }
        }
    }
    return res;
}

float detFMat2(FMat2 a)
{
    float res = a.mem[0] * a.mem[3] - a.mem[1] * a.mem[2];
    
    return res;
}

FMat2 inverseFMat2(FMat2 a, float det)
{
    FMat2 res;
    
    float oneOverDet = 1.0f / det;
    
    res.mem[0] = a.mem[3];
    res.mem[1] = -a.mem[1];
    res.mem[2] = -a.mem[2];
    res.mem[3] = a.mem[0];
    
    res = scaleFMat2(res, oneOverDet);
    
    return res;
}

FMat2 transposeFMat2(FMat2 a)
{
    FMat2 res = a;
    
    res.col1.y = a.col2.x;
    res.col2.x = a.col1.y;
    
    return res;
}

FVec2 mulFMat2ByFVec2(FMat2 a, FVec2 b)
{
    FVec2 res = {};
    
    for (unsigned i = 0; i < 2; ++i)
    {
        float* resAcc = &res.mem[i];
        
        for (unsigned k = 0; k < 2 ; ++k)
        {
            float* matAcc = accessFMat2(&a, k, i);
            
            *resAcc += b.mem[k] * *matAcc;
        }
    }
    
    return res;
}
