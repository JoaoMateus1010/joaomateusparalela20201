// Nota 0,3. Você poderia ter utilizado a mesma chamada All_to_all, apenas alterando os parâmetros.
// Cálculo das Médias
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
                
int main(int argc, char *argv[]) {
    int i, rank, size;
    int *input_array, *output_array;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    input_array = (int *) malloc(size * sizeof(int));
    output_array = (int *) malloc(size * sizeof(int));

    for (i = 0; i < size; i++)
        input_array[i] = rank * size + i;

    printf("Input for process %d\n", rank);
    for (i = 0; i < size; i++)
        printf("%d ", input_array[i]);
    printf("\n");

    //MPI_Alltoall(input_array, 1, MPI_INT, output_array, 1, MPI_INT, MPI_COMM_WORLD);

    /*
    
    MPI_Gather(inbuffer,1,MPI_INT,outbuffer,1,MPI_INT,ROOT,MPI_COMM_WORLD);

    */
   MPI_Status *st;
    for(int i=0;i<size;i++){        
        //Tentei fazer com o Gather mas não encontrei a lógica, não sei se era possível, e se é, não sei como se faz.
        // Também não sei se era usadn send e recv que foi pedido, mas só consegui fazer assim.

        //MPI_Gather(&input_array[rank],1,MPI_INT,&output_array[i],1,MPI_INT,0,MPI_COMM_WORLD);   
                             
        MPI_Send(&input_array[rank],1,MPI_INT,i,0,MPI_COMM_WORLD);
        MPI_Recv(&output_array[i],1,MPI_INT,i,0,MPI_COMM_WORLD,st);
    }

    printf("Output for process %d\n", rank);
    for (i = 0; i < size; i++)
        printf("%d ", output_array[i]);
    printf("\n");

    free(input_array);
    free(output_array);
    MPI_Finalize();
    return 0;
}
