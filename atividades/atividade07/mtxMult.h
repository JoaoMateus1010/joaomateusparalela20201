#ifndef MTXMULT
#define MTXMULT

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start,end;
double cpu_time_used;

double **AlocMat(int linhas, int colunas);
double mtxMul(double **c, double **a, double **b, int n);
void showMtx(double **mtx,int n);

#endif