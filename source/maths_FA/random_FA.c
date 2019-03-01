#include "random_FA.h"

unsigned xorshift(RandomSeries* rs)
{
    unsigned x = rs->seed;
    
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    
    rs->seed = x;
    
    return x;
}

void setRandomSeed(RandomSeries* rs, unsigned s)
{
    rs->seed = s;
}

void setRandomSeedTime(RandomSeries* rs)
{
    rs->seed = (unsigned)time(0);
}

float getRandomFloatZeroOne(RandomSeries* rs)
{
    float res;
    
    unsigned r = xorshift(rs);
    
    res = (float)r / UINT_MAX;
    
    return res;    
}

double getRandomDoubleZeroOne(RandomSeries* rs)
{
    double res;
    
    unsigned r = xorshift(rs);
    
    res = (double)r / UINT_MAX;
    
    return res;
}

unsigned getRandomUnsignedOnInterval(RandomSeries* rs, unsigned a, unsigned b)
{
    unsigned res = xorshift(rs);
    
    res = res % (b - a + 1);
    res += a;
    
    return res;
}

float getRandomFloatOnInterval(RandomSeries* rs, float a, float b)
{
    float res = getRandomFloatZeroOne(rs);
    
    res *= absFloat(b - a);
    res += minFloat(a, b);
    
    return res;
}

double getRandomDoubleOnInterval(RandomSeries* rs, double a, double b)
{
    double res = getRandomDoubleZeroOne(rs);
    
    res *= absDouble(b - a);
    res += minDouble(a, b);
    
    return res;
}

int getRandomIntOnInterval(RandomSeries* rs, int a, int b)
{
    int res = xorshift(rs);
    res = absInt(res);
    
    res = res % absInt(b - a + 1);
    res += minInt(a, b);
    
    return res;
}

FVec2 getRandomFVec2OnInterval(RandomSeries* rs, float a, float b)
{
    FVec2 res;
    
    res.x = getRandomFloatOnInterval(rs, a, b);
    res.y = getRandomFloatOnInterval(rs, a, b);
    
    return res;
}

FVec3 getRandomFVec3OnInterval(RandomSeries* rs, float a, float b)
{
    FVec3 res;
    
    res.x = getRandomFloatOnInterval(rs, a, b);
    res.y = getRandomFloatOnInterval(rs, a, b);
    res.z = getRandomFloatOnInterval(rs, a, b);
    
    return res;
}

FVec4 getRandomFVec4OnInterval(RandomSeries* rs, float a, float b)
{
    FVec4 res;
    
    res.x = getRandomFloatOnInterval(rs, a, b);
    res.y = getRandomFloatOnInterval(rs, a, b);
    res.z = getRandomFloatOnInterval(rs, a, b);
    res.w = getRandomFloatOnInterval(rs, a, b);
    
    return res;
}

#if 0
DVec2 getRandomDVec2OnInterval(RandomSeries* rs, double a, double b)
{
    DVec2 res;
    
    res.x = getRandomDoubleOnInterval(rs, a, b);
    res.y = getRandomDoubleOnInterval(rs, a, b);
    
    return res;
}

UVec2 getRandomUVec2OnInterval(RandomSeries* rs, unsigned a, unsigned b)
{
    UVec2 res;
    
    res.x = getRandomUnsignedOnInterval(rs, a, b);
    res.y = getRandomUnsignedOnInterval(rs, a, b);
    
    return res;
}

IVec2 getRandomIVec2OnInterval(RandomSeries* rs, int a, int b)
{
    IVec2 res;
    
    res.x = getRandomIntOnInterval(rs, a, b);
    res.y = getRandomIntOnInterval(rs, a, b);
    
    return res;
}

DVec3 getRandomDVec3OnInterval(RandomSeries* rs, double a, double b)
{
    DVec3 res;
    
    res.x = getRandomDoubleOnInterval(rs, a, b);
    res.y = getRandomDoubleOnInterval(rs, a, b);
    res.z = getRandomDoubleOnInterval(rs, a, b);
    
    return res;
}

UVec3 getRandomUVec3OnInterval(RandomSeries* rs, unsigned a, unsigned b)
{
    UVec3 res;
    
    res.x = getRandomUnsignedOnInterval(rs, a, b);
    res.y = getRandomUnsignedOnInterval(rs, a, b);
    res.z = getRandomUnsignedOnInterval(rs, a, b);
    
    return res;
}

IVec3 getRandomIVec3OnInterval(RandomSeries* rs, int a, int b)
{
    IVec3 res;
    
    res.x = getRandomIntOnInterval(rs, a, b);
    res.y = getRandomIntOnInterval(rs, a, b);
    res.z = getRandomIntOnInterval(rs, a, b);
    
    return res;
}

DVec4 getRandomDVec4OnInterval(RandomSeries* rs, double a, double b)
{
    DVec4 res;
    
    res.x = getRandomDoubleOnInterval(rs, a, b);
    res.y = getRandomDoubleOnInterval(rs, a, b);
    res.z = getRandomDoubleOnInterval(rs, a, b);
    res.w = getRandomDoubleOnInterval(rs, a, b);
    
    return res;
}

UVec4 getRandomUVec4OnInterval(RandomSeries* rs, unsigned a, unsigned b)
{
    UVec4 res;
    
    res.x = getRandomUnsignedOnInterval(rs, a, b);
    res.y = getRandomUnsignedOnInterval(rs, a, b);
    res.z = getRandomUnsignedOnInterval(rs, a, b);
    res.w = getRandomUnsignedOnInterval(rs, a, b);
    
    return res;
}

IVec4 getRandomIVec4OnInterval(RandomSeries* rs, int a, int b)
{
    IVec4 res;
    
    res.x = getRandomIntOnInterval(rs, a, b);
    res.y = getRandomIntOnInterval(rs, a, b);
    res.z = getRandomIntOnInterval(rs, a, b);
    res.w = getRandomIntOnInterval(rs, a, b);
    
    return res;
}
#endif