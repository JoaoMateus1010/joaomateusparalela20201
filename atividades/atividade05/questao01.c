#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define MAX (100)
#define SOURCE (0)

int main(int argc,char* argv[]){
    /*
        A quantidade de task pode ser alterada facilmente no Makefile na label q01
    */
    int rank; //Numero do rank
    int numtasks; //Número máximo de pontos executando.    

    MPI_Init(&argc,&argv); // Inicializando o MPI
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);//Recupera o número de tasks
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);//recupera o identificador de cada processo
    
    if(rank!=SOURCE){
        //printf("Ponto executando...\n");
        //Código para qualquer ponto exceto o SOURCE          
        int rand_size = (rand() / (float) RAND_MAX/rank) * MAX;
        /*
            Professor fiz uma pequena alteração na forma de gerar o número aleatório para que o tamanho do vetor seja diferente, 
            pois o rand usa a hora e tava dando o mesmo valor de size para todos os vetores, então eu adicionei uma divisão por rank, 
            assim melhora o random de cada execução.
        */
        int buffer[rand_size];
        MPI_Send(&buffer,rand_size,MPI_INT,SOURCE,0,MPI_COMM_WORLD);
        
    }else{
        //printf("SOURCE executando...\n");
        //Código para o ponto SOURCE 
        int buffer[MAX];
        MPI_Status status;
        int num_val_recebidos;
        int val_max = MAX;
        int msg_count_points[numtasks];     // Vetor com a quantidade de processos no source, assim ele pode contar a quantidade de cada envio e somar os blocos usando o indexador i   
        for(int i=0;i<numtasks;i++){ 
            msg_count_points[i]=0;
        }
        for(int i=1;i<numtasks;i++){
            MPI_Recv(&buffer,val_max,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status); // Recebendo a mensagem
            MPI_Get_count(&status,MPI_INT,&num_val_recebidos); // Recebendo o quanto foi transferido para o source
            msg_count_points[status.MPI_SOURCE]+=num_val_recebidos;
        }
        for(int i=1;i<numtasks;i++){
            printf("[%d]=%d\n",i,msg_count_points[i]);
        }
        
    }
    MPI_Finalize();
    return 0;
}