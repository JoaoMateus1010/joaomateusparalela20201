#include <stdio.h>
#include <omp.h>
#include "mtx.h"

int main(int argc,char *argv[]){    
    int SIZE;
    int MAX;

    sscanf(argv[1],"%d",&SIZE);    
    sscanf(argv[2],"%d",&MAX);
    
    double** Mtx_New = AlocMat(SIZE+2,SIZE+2);
    double** Mtx_Old = AlocMat(SIZE+2,SIZE+2);

    // TRATAMENTO INICIAL
    #pragma omp parallel for collapse(2)
    for(int i=0;i<SIZE+2;i++){
        for(int j=0;j<SIZE+2;j++){            
            Mtx_New[i][j]=(i==0 || j==0 ||j==SIZE+1 || i==SIZE+1)?0:i*j;
            Mtx_Old[i][j]=(i==0 || j==0 ||j==SIZE+1 || i==SIZE+1)?0:i*j;
        }
    }
    #pragma omp parallel for
    for(int count=0;count<MAX;count++){ // Laço no número MAX        
        #pragma omp parallel for collapse(2)
        for(int i=1;i<SIZE+1;i++){ // Laço para cálculo dos valores de New baseados nos valores de Old
            for(int j=1;j<SIZE+1;j++){
                Mtx_New[i][j]=(Mtx_Old[i+1][j]+Mtx_Old[i-1][j]+Mtx_Old[i][j+1]+Mtx_Old[i][j-1])*0.25;
            }
        }
        #pragma omp parallel for collapse(2)
        for(int i=1;i<SIZE+1;i++){//Laço para atualizar os valores de Old baseados no New
            for(int j=1;j<SIZE+1;j++){
                Mtx_Old[i][j]=Mtx_New[i][j];
            }
        }

    }    
    //showMtx(Mtx_New,SIZE+2);        
    return 0;
}
