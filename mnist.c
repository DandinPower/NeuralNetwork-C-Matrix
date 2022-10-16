#include "include/matrix.h"
#include "include/libs.h"
#include "include/activation.h"
#include "include/vector.h"
#include "include/loss.h"
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
#define BATCH_SIZE 128
#define LEARNING_RATE 0.001
#define EPOCHS_NUMS 10001

#define IMAGE_NORMALIZE 255

double** layer_1;
double** layer_2;
double** updateLayer1;
double** updateLayer2;
double* losses;
double* accuracies;


//讀取資料集的Y
double** ReadMnistLabel(){
    double** yTrain = AllocateNewMatrix(TRAIN_DATA_SIZE, CLASS_NUMS);
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
double** ReadMnistImage(){
    double** xTrain = AllocateNewMatrix(TRAIN_DATA_SIZE, INPUT_DIMENSIONS);
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
double** ForwardBackwardPass(double **x, double **y){
    double** xLayer1 = MultiplyMatrix(BATCH_SIZE, INPUT_DIMENSIONS, LAYER1_UNITS, x, layer_1);
    double** xSigmoid = sigmoid(BATCH_SIZE, LAYER1_UNITS, xLayer1);
    double** xLayer2 = MultiplyMatrix(BATCH_SIZE, LAYER1_UNITS, LAYER2_UNITS, xSigmoid, layer_2);
    double** out = softmax(BATCH_SIZE, LAYER2_UNITS, xLayer2);
    double** tempError = SubMatrix(BATCH_SIZE, LAYER2_UNITS, out, y);
    MulMatrixValue(BATCH_SIZE, LAYER2_UNITS, tempError, 2);
    DivMatrixValue(BATCH_SIZE, LAYER2_UNITS, tempError,LAYER1_UNITS);
    double** dSoftmaxXLayer2 = dSoftmax(BATCH_SIZE, LAYER2_UNITS, xLayer2);
    double** tempError2 = HadamardProductMatrix(BATCH_SIZE, LAYER2_UNITS, tempError, dSoftmaxXLayer2);
    double** xSigmoidT = TransposeMatrix(BATCH_SIZE, LAYER1_UNITS, xSigmoid);
    updateLayer2 = MultiplyMatrix(LAYER1_UNITS, BATCH_SIZE, LAYER2_UNITS, xSigmoidT, tempError2);
    double** errorT = TransposeMatrix(BATCH_SIZE, LAYER2_UNITS, tempError2);
    double** tempError3 = MultiplyMatrix(LAYER1_UNITS, LAYER2_UNITS, BATCH_SIZE, layer_2, errorT);
    double** error3T = TransposeMatrix(LAYER1_UNITS, BATCH_SIZE, tempError3);
    double** dSigmoidXLayer1 = dSigmoid(BATCH_SIZE, LAYER1_UNITS, xLayer1);
    double** tempError4 = HadamardProductMatrix(BATCH_SIZE, LAYER1_UNITS, error3T, dSigmoidXLayer1);
    double** xT = TransposeMatrix(BATCH_SIZE, INPUT_DIMENSIONS, x);
    updateLayer1 = MultiplyMatrix(INPUT_DIMENSIONS, BATCH_SIZE, LAYER1_UNITS, xT, tempError4);
    FreeMatrix(xLayer1);
    FreeMatrix(xSigmoid);
    FreeMatrix(xLayer2);
    FreeMatrix(tempError);
    FreeMatrix(dSoftmaxXLayer2);
    FreeMatrix(tempError2);
    FreeMatrix(xSigmoidT);
    FreeMatrix(errorT);
    FreeMatrix(tempError3);
    FreeMatrix(error3T);
    FreeMatrix(dSigmoidXLayer1);
    FreeMatrix(tempError4);
    FreeMatrix(xT);
    return out;
}

//Mnist的forward passing
double** ForwardPassOnly(double **x, double **y){
    double** xLayer1 = MultiplyMatrix(BATCH_SIZE, INPUT_DIMENSIONS, LAYER1_UNITS, x, layer_1);
    double** xSigmoid = sigmoid(BATCH_SIZE, LAYER1_UNITS, xLayer1);
    double** xLayer2 = MultiplyMatrix(BATCH_SIZE, LAYER1_UNITS, LAYER2_UNITS, xSigmoid, layer_2);
    double** out = softmax(BATCH_SIZE, LAYER2_UNITS, xLayer2);
    FreeMatrix(xLayer1);
    FreeMatrix(xSigmoid);
    FreeMatrix(xLayer2);
    return out;
}

//單個epoch的訓練流程
void Training(int epoch, double** xTrain, double** yTrain, double* yVector){
    int* order = GetShuffleOrder(TRAIN_DATA_SIZE); 
    double* yVectorSlice = GetSliceVectorByOrder(TRAIN_DATA_SIZE, yVector, BATCH_SIZE, order);
    double** yTrainSlice = GetSliceMatrixByOrder(TRAIN_DATA_SIZE, CLASS_NUMS, yTrain, BATCH_SIZE, order);
    double** xTrainSlice = GetSliceMatrixByOrder(TRAIN_DATA_SIZE, INPUT_DIMENSIONS, xTrain, BATCH_SIZE, order);
    double** out = ForwardBackwardPass(xTrainSlice, yTrainSlice);
    double* category = Argmax(BATCH_SIZE, LAYER2_UNITS, out, 1);
    accuracies[epoch] = CountVectorDifferenceMean(BATCH_SIZE, category, yVectorSlice);
    losses[epoch] = MeanSquareError(BATCH_SIZE, category, yVectorSlice);
    UpdateLayerByGradient(INPUT_DIMENSIONS, LAYER1_UNITS, layer_1, updateLayer1, LEARNING_RATE);
    UpdateLayerByGradient(LAYER1_UNITS, LAYER2_UNITS, layer_2, updateLayer2, LEARNING_RATE);
    if(epoch % 500 == 0) printf("For %dth epoch: train accuracy: %lf\n", epoch, accuracies[epoch]);
    FreeMatrix(yTrainSlice);
    FreeMatrix(xTrainSlice);
    FreeMatrix(out);
    FreeVector(yVectorSlice);
    FreeVector(category);
    free(order);
}

//訓練參數
void Train(){
    srand(time(NULL));
    layer_1 = InitWeightMatrix(INPUT_DIMENSIONS, LAYER1_UNITS);
    layer_2 = InitWeightMatrix(LAYER1_UNITS, LAYER2_UNITS);
    double** yTrain = ReadMnistLabel();
    double** xTrain = ReadMnistImage();
    double* yVector = TransferOnehotMatrixToVector(TRAIN_DATA_SIZE, CLASS_NUMS, yTrain);
    losses = AllocateNewVector(EPOCHS_NUMS);
    accuracies = AllocateNewVector(EPOCHS_NUMS);
    for (int i=0; i<EPOCHS_NUMS; i++) Training(i, xTrain, yTrain, yVector);
    WriteLayerToParams(INPUT_DIMENSIONS, LAYER1_UNITS, layer_1, "backups/layer1.params");
    WriteLayerToParams(LAYER1_UNITS, LAYER2_UNITS, layer_2, "backups/layer2.params");
    WriteVectorToRecords(EPOCHS_NUMS, accuracies, "backups/accuracy.records");
    WriteVectorToRecords(EPOCHS_NUMS, losses, "backups/loss.records");
    FreeMatrix(yTrain);
    FreeMatrix(xTrain);
    FreeMatrix(layer_1);
    FreeMatrix(layer_2);
    FreeMatrix(updateLayer1);
    FreeMatrix(updateLayer2);
    FreeVector(yVector);
    FreeVector(losses);
    FreeVector(accuracies);
}

//讀參數近來後進行inference
void Inference(){
    layer_1 = LoadLayerByParams(INPUT_DIMENSIONS, LAYER1_UNITS, "backups/layer1.params");
    layer_2 = LoadLayerByParams(LAYER1_UNITS, LAYER2_UNITS, "backups/layer2.params");
    double** yTrain = ReadMnistLabel();
    double** xTrain = ReadMnistImage();
    double* yVector = TransferOnehotMatrixToVector(TRAIN_DATA_SIZE, CLASS_NUMS, yTrain);
    double** out;
    double* category;
    out = ForwardPassOnly(xTrain, yTrain);
    category = Argmax(BATCH_SIZE, LAYER2_UNITS, out, 1);
    double accuracy = CountVectorDifferenceMean(BATCH_SIZE, category, yVector);
    double loss= MeanSquareError(BATCH_SIZE, category, yVector);
    printf("test accuracy: %lf, loss: %lf\n", accuracy, loss);
    FreeMatrix(out);
    FreeVector(category);
    FreeMatrix(yTrain);
    FreeMatrix(xTrain);
    FreeMatrix(layer_1);
    FreeMatrix(layer_2);
    FreeVector(yVector);
}


int main(void){
    //Train();
    Inference();
    return 0;
}