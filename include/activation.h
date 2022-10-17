#ifndef ACTIVATION_H
#define ACTIVATION_H

//將matrix做sigmoid
double** sigmoid(int x, int y, double **matrix);

//將matrix做sigmoid的偏微分
double** dSigmoid(int x, int y, double **matrix);

//對第1維度的值做softmax
double** softmax(int x, int y, double **matrix);

//以第1維為基底做softmax的偏微分
double** dSoftmax(int x, int y, double **matrix);

#endif