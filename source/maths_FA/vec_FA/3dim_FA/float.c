#include "float.h"

FVec3 scaleFVec3(FVec3 v, float s)
{
    FVec3 res = v;
    
    res.x *= s;
    res.y *= s;
    res.z *= s;
    
    return res;
}

FVec3 addFVec3(FVec3 v, FVec3 w)
{
    FVec3 res = v;
    res.x += w.x;
    res.y += w.y;
    res.z += w.z;
    
    return res;
}

FVec3 subFVec3(FVec3 v, FVec3 w)
{
    FVec3 res = v;
    res.x -= w.x;
    res.y -= w.y;
    res.z -= w.z;
    
    return res;
}

FVec3 hadamardFVec3(FVec3 v, FVec3 w)
{
    FVec3 res = v;
    res.x *= w.x;
    res.y *= w.y;
    res.z *= w.z;
    
    return res;
}

float dotProductFVec3(FVec3 v, FVec3 w)
{
    float res = 0;
    
    res += v.x * w.x;
    res += v.y * w.y;
    res += v.z * w.z;
    
    return res;
}

FVec3 crossProductFVec3(FVec3 a, FVec3 b)
{
    FVec3 res;
    
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.x * b.z - a.z * b.x;
    res.z = a.x * b.y - a.y * b.x;
    
    return res;
}

float lengthSquaredFVec3(FVec3 v)
{
    float res = v.x * v.x
        + v.y * v.y
        + v.z * v.z;
    
    return res;
}

float lengthFVec3(FVec3 v)
{
    float res = sqrt((float)lengthSquaredFVec3(v));
    
    return res;
}    

FVec3 normalizeFVec3(FVec3 v)
{
    FVec3 res;
    
    res = scaleFVec3(v, 1.0f / lengthFVec3(v));
    
    return res;
}

FVec3 initFVec3(float a, float b, float c)
{
    FVec3 res;
    
    res.x = a;
    res.y = b;
    res.z = c;
    
    return res;
}
