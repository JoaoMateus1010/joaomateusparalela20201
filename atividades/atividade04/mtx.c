#include "mtx.h"

double **AlocMat(int linhas, int colunas) {
   double **ret;
   ret = (double**)calloc(linhas,sizeof(double));
   for(int i=0;i<linhas;i++){
        ret[i]=(double*)calloc(colunas,sizeof(double));
   }
   return ret;
}
void showMtx(double **mtx,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%.2f ",mtx[i][j]);
        }  
        printf("\n");      
    }
}