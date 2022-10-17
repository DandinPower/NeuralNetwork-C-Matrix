#include "../include/activation.h"
#include "../include/matrix.h"
#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <time.h>

//將matrix做sigmoid
double** sigmoid(int x, int y, double **matrix){
    double** result = AllocateNewMatrix(x, y);
    for(int i=0; i<x; i++)for(int j=0; j<y; j++) result[i][j] = 1 / (exp( -matrix[i][j]) + 1);
    return result;
}

//將matrix做sigmoid的偏微分
double** dSigmoid(int x, int y, double **matrix){
    double** result = AllocateNewMatrix(x, y);
    for(int i=0; i<x; i++)for(int j=0; j<y; j++) result[i][j] = exp( -matrix[i][j]) / pow((exp( -matrix[i][j]) + 1), 2);
    return result;
}

//以第1維為基底做softmax
double** softmax(int x, int y, double **matrix){
    double** expElement = AllocateNewMatrix(x, y);
    double tempMax = MaxMatrix(x, y, matrix, -1);
    //每一維各自的答案
    for (int i=0; i<x; i++){
        for (int j=0; j<y; j++){
            expElement[i][j] = exp(matrix[i][j] - tempMax);
        }
    }
    double* tempSum = SumMatrix(x, y, expElement, 0);
    for (int i=0; i<x; i++) for (int j=0; j<y; j++) expElement[i][j] /= tempSum[j];
    FreeVector(tempSum);
    return expElement;
}


//以第1維為基底做softmax的偏微分
double** dSoftmax(int x, int y, double **matrix){
    double** expElement = AllocateNewMatrix(x, y);
    //每一維各自的答案
    for (int i=0; i<x; i++){
        double tempMax = MaxMatrix(x, y, matrix, -1);
        for (int j=0; j<y; j++){
            expElement[i][j] = exp(matrix[i][j] - tempMax);
        }
    }
    double* tempSum = SumMatrix(x, y, expElement, 0);
    for (int i=0; i<x; i++) for (int j=0; j<y; j++) {
        expElement[i][j] /= tempSum[j];
    }
    double **minusExpElement = CopyMatrix(x, y, expElement);
    MulMatrixValue(x, y, minusExpElement, -1);
    AddMatrixValue(x, y, minusExpElement, 1);
    double **finalResult = HadamardProductMatrix(x, y, expElement, minusExpElement);
    FreeMatrix(expElement);
    FreeMatrix(minusExpElement);
    FreeVector(tempSum);
    return finalResult;
}
