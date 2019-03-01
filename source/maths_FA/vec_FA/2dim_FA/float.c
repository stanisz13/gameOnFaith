#include "float.h"

FVec2 scaleFVec2(FVec2 v, float s)
{
    FVec2 res = v;
    
    res.x *= s;
    res.y *= s;
    
    return res;
}

FVec2 addFVec2(FVec2 v, FVec2 w)
{
    FVec2 res = v;
    res.x += w.x;
    res.y += w.y;
    
    return res;
}

FVec2 subFVec2(FVec2 v, FVec2 w)
{
    FVec2 res = v;
    res.x -= w.x;
    res.y -= w.y;
    
    return res;
}

FVec2 hadamardFVec2(FVec2 v, FVec2 w)
{
    FVec2 res = v;
    res.x *= w.x;
    res.y *= w.y;
    
    return res;
}

float dotProductFVec2(FVec2 v, FVec2 w)
{
    float res = 0;
    
    res += v.x * w.x;
    res += v.y * w.y;
    
    return res;
}

float lengthSquaredFVec2(FVec2 v)
{
    float res = v.x * v.x
        + v.y * v.y; 
    
    return res;
}

float lengthFVec2(FVec2 v)
{
    float res = sqrt((float)lengthSquaredFVec2(v));
    
    return res;
}

FVec2 normalizeFVec2(FVec2 v)
{
    FVec2 res;
    
    res = scaleFVec2(v, 1.0f / lengthFVec2(v));
    
    return res;
}

FVec2 initFVec2(float a, float b)
{
    FVec2 res;
    
    res.x = a;
    res.y = b;
    
    return res;
}
