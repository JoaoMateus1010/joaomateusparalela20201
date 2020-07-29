#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "mtxMul.h"

int **AlocMat(int linhas, int colunas) {
   double **ret;
   ret = (double**)calloc(linhas,sizeof(double));
   for(int i=0;i<linhas;i++){
        ret[i]=(double*)calloc(colunas,sizeof(double));
   }
   return ret;
}
int main(int argc,char *argv[]){    
    int size = atoi(argv[1]);    
    double **a = AlocMat(size,size);  
    double **b = AlocMat(size,size);      
    double **c = AlocMat(size,size);  
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            a[i][j]=1.0;
            b[i][j]=1.0;
            c[i][j]=0.0;
        }
    }           
    mtxMul(c,a,b,size);  
    //showMtx(c,size); 

    return 0; 
}