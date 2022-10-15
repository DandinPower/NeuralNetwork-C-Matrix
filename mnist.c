#include "include/matrix.h"
#include "include/libs.h"
#include "include/activation.h"
#include "include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <time.h>

#define LABEL_N 100
#define IMAGE_N 5000
#define INPUT_DIMENSIONS 784
#define LAYER1_UNITS 128
#define LAYER2_UNITS 10

#define TRAIN_DATA_SIZE 60000
#define CLASS_NUMS 10
#define BATCH_SIZE 100

#define IMAGE_NORMALIZE 255

double** layer_1;
double** layer_2;


//讀取資料集的Y
double** ReadMnistLabel(){
    double **yTrain = AllocateNewMatrix(TRAIN_DATA_SIZE, CLASS_NUMS);
    FILE *fp;
    char str[LABEL_N + 1];
    if ( (fp = fopen("dataset/label.txt", "rt")) == NULL ) {
        puts("Fail to open file!");
        exit(0);
    }
    int i = 0;
    int j = 0;
    while( fgets(str, LABEL_N, fp) != NULL ) {
        const char* d = ",";
        char *p;
        p = strtok(str, d);
        j = 0;
        while (p != NULL) {
            if (j == CLASS_NUMS) break;
            sscanf(p, "%lf", &yTrain[i][j]);
            p = strtok(NULL, d);		   
            j++;
        }
        i++;
    }
    printf("Label Rows: %d, Label Columns: %d\n", i, j);
    fclose(fp);
    return yTrain;
}

//讀取資料集的X
double ** ReadMnistImage(){
    double **xTrain = AllocateNewMatrix(TRAIN_DATA_SIZE, INPUT_DIMENSIONS);
    FILE *fp;
    char str[IMAGE_N + 1];
    if ( (fp = fopen("dataset/minist.txt", "rt")) == NULL ) {
        puts("Fail to open file!");
        exit(0);
    }
    int i = 0;
    int j = 0;
    while( fgets(str, IMAGE_N, fp) != NULL ) {
        const char* d = ",";
        char *p;
        p = strtok(str, d);
        j = 0;
        while (p != NULL) {
            if (j == INPUT_DIMENSIONS) break;
            sscanf(p, "%lf", &xTrain[i][j]);
            p = strtok(NULL, d);		   
            j++;
        }
        i++;
    }
    printf("Image Rows: %d, Image Columns: %d\n", i, j);
    fclose(fp);
    return xTrain;
}

//Mnist的forward & backward passing
void ForwardBackwardPass(double **x, double **y){
    double **xLayer1 = MultiplyMatrix(BATCH_SIZE, INPUT_DIMENSIONS, LAYER1_UNITS, x, layer_1);
    //double **xSigmoid = sigmoid(BATCH_SIZE, LAYER1_UNITS, xLayer1);
    ShowMatrix(BATCH_SIZE, LAYER1_UNITS, xLayer1);
    double **xSigmoid = sigmoid(BATCH_SIZE, LAYER1_UNITS, xLayer1);
    ShowMatrix(BATCH_SIZE, LAYER1_UNITS, xSigmoid);
}

int main(void){
    srand(time(NULL));
    layer_1 = InitWeightMatrix(INPUT_DIMENSIONS, LAYER1_UNITS);
    layer_2 = InitWeightMatrix(LAYER1_UNITS, LAYER2_UNITS);
    double** yTrain = ReadMnistLabel();
    double** xTrain = ReadMnistImage();
    DivMatrixValue(TRAIN_DATA_SIZE, INPUT_DIMENSIONS, xTrain, IMAGE_NORMALIZE);
    int* order = GetShuffleOrder(TRAIN_DATA_SIZE); 
    double** yTrainSlice = GetSliceMatrixByOrder(TRAIN_DATA_SIZE, CLASS_NUMS, yTrain, BATCH_SIZE, order);
    double** xTrainSlice = GetSliceMatrixByOrder(TRAIN_DATA_SIZE, INPUT_DIMENSIONS, xTrain, BATCH_SIZE, order);
    free(order);
    ForwardBackwardPass(xTrainSlice, yTrainSlice);
    return 0;
}