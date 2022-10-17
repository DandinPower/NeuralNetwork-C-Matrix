#include "../include/libs.h"
#include "../include/matrix.h"
#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <time.h>

//計算兩個vector的均方差
double MeanSquareError(int x, double* vector1, double* vector2){
    double result = 0;
    for (int i=0; i<x; i++) result += pow((vector1[i] - vector2[i]),2);
    return result / x;
}