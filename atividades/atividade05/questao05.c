#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SOURCE (0)
#define TRUE (1)
#define FALSE (0)

int main(int argc, char* argv[]){
    int numtasks, rank, num,tag=0;  
    MPI_Init(&argc,&argv);        
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    sscanf(argv[1],"%d",&num);
    int buffer = num;
    MPI_Status status;
    while(buffer>0){        
        //printf("Fluxo %d send [%d,%d]\n",buffer,rank,((rank==numtasks-1)?SOURCE:rank+1));
        //printf("Fluxo %d recv [%d,%d]\n",buffer,((rank==SOURCE)?numtasks-1:rank-1),rank);                
        MPI_Send(&buffer,1,MPI_INT,((rank==numtasks-1)?SOURCE:rank+1),tag,MPI_COMM_WORLD);                
        MPI_Recv(&buffer,1,MPI_INT,((rank==SOURCE)?numtasks-1:rank-1),tag,MPI_COMM_WORLD,&status);                                                        
        buffer--;                                      
    }
    if(rank==SOURCE) printf("%d",buffer);
    MPI_Finalize();    
    return 0;
}