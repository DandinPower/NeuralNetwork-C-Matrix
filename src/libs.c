#include "../include/libs.h"
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