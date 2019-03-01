#ifndef MATHS_FA__H
#define MATHS_FA__H

#include <limits.h>
#include <float.h>
#include <string.h>
#include <math.h>
#include "../log_FA.h"

#define EPSILON 0.0000001f
#define EPSILON_DOUBLE 0.0000000000001f
#define PI 3.14159265358979f


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





#endif
