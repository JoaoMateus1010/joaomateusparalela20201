#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>

#define MASTER (0)

int main(int argc,char* argv[]){        
    float t1,t2;       
    int rank, numtasks,N;
    sscanf(argv[1],"%d",&N);        
    int v1[N],v2[N],result;    

    for(int i=0;i<N;i++){        
        v1[i]=i;
        v2[i]=i;
    }

    MPI_Init(&argc,&argv);
    //t1 = MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);    
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);           
    unsigned long int lo = rank*(N/numtasks)+1;
    unsigned long int hi = rank*(N/numtasks)+(N/numtasks);    
    //Intervalos não levam em conta os restos, como foi dito na questão    
    unsigned long int SUM = 0;
    for(int i=lo;i<=hi;i++){
        SUM+=i;
    }    
    //printf("RANK : %d result P: -> %d\n",rank,SUM);
    //Todos irão fazer uma parcela da soma e no fim irão mandar para o Master o resultado para que ele faça a soma    
    if(rank!=MASTER){
        //Código para qualquer ponto exceto o master
        MPI_Send(&SUM,1,MPI_UNSIGNED_LONG,MASTER,0,MPI_COMM_WORLD);
    }else{
        //Código do Master
        unsigned long int buffer;
        MPI_Status status;        
        for(int i=1;i<numtasks;i++){
            MPI_Recv(&buffer,1,MPI_UNSIGNED_LONG,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);            
            SUM+=buffer;            
        }
        printf("%ld\n",SUM);
        
    }
    //t2 = MPI_Wtime();
    //printf("t2-t1=%f\n",t2-t1);
    MPI_Finalize();    
    return 0;
}