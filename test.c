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

#define INPUT_DIMENSIONS 768
#define LAYER1_UNITS 128
#define LAYER2_UNITS 10

int main(void){
    srand(time(NULL));
    double** test = InitWeightMatrix(2, 3);
    test[0][0] = 1;
    test[0][1] = 2;
    test[0][2] = 1;
    test[1][0] = 3.1;
    test[1][1] = 1;
    test[1][2] = -3.11;
    double* test2 = AllocateNewVector(4);
    test2[0] = 6;
    test2[1] = 12;
    test2[2] = -1;
    test2[3] = 3;
    double* test3 = AllocateNewVector(4);
    test3[0] = 6;
    test3[1] = 10;
    test3[2] = -1;
    test3[3] = 3.1;
    printf("%lf\n", MeanSquareError(4, test2, test3));
    return 0;
}