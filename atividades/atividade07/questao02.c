#include "mtxMult_mpi.h"

int main(int argc,char* argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    double** c,** b,** a;    

    mtxMult_MPI(c,a,b,size,argc,argv);
    /*
    int cont = 1;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            printf("%d ",cont);
            cont++;
        }
        printf("\n");
    }*/
}