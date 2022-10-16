#ifndef VECTOR_H
#define VECTOR_H

//初始化vector的記憶體空間
double* AllocateNewVector(int x);

//釋放vector的記憶體空間
void FreeVector(double *vector);

//將vector值設為0
void SetZeroVector(int x, double *vector);

//印出vector的值
void ShowVector(int x, double *vector);

//取得隨機長度為sliceNums的Vector
double* GetSliceVectorByOrder(int x, double *vector, int sliceNums, int *order);

//計算兩個矩陣的差異並取平均值
double CountVectorDifferenceMean(int x, double* vector1, double* vector2);

#endif