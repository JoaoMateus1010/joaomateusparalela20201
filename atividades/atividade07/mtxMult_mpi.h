#ifndef MTXMUL_MPI
#define MTXMUL_MPI 
    #include "mtxMult.h"    
    #include <mpi.h>
    #include <unistd.h>

    #define ROOT    (0)

    double mtxMult_MPI(double** c,double** a,double** b,int n,int argc,char* argv[]);
    double** Transpose(double** MTX,int n);

#endif