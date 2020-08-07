#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>

#define MASTER (0)

int main(int argc,char* argv[]){

    int rank, numtasks,N;
    sscanf(argv[1],"%d",&N);        
    int *v1 = (int*)calloc(N,sizeof(int));
    int *v2 = (int*)calloc(N,sizeof(int));
    int *vr = (int*)calloc(N,sizeof(int));    

    for(int i=0;i<N;i++){
        v1[i]=i+1;
        v2[i]=i+1;
    }

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);           
    int lo = rank*(N/numtasks);
    int hi = rank*(N/numtasks)+(N/numtasks)-1;    
    //Intervalos não levam em conta os restos, como foi dito na questão    
    int SUM = 0;
    for(int i=lo;i<=hi;i++){
        vr[i]=v1[i]*v2[i];                
    }
    for(int i=lo;i<=hi;i++){             
        SUM+=vr[i];
    }        
    //Todos irão fazer uma parcela da soma e no fim irão mandar para o Master o resultado para que ele faça a soma    
    if(rank!=MASTER){
        //Código para qualquer ponto exceto o master
        MPI_Send(&SUM,1,MPI_INT,MASTER,0,MPI_COMM_WORLD);
    }else{
        //Código do Master
        int buffer;
        MPI_Status status;        
        for(int i=1;i<numtasks;i++){
            MPI_Recv(&buffer,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);            
            SUM+=buffer;            
        }
        printf("%d\n",SUM);
        
    }
    MPI_Finalize();
    return 0;
}