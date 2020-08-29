#include "mtxMult.h"

double **AlocMat(int linhas, int colunas) {
   double **ret;
   ret = (double**)calloc(linhas,sizeof(double));
   for(int i=0;i<linhas;i++){
        ret[i]=(double*)calloc(colunas,sizeof(double));
   }   
   int count = 1;
   for(int i=0;i<linhas;i++){
        for(int j=0;j<colunas;j++){
            ret[i][j]=count;
            count++;
        }
    }
   return ret;
}
double mtxMul(double **c, double **a, double **b, int n){
    start=clock();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            c[i][j] = 0.0;
            for (int k = 0; k < n; k++){
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }       
    end=clock();
    cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
    return cpu_time_used;
}

void showMtx(double **mtx,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("[%d][%d]=%.2f ",i,j,mtx[i][j]);
        }        
        printf("\n");
    }
}