#include "mtxMul.h"
#include <stdio.h>
double **mtxMul(double **c, double **a, double **b, int n){
    //#pragma omp parallel
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            c[i][j] = 0.0;
            for (int k = 0; k < n; k++){
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

void showMtx(double **mtx,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%.2f\n",mtx[i][j]);
        }        
    }
}