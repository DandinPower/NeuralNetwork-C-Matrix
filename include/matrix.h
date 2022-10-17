<<<<<<< HEAD
#ifndef MATRIX_H
#define MATRIX_H

//初始化matrix的記憶體空間
double** AllocateNewMatrix(int x, int y);

//釋放Matrix的記憶體空間
void FreeMatrix(double **matrix);

//將矩陣全部值設為0
void SetMatrixZero(int x, int y, double **matrix);

//初始化參數
double** InitWeightMatrix(int x, int y);

//印出Matrix的值
void ShowMatrix(int x, int y, double **weights);

//取出matrix在0維[xIndex]內的最大值 && 如果xIndex == -1則取global最大值
double MaxMatrix(int x, int y, double **matrix, int xIndex);

//計算選定的軸的sum && 目前僅有實作axis == 0
double* SumMatrix(int x, int y, double **matrix, int axis);

//複製一個矩陣
double** CopyMatrix(int x, int y, double **matrix);

//將矩陣每一個值都加上一個純量
void** AddMatrixValue(int x, int y, double **matrix, int value);
//將矩陣對應的值做相加
double** AddMatrix(int x, int y, double **matrix1, double ** matrix2);

//將矩陣對應的值做相減
double** SubMatrix(int x, int y, double **matrix1, double ** matrix2);

//將矩陣每一個值都乘上一個純量
void** MulMatrixValue(int x, int y, double **matrix, int value);

//將矩陣對應的值做相乘
double** HadamardProductMatrix(int x, int y, double **matrix1, double ** matrix2);

//將兩個矩陣做相乘
double** MultiplyMatrix(int x, int y, int z, double **matrix1, double ** matrix2);

//將矩陣每一個值都除上一個純量
void** DivMatrixValue(int x, int y, double **matrix, int value);

//將矩陣對應的值做相除
double** DivMatrix(int x, int y, double **matrix1, double ** matrix2);

//將矩陣置換
double** TransposeMatrix(int x, int y, double** matrix);
//取得隨機長度為sliceNums的Maxtrix
double** GetSliceMatrixByOrder(int x, int y, double **matrix, int sliceNums, int *order);

//將one hot encoding的matrix轉成vector
double* TransferOnehotMatrixToVector(int x, int y, double** matrix);

//根據gradient跟learning rate進行更新
void UpdateLayerByGradient(int x, int y, double **weight, double **gradient, double lr);
=======
#ifndef MATRIX_H
#define MATRIX_H

//初始化matrix的記憶體空間
double** AllocateNewMatrix(int x, int y);

//釋放Matrix的記憶體空間
void FreeMatrix(double **matrix);

//將矩陣全部值設為0
void SetMatrixZero(int x, int y, double **matrix);

//初始化參數
double** InitWeightMatrix(int x, int y);

//印出Matrix的值
void ShowMatrix(int x, int y, double **weights);

//取出matrix在0維[xIndex]內的最大值 && 如果xIndex == -1則取global最大值
double MaxMatrix(int x, int y, double **matrix, int xIndex);

//計算選定的軸的sum && 目前僅有實作axis == 0
double* SumMatrix(int x, int y, double **matrix, int axis);

//複製一個矩陣
double** CopyMatrix(int x, int y, double **matrix);

//將矩陣每一個值都加上一個純量
void AddMatrixValue(int x, int y, double **matrix, int value);
//將矩陣對應的值做相加
double** AddMatrix(int x, int y, double **matrix1, double ** matrix2);

//將矩陣對應的值做相減
double** SubMatrix(int x, int y, double **matrix1, double ** matrix2);

//將矩陣每一個值都乘上一個純量
void MulMatrixValue(int x, int y, double **matrix, int value);

//將矩陣對應的值做相乘
double** HadamardProductMatrix(int x, int y, double **matrix1, double ** matrix2);

//將兩個矩陣做相乘
double** MultiplyMatrix(int x, int y, int z, double **matrix1, double ** matrix2);

//將矩陣每一個值都除上一個純量
void DivMatrixValue(int x, int y, double **matrix, int value);

//將矩陣對應的值做相除
double** DivMatrix(int x, int y, double **matrix1, double ** matrix2);

//將矩陣置換
double** TransposeMatrix(int x, int y, double** matrix);
//取得隨機長度為sliceNums的Maxtrix
double** GetSliceMatrixByOrder(int x, int y, double **matrix, int sliceNums, int *order);

//將one hot encoding的matrix轉成vector
double* TransferOnehotMatrixToVector(int x, int y, double** matrix);

//根據gradient跟learning rate進行更新
void UpdateLayerByGradient(int x, int y, double **weight, double **gradient, double lr);
>>>>>>> 6f3abb31a47859724edcfb4519e32f97eb5a748a
#endif