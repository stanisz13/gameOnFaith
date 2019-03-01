#include "base_FA.h"

float absFloat(float v)
{
    if (v < 0.0f)
    {
        return -v;
    }
    
    return v;
}

int absInt(int v)
{
    if (v < 0)
    {
        return -v;
    }
    
    return v;
}

double absDouble(double v)
{
    if (v < 0.0f)
    {
        return -v;
    }
    
    return v;
}

float minFloat(float v, float w)
{
    if (v - w < EPSILON)
    {
        return v;
    }
    
    return w;
}

float maxFloat(float v, float w)
{
    if (v - w > EPSILON)
    {
        return v;
    }
    
    return w;
}

double minDouble(double v, double w)
{
    if (v - w < EPSILON_DOUBLE)
    {
        return v;
    }
    
    return w;
}

double maxDouble(double v, double w)
{
    if (v - w > EPSILON_DOUBLE)
    {
        return v;
    }
    
    return w;
}

double maxDouble(double v, double w);

int maxInt(int v, int w)
{
    if (v > w)
    {
        return v;
    }
    
    return w;
}

int minInt(int v, int w)
{
    if (v < w)
    {
        return v;
    }
    
    return w;
}

unsigned minUnsigned(unsigned v, unsigned w)
{
    if (v < w)
    {
        return v;
    }
    
    return w;
}

unsigned maxUnsigned(unsigned v, unsigned w)
{
    if (v > w)
    {
        return v;
    }
    
    return w;
}

float degreesToRadians(float deg)
{
    return ((deg * PI) / 180.0f);
}

float radiansToDegrees(float rad)
{
    return((rad * 180.0f) / PI);
}

