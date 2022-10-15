#ifndef LIBS_H
#define LIBS_H

//隨機產生-1~1的weight
double GenerateRandomValue(int x, int y, int max, int min);

//取得一個打亂過後的order vector
int* GetShuffleOrder(int sliceNums);
#endif