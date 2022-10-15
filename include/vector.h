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

#endif