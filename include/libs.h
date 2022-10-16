#ifndef LIBS_H
#define LIBS_H

//隨機產生-1~1的weight
double GenerateRandomValue(int x, int y, int max, int min);

//取得一個打亂過後的order vector
int* GetShuffleOrder(int sliceNums);

//計算axis維度的最大值 && 目前僅實作axis = 1
double* Argmax(int x, int y, double** matrix, int axis);

//比較double的值 1為相等0為不相等
int CompareDouble(double x, double y);
#endif