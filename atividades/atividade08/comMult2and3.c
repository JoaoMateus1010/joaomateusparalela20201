#include <stdio.h>
#include <mpi.h>

#define DEF_KEY (0)

int main(int argc,char* argv[]){
    int numtasks,rank,len,rc;    
    int rank_comm_2,rank_comm_3,rank_comm_2_3,size_comm_2,size_comm_3,size_comm_2_3;

    MPI_Init(&argc,&argv); // Inicializando o MPI
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);//Recupera o número de tasks
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);//recupera o identificador de cada processo    
     
    MPI_Comm mult2_comm;
    MPI_Comm mult3_comm;
    MPI_Comm mult2_3_comm;

    MPI_Comm_split(MPI_COMM_WORLD,rank%2,DEF_KEY,&mult2_comm);
    MPI_Comm_split(MPI_COMM_WORLD,rank%3,DEF_KEY,&mult3_comm);
    MPI_Comm_split(MPI_COMM_WORLD,rank%6,DEF_KEY,&mult2_3_comm);

    
    MPI_Comm_size(mult2_comm,&size_comm_2);//Recupera o número de tasks
    MPI_Comm_rank(mult2_comm,&rank_comm_2);//recupera o identificador de cada processo    
            
    MPI_Comm_size(mult3_comm,&size_comm_3);//Recupera o número de tasks
    MPI_Comm_rank(mult3_comm,&rank_comm_3);//recupera o identificador de cada processo
    
    MPI_Comm_size(mult2_3_comm,&size_comm_2_3);//Recupera o número de tasks
    MPI_Comm_rank(mult2_3_comm,&rank_comm_2_3);//recupera o identificador de cada processo

    printf(" COM_2 : %d \n",rank_comm_2);
    printf(" COM_3 : %d \n",rank_comm_3);
    printf(" COM_2_3 : %d \n",rank_comm_2_3);

    MPI_Comm_free(&mult2_comm);
    MPI_Comm_free(&mult3_comm);
    MPI_Comm_free(&mult2_3_comm);

    MPI_Finalize();//Finaliza o MPI
    return 0;
}