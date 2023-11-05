#ifndef PIXELWORK_QUAT_H
#define PIXELWORK_QUAT_H

#define SIZE_MATRIX 3


#include "functions/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <assert.h>
#include <time.h>

typedef struct Quaternion{
    long double q0;
    long double q1;  //Imaginary i
    long double q2;  //Imaginary j
    long double q3;  //Imaginary k
}Quaternion;

struct Vector{
    long double x;
    long double y;
    long double z;
};

//clock_t begin = clock();
/* here, do your time-consuming job */
//clock_t end = clock();
//double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

#endif //PIXELWORK_QUAT_H
