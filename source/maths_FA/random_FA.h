#ifndef RANDOM_FA_H
#define RANDOM_FA_H

#include <time.h>

#include "base_FA.h"
#include "vec_FA/2dim_FA/float.h"
#include "vec_FA/3dim_FA/float.h"
#include "vec_FA/4dim_FA/float.h"

typedef struct
{
    unsigned seed;
    
} RandomSeries;

void setRandomSeed(RandomSeries* rs, unsigned s);
void setRandomSeedTime(RandomSeries* rs);

unsigned getRandomUnsignedOnInterval(RandomSeries* rs, unsigned a, unsigned b);
float getRandomFloatOnInterval(RandomSeries* rs, float a, float b);
double getRandomDoubleOnInterval(RandomSeries* rs, double a, double b);
int getRandomIntOnInterval(RandomSeries* rs, int a, int b);

FVec2 getRandomFVec2OnInterval(RandomSeries* rs, float a, float b);
FVec3 getRandomFVec3OnInterval(RandomSeries* rs, float a, float b);
FVec4 getRandomFVec4OnInterval(RandomSeries* rs, float a, float b);

#if 0
DVec2 getRandomDVec2OnInterval(RandomSeries* rs, double a, double b);
UVec2 getRandomUVec2OnInterval(RandomSeries* rs, unsigned a, unsigned b);
IVec2 getRandomIVec2OnInterval(RandomSeries* rs, int a, int b);
DVec3 getRandomDVec3OnInterval(RandomSeries* rs, double a, double b);
UVec3 getRandomUVec3OnInterval(RandomSeries* rs, unsigned a, unsigned b);
IVec3 getRandomIVec3OnInterval(RandomSeries* rs, int a, int b);
DVec4 getRandomDVec4OnInterval(RandomSeries* rs, double a, double b);
UVec4 getRandomUVec4OnInterval(RandomSeries* rs, unsigned a, unsigned b);
IVec4 getRandomIVec4OnInterval(RandomSeries* rs, int a, int b);
#endif


#endif