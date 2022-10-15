#include "../include/matrix.h"
#include "../include/libs.h"
#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <time.h>

//初始化vector的記憶體空間
double* AllocateNewVector(int x){
    return (double*)malloc(x * sizeof(double));
}

//釋放vector的記憶體空間
void FreeVector(double *vector){
    free(vector);
}

//將vector值設為0
void SetZeroVector(int x, double *vector){
    for (int i=0; i<x; i++) vector[i] = 0.0f;
}

//印出vector的值
void ShowVector(int x, double *vector){
    for(int i=0; i<x; i++) printf("%f,", vector[i]);
    printf("\n");
}