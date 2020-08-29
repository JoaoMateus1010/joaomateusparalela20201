/*
#include <stdio.h>
#include "mtxMult.h"
#include "mtxMult_linemajor.h"

#define IS_LINEAR (1)

int main(int argc,char* argv[]){
    printf("-> %s \n",(!IS_LINEAR)?"NORMAL":"LINEAR");
    int mtx_size;
    sscanf(argv[1],"%d",&mtx_size);
    if(!IS_LINEAR){
        double** A,**B,**C;    
        A=AlocMat(mtx_size,mtx_size);
        B=AlocMat(mtx_size,mtx_size);
        C=AlocMat(mtx_size,mtx_size);    
        double tempo;
        tempo = mtxMul(C,A,B,mtx_size);
        printf("%.5f",tempo);
    }else{
        double* A = AlocMat_Linear(mtx_size);
        double* B = AlocMat_Linear(mtx_size);
        double* C = AlocMat_Linear(mtx_size);
        double tempo;
        tempo = mtxMul_Linear(C,A,B,mtx_size);    
        printf("%.5f",tempo);
    }
    return 0;
}
*/