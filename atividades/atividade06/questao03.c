#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ROOT    (0)

int main(int argc,char* argv[]){   
    double t1,t2;         
    int numtasks,rank,len,rc;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    float number_vect_0,number_vect_1;
    int size_both_vect,chunk;    
    float total_sum;
    sscanf (argv[1], "%f", &number_vect_0);     
    sscanf (argv[2], "%f", &number_vect_1);     
    sscanf (argv[3], "%d", &size_both_vect);     
    
    float* vect_0=(float*)calloc(size_both_vect,sizeof(float));
    float* vect_1=(float*)calloc(size_both_vect,sizeof(float));

    for(int i=0;i<size_both_vect;i++){
        vect_0[i]=number_vect_0;
        vect_1[i]=number_vect_1;
    }               
    
    MPI_Init(&argc,&argv); // Inicializando o MPI    
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);//Recupera o número de tasks
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);//recupera o identificador de cada processo
    MPI_Get_processor_name(hostname,&len);//Recupera o nome da máquina    
    if(rank==ROOT){
        t1 = MPI_Wtime();
    } 
    MPI_Bcast(&size_both_vect,1,MPI_INT,ROOT,MPI_COMM_WORLD);

    chunk = (int)size_both_vect/numtasks;        

    float* vet_temp_0 = (float*)calloc(chunk,sizeof(float));        
    float* vet_temp_1 = (float*)calloc(chunk,sizeof(float));      

    MPI_Scatter(vect_0,chunk,MPI_FLOAT,vet_temp_0,chunk,MPI_FLOAT,ROOT,MPI_COMM_WORLD);    
    MPI_Scatter(vect_1,chunk,MPI_FLOAT,vet_temp_1,chunk,MPI_FLOAT,ROOT,MPI_COMM_WORLD);            

    for(int i=0;i<chunk;i++){
        vet_temp_0[i]*=vet_temp_1[i];
    }
    
    MPI_Gather(vet_temp_0,chunk,MPI_FLOAT,vect_0,chunk,MPI_FLOAT,ROOT,MPI_COMM_WORLD);
    if(rank==ROOT){
        for(int i=0;i<size_both_vect;i++){
            total_sum+=vect_0[i];
        }
        printf("PRODUTO: %.1f",total_sum);
    }
    if(rank==ROOT){ t2 = MPI_Wtime();}
    if(rank==ROOT) printf("%f",t2-t1);                    
    MPI_Finalize();//Finaliza o MPI
    free(vect_0);
    free(vect_1);        
    return 0;
}