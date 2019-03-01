#include "float.h"

FVec4 scaleFVec4(FVec4 v, float s)
{
    FVec4 res = v;
    
    res.x *= s;
    res.y *= s;
    res.z *= s;
    res.w *= s;
    
    return res;
}

FVec4 addFVec4(FVec4 v, FVec4 w)
{
    FVec4 res = v;
    res.x += w.x;
    res.y += w.y;
    res.z += w.z;
    res.w += w.w;
    
    return res;
}

FVec4 subFVec4(FVec4 v, FVec4 w)
{
    FVec4 res = v;
    res.x -= w.x;
    res.y -= w.y;
    res.z -= w.z;
    res.w -= w.w;
    
    return res;
}

FVec4 hadamardFVec4(FVec4 v, FVec4 w)
{
    FVec4 res = v;
    res.x *= w.x;
    res.y *= w.y;
    res.z *= w.z;
    res.w *= w.w;
    
    return res;
}

float dotProductFVec4(FVec4 v, FVec4 w)
{
    float res = 0;
    
    res += v.x * w.x;
    res += v.y * w.y;
    res += v.z * w.z;
    res += v.w * w.w;
    
    return res;
}

float lengthSquaredFVec4(FVec4 v)
{
    float res = v.x * v.x
        + v.y * v.y
        + v.z * v.z
        + v.w * v.w;
    
    return res;
}

float lengthFVec4(FVec4 v)
{
    float res = sqrt((float)lengthSquaredFVec4(v));
    
    return res;
}

FVec4 normalizeFVec4(FVec4 v)
{
    FVec4 res;
    
    res = scaleFVec4(v, 1.0f / lengthFVec4(v));
    
    return res;
}

FVec4 initFVec4(float a, float b, float c, float d)
{
    FVec4 res;
    
    res.x = a;
    res.y = b;
    res.z = c;
    res.w = d;
    
    return res;
}
