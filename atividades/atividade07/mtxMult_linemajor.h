#ifndef MTX_LINEAR_MAJOR
#define MTX_LINEAR_MAJOR
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

    #define CONVERT(i,j,s) ((s*i)+j)

    clock_t start,end;
    double cpu_time_used;

    double *AlocMat_Linear(int size);
    double mtxMul_Linear(double *c, double *a, double *b, int n);
    void showMtx_Linear(double *mtx,int n);
    
#endif