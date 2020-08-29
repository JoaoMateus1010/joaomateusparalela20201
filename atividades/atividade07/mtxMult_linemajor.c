#include "mtxMult_linemajor.h"

double *AlocMat_Linear(int size){//Aloca uma matriz sizeXsize na representação linear
    double* mtx = (double*)calloc(size*size,sizeof(double));
    for(int i=0;i<size*size;i++){
        mtx[i]=i;
    }
    return mtx;    
}

double mtxMul_Linear(double *c, double *a, double *b, int n){
    start = clock();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            c[CONVERT(i,j,n)] = 0.0;
            for (int k = 0; k < n; k++){
                c[CONVERT(i,j,n)] = c[CONVERT(i,j,n)] + a[CONVERT(i,k,n)] * b[CONVERT(k,j,n)];
            }
        }
    }
    end=clock();
    cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
    return cpu_time_used;
}

void showMtx_Linear(double *mtx,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("[%d]=%.2f ",CONVERT(i,j,n),mtx[CONVERT(i,j,n)]);
        }
        printf("\n");
    }
}