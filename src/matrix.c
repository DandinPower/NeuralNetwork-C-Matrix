#include "../include/matrix.h"
#include "../include/libs.h"
#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <time.h>

//初始化matrix的記憶體空間
double** AllocateNewMatrix(int x, int y){
    double **matrix;
    double *tmp;
    matrix = (double**)malloc(x * sizeof(double *));
    tmp = (double*)malloc( x * y * sizeof(double));
    for (int i=0; i<x; tmp += y) matrix[i++] = tmp;
    return matrix;
}

//釋放Matrix的記憶體空間
void FreeMatrix(double **matrix){
    free(matrix[0]);
    free(matrix);
}

//初始化參數
double** InitWeightMatrix(int x, int y){
    double **weights = AllocateNewMatrix(x, y);
    for(int i=0; i<x; i++) for (int j=0; j<y; j++) weights[i][j] = GenerateRandomValue(x,y,1,-1);
    return weights;
}

//將矩陣全部值設為0
void SetMatrixZero(int x, int y, double **matrix){
    for(int i=0; i<x; i++) for (int j=0; j<y; j++) matrix[i][j] = 0;
}

//印出Matrix的值
void ShowMatrix(int x, int y, double **weights){
    for(int i=0; i<x; i++) {
        for (int j=0; j<y; j++) printf("%E,", weights[i][j]);
        printf("\n");
    }
}

//取出matrix在0維[xIndex]內的最大值 && 如果xIndex == -1則取global最大值
double MaxMatrix(int x, int y, double **matrix, int xIndex){
    double max = 0;
    if (xIndex == -1){
        max = matrix[0][0];
        for (int i=0; i<x; i++) for (int j=0; j<y; j++) if (matrix[i][j] >= max) max = matrix[i][j];
    }
    else{
        max = matrix[xIndex][0];
        for (int i=1; i<y; i++) if (matrix[xIndex][i] >= max) max = matrix[xIndex][i];
    }
    return max;
}

//計算選定的軸的sum && 目前僅有實作axis == 0跟axis == 1
double* SumMatrix(int x, int y, double **matrix, int axis){
    double* sumResult = AllocateNewVector(x);
    SetZeroVector(x, sumResult);
    if (axis == 0){
        for (int i=0; i<x; i++) for (int j=0; j<y; j++) sumResult[j] += matrix[i][j];
    }
    else if (axis == 1){
        for (int i=0; i<x; i++) for (int j=0; j<y; j++) sumResult[i] += matrix[i][j];
    }
    else{
        printf("ERROR:axis != 0\n");
        sumResult = NULL;
    }
    return sumResult;
}

//複製一個矩陣
double** CopyMatrix(int x, int y, double **matrix){
    double **newMatrix = AllocateNewMatrix(x, y);
    for(int i=0; i<x; i++) for(int j=0; j<y; j++) newMatrix[i][j] = matrix[i][j];
    return newMatrix;
}

//將矩陣每一個值都加上一個純量
void** AddMatrixValue(int x, int y, double **matrix, int value){
    for(int i=0; i<x; i++) for(int j=0; j<y; j++) matrix[i][j] += value;
}

//將矩陣對應的值做相加
double** AddMatrix(int x, int y, double **matrix1, double ** matrix2){
    double **addResult = AllocateNewMatrix(x, y);
    for(int i=0; i<x; i++) for(int j=0; j<y; j++) addResult[i][j] = matrix1[i][j] + matrix2[i][j];
    return addResult;
}

//將矩陣對應的值做相減
double** SubMatrix(int x, int y, double **matrix1, double ** matrix2){
    double **subResult = AllocateNewMatrix(x, y);
    for(int i=0; i<x; i++) for(int j=0; j<y; j++) subResult[i][j] = matrix1[i][j] - matrix2[i][j];
    return subResult;
}

//將矩陣每一個值都乘上一個純量
void** MulMatrixValue(int x, int y, double **matrix, int value){
    for(int i=0; i<x; i++) for(int j=0; j<y; j++) matrix[i][j] *= value;
}

//將矩陣對應的值做相乘
double** HadamardProductMatrix(int x, int y, double **matrix1, double ** matrix2){
    double **mulResult = AllocateNewMatrix(x, y);
    for(int i=0; i<x; i++) for(int j=0; j<y; j++) mulResult[i][j] = matrix1[i][j] * matrix2[i][j];
    return mulResult;
}

//將兩個矩陣做相乘
double** MultiplyMatrix(int x, int y, int z, double **matrix1, double ** matrix2){
    double **mulResult = AllocateNewMatrix(x, z);
    SetMatrixZero(x, z, mulResult);
    for (int i=0; i<x; i++){
        for (int k=0; k<y; k++){
            double tempS = matrix1[i][k];
            for (int j=0; j<z; j++) mulResult[i][j] += tempS * matrix2[k][j];
        }
    }
    return mulResult;
}

//將矩陣每一個值都除上一個純量
void** DivMatrixValue(int x, int y, double **matrix, int value){
    for(int i=0; i<x; i++) for(int j=0; j<y; j++) matrix[i][j] /= value;
}

//將矩陣對應的值做相除
double** DivMatrix(int x, int y, double **matrix1, double ** matrix2){
    double **divResult = AllocateNewMatrix(x, y);
    for(int i=0; i<x; i++) for(int j=0; j<y; j++) divResult[i][j] = matrix1[i][j] / matrix2[i][j];
    return divResult;
}

//將矩陣置換
double** TransposeMatrix(int x, int y, double** matrix){
    double** result = AllocateNewMatrix(y, x);
    for (int i=0; i<y; i++) for (int j=0; j<x; j++) result[i][j] = matrix[j][i];
    return result;
}

//取得隨機長度為sliceNums的Maxtrix
double** GetSliceMatrixByOrder(int x, int y, double **matrix, int sliceNums, int *order){
    double **sliceMatrix = AllocateNewMatrix(sliceNums, y);
    for (int i=0; i<sliceNums; i++){
        int x = order[i];
        for (int j=0; j<y; j++) sliceMatrix[i][j] = matrix[x][j];
    }
    return sliceMatrix;
}

//將one hot encoding的matrix轉成vector
double* TransferOnehotMatrixToVector(int x, int y, double** matrix){
    double* result = AllocateNewVector(x);
    for (int i=0; i<x; i++){
        result[i] = -1;
        for (int j=0; j<y; j++) if(CompareDouble(1.0f, matrix[i][j])) result[i] = j; 
        if (CompareDouble(-1, result[i])) {
            printf("ERROR:not find 1!\n");
            result = NULL;
            break;
        }
    }
    return result;
}

//根據gradient跟learning rate進行更新
void UpdateLayerByGradient(int x, int y, double **weight, double **gradient, double lr){
    for (int i=0; i<x; i++) for (int j=0; j<y; j++) weight[i][j] -= (lr * gradient[i][j]);
}