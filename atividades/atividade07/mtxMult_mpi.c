#include "mtxMult_mpi.h"

double mtxMult_MPI(double** c,double** a,double** b,int n,int argc,char* argv[]){ // c=a*b
    int numtasks,rank,len,rc;    
    double start,end;    
    int chunk;
    MPI_Init(&argc,&argv); // Inicializando o MPI    
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);//Recupera o número de tasks
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);//recupera o identificador de cada processo        
    if(rank==ROOT) start = MPI_Wtime();
    chunk = (int)n/numtasks;
    double linha_a_buffer[chunk],coluna_b_buffer[chunk],resultado;
    double buffer_results_partial[chunk];    
    double **bT = AlocMat(n,n);
    if(rank==ROOT){
        a=AlocMat(n,n);
        b=AlocMat(n,n);        
        b=Transpose(b,n);
        c=AlocMat(n,n);                   
        //showMtx(b,n);                
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            //c[i][j]=0;
            MPI_Scatter(a[i],chunk,MPI_DOUBLE,linha_a_buffer,chunk,MPI_DOUBLE,ROOT,MPI_COMM_WORLD);  
            MPI_Scatter(b[j],chunk,MPI_DOUBLE,coluna_b_buffer,chunk,MPI_DOUBLE,ROOT,MPI_COMM_WORLD); 
            for(int k=0;k<chunk;k++){
                buffer_results_partial[k]=linha_a_buffer[k]*coluna_b_buffer[k];                
                printf("T(P) %d ->[%d,%d] = %.1f \n",rank,i,j,buffer_results_partial[k]);                                
            }
            //MPI_Reduce(buffer_results_partial,&resultado,chunk,MPI_DOUBLE,MPI_SUM,ROOT,MPI_COMM_WORLD);                                            
        }        
    }     
    //MPI_Scatter(b[3],chunk,MPI_DOUBLE,coluna_b_buffer,chunk,MPI_DOUBLE,ROOT,MPI_COMM_WORLD);                             
    for(int i=0;i<chunk;i++){
        //printf("R(L) %d -> %.1f \n",rank,linha_a_buffer[i]);
        //printf("R(C) %d -> %.1f \n",rank,coluna_b_buffer[i]);
        //printf("T(P) %d -> %.1f \n",rank,buffer_results_partial[i]);
    }
    if(rank==ROOT) end = MPI_Wtime();    
    if(rank==ROOT) printf("%f",(end-start));
    MPI_Finalize();//Finaliza o MPI
}
double** Transpose(double** MTX,int n){
    double** ret=AlocMat(n,n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            ret[i][j]=MTX[j][i];
        }
    }
    return ret;
}