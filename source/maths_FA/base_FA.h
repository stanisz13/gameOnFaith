#ifndef MATHS_FA__H
#define MATHS_FA__H

#include <limits.h>
#include <float.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "../log_FA.h"

#define EPSILON 0.0000001f
#define EPSILON_DOUBLE 0.0000000000001f
#define PI 3.14159265358979f

typedef struct
{
    union
    {
        struct
        {
            FVec3 col1, col2, col3;
        };
        float mem[9];
    };
} FMat3;

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

typedef struct
{
    FVec3 pos;
    FVec3 target;
    
    float zoomRangeMin;
    float zoomRangeMax;
    
} Camera;

//NOTE(Stanisz13): FUNCTIONS

//NOTE(Stanisz13): NUMERIC
float absFloat(float v);
int absInt(int v);
double absDouble(double v);

float minFloat(float v, float w);
float maxFloat(float v, float w);
double minDouble(double v, double w);
double maxDouble(double v, double w);
int maxInt(int v, int w);
int minInt(int v, int w);
unsigned minUnsigned(unsigned v, unsigned w);
unsigned maxUnsigned(unsigned v, unsigned w);

float degreesToRadians(float deg);
float radiansToDegrees(float rad);



//NOTE(Stanisz13): MATRICES

float* accessFMat3(FMat3* m, unsigned x, unsigned y);
float* accessFMat4(FMat4* m, unsigned x, unsigned y);

FMat3 setFMat3ByElements(const float* data);
FMat4 setFMat4ByElements(const float* data);

FMat3 setFMat3ByVectors(FVec3 a, FVec3 b, FVec3 c);
FMat4 setFMat4ByVectors(FVec4 a, FVec4 b, FVec4 c, FVec4 d);

FMat3 identityFMat3();
FMat4 identityFMat4();

FMat3 addFMat3(FMat3 a, FMat3 b);
FMat4 addFMat4(FMat4 a, FMat4 b);

FMat3 scaleFMat3(FMat3 a, float b);
FMat4 scaleFMat4(FMat4 a, float b);

FMat3 mulFMat3(FMat3 a, FMat3 b);
FMat4 mulFMat4(FMat4 a, FMat4 b);

float detFMat3(FMat3 a);
float detFMat4(FMat4 a);

FMat3 inverseFMat3(FMat3 a, float det);
FMat4 inverseFMat4(FMat4 a, float det);

FMat3 transposeFMat3(FMat3 a);
FMat4 transposeFMat4(FMat4 a);

FVec3 mulFMat3ByFVec3(FMat3 a, FVec3 b);
FVec4 mulFMat4ByFVec4(FMat4 a, FVec4 b);

FMat4 perspectiveFMat4(float near, float far,
                       float aRatio, float FOVradians);

FMat4 rotationFMat4(float angleRadians, FVec3 rotationAxis);
FMat4 translationFMat4(FVec3 v);
FMat4 scalingFMat4(FVec3 v);

FMat4 lookAt(Camera* cam);

#endif
