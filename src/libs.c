#include "../include/libs.h"
#include "../include/matrix.h"
#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <time.h>

//隨機產生-1~1的weight
double GenerateRandomValue(int x, int y, int max, int min) { 
    return ((double)rand()*(max-min) / RAND_MAX + min)/sqrt(x*y);
}

//取得一個打亂過後的order vector
int* GetShuffleOrder(int sliceNums){
    int* newOrder = (int *)malloc(sliceNums * sizeof(int));
    for (int i=0; i<sliceNums; i++) newOrder[i] = i;
    for (int i = 0; i < sliceNums; i++) {
        int j = rand() % sliceNums;
        int t = newOrder[i];
        newOrder[i] = newOrder[j];
        newOrder[j] = t;
    }
    return newOrder;
}

//計算axis維度的最大值 && 目前僅實作axis = 1
double* Argmax(int x, int y, double** matrix, int axis){
    double* result;
    if (axis == 0){
        printf("ERROR:axis == 0\n");
        result = NULL;
    }
    else if (axis == 1){
        result = AllocateNewVector(x);
        for (int i=0; i<x; i++){
            double tempMax = matrix[i][0];
            double tempIndex = 0;
            for (int j=0; j<y; j++){
                if (matrix[i][j] >= tempMax){
                    tempIndex = j;
                    tempMax = matrix[i][j];
                }
            }
            result[i] = tempIndex;
        }
    }
    else {
        printf("ERROR:axis != 1\n");
        result = NULL;
    }
    return result;
}

//比較double的值 1為相等0為不相等
int CompareDouble(double x, double y){
    return fabs(x - y) <= 1e-20;
}