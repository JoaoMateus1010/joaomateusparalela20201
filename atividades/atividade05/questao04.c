// Nota 0,5
// Eu não deixei claro na questão, mas ficaria mais interessante ter gerado os vetores
// apenas no processo 0. Mas não como não mencionei, está ok.
#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>

#define MASTER (0)

int main(int argc,char* argv[]){
    double t1,t2;
    int rank, numtasks,N;
    sscanf(argv[1],"%d",&N);        
    double *v1 = (double*)calloc(N,sizeof(double));
    double *v2 = (double*)calloc(N,sizeof(double));
    double *vr = (double*)calloc(N,sizeof(double));    

    for(int i=0;i<N;i++){
        v1[i]=i+1;
        v2[i]=i+1;
    }

    MPI_Init(&argc,&argv);
    t1=MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);           
    int lo = rank*(N/numtasks);
    int hi = rank*(N/numtasks)+(N/numtasks)-1;    
    //Intervalos não levam em conta os restos, como foi dito na questão    
    double SUM = 0;
    for(int i=lo;i<=hi;i++){
        vr[i]=v1[i]*v2[i];                
    }
    for(int i=lo;i<=hi;i++){             
        SUM+=vr[i];
    }        
    //Todos irão fazer uma parcela da soma e no fim irão mandar para o Master o resultado para que ele faça a soma    
    if(rank!=MASTER){
        //Código para qualquer ponto exceto o master
        MPI_Send(&SUM,1,MPI_DOUBLE,MASTER,0,MPI_COMM_WORLD);
    }else{
        //Código do Master
        double buffer;
        MPI_Status status;        
        for(int i=1;i<numtasks;i++){
            MPI_Recv(&buffer,1,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);            
            SUM+=buffer;            
        }
        printf("%f\n",SUM);
        
    }
    t2=MPI_Wtime();
    if(rank == MASTER) printf("t2-t1 = %f\n",t2-t1);
    MPI_Finalize();
    return 0;
}
