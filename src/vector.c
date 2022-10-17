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
    for(int i=0; i<x; i++) printf("%E,", vector[i]);
    printf("\n");
}

//取得隨機長度為sliceNums的Vector
double* GetSliceVectorByOrder(int x, double *vector, int sliceNums, int *order){
    double *sliceVector = AllocateNewVector(sliceNums);
    for (int i=0; i<sliceNums; i++){
        int x = order[i];
        sliceVector[i] = vector[x];
    }
    return sliceVector;
}

//計算兩個矩陣的差異並取平均值
double CountVectorDifferenceMean(int x, double* vector1, double* vector2){
    double result = 0;
    for (int i=0; i<x; i++) result += CompareDouble(vector1[i], vector2[i]);
    return result / x;
}