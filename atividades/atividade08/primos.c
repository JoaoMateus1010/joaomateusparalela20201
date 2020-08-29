#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>

#define ROOT    (0)

#define IS_PRIMO    (0)

#define MAX (1000000)
#define MIN (1)

int primo (int n);
int main(int argc,char* argv[]){
    int numtasks,rank,len,rc;        
    int* vet;//Vetor de números
    int* out_buff;//Buffer para cada rank
    int* primos_buffer;//buffer de primos
    int chunk;//Tamanho do chunk
    int count_primos = 0;//Quantidade de primos para o vetor primos_buffer ir escalonando o tamanho    
    int total_primos;//Quantidade total de inteiros que foi contabilizado
    int* total_primos_buffer;//Vetor com todos os números inteiros

    MPI_Init(&argc,&argv); // Inicializando o MPI
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);//Recupera o número de tasks
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);//recupera o identificador de cada processo
    chunk=(int) MAX/numtasks;     
    out_buff=(int*)calloc(chunk,sizeof(int));
    if(rank==ROOT){
        vet=(int*)calloc(MAX,sizeof(int));
        for(int i=0;i<MAX;i++){
            vet[i]=i+1;                        
        } 
    }
    MPI_Scatter(vet,chunk,MPI_INT,out_buff,chunk,MPI_INT,ROOT,MPI_COMM_WORLD); 
    primos_buffer=(int*)calloc(chunk,sizeof(int));
    for(int i=0;i<chunk;i++){                               
        //printf("R %d = %d\n",rank,out_buff[i]);
        if(primo(out_buff[i])==IS_PRIMO){
            count_primos++;
        }
    }    
    primos_buffer=(int*)calloc(count_primos,sizeof(int));
    count_primos=0;    
    for(int i=0;i<chunk;i++){                               
        if(primo(out_buff[i])==IS_PRIMO){
            primos_buffer[count_primos]=out_buff[i];
            count_primos++;
        }
    }

    for(int i=0;i<count_primos;i++){
        printf("R %d [%d]=%d\n",rank,i,primos_buffer[i]);
        /*(1)*/
        /*
            Neste ponto eu tenho todos os primos em um vetor de tamanho diretente pra cada rank, esse tamanho é referente a quantidade de números primos.
            no caso do valor N=20, e numero de tasks = 4

            Rank= 0 | [0]=1
            Rank= 0 | [1]=2
            Rank= 0 | [2]=3
            Rank= 0 | [3]=5

            Rank= 1 | [0]=7

            Rank= 2 | [0]=11
            Rank= 2 | [1]=13

            Rank= 3 | [0]=17
            Rank= 3 | [1]=19            
            ou seja, o tamanho dos vetores representa a quantidade de primos que cada rank encontrou.
        */
    }    
    free(out_buff);
    MPI_Reduce(&count_primos,&total_primos,1,MPI_INT,MPI_SUM,ROOT,MPI_COMM_WORLD);
    /*(2)*/        
    /*
        Neste ponto eu tenho a quantidade total de números primos encontrados, deste ponto eu aloco um vetor que terá todos os números
        que vem do Gather
    */
    if(rank==ROOT){        
        total_primos_buffer=(int*)calloc(total_primos,sizeof(int));                          
    }    
    MPI_Gather(primos_buffer,count_primos,MPI_INT,total_primos_buffer,count_primos,MPI_INT,ROOT,MPI_COMM_WORLD);
    /*
        Neste ponto eu não estou conseguindo desenvolver o Gather, minha intenção era juntar as partes de cada contribuição feita pelos ranks
        voltando para o caso (1) onde o N=20
        sabendo que a quantidade de números primos que cada rank encontrou foi:
        Rank=0 encontrou 4
        Rank=1 encontrou 1
        Rank=2 encontrou 2
        Rank=3 encontrou 2
        quando é feito a redução eu consigo o total, que neste caso é 9.
        minha intenção do Gather era ter um vetor parecido com isso:
        | 1 | 2 | 3 | 5 | 7 | 11 | 13 | 17 | 19 |
        
        Mas estou tendo como resposta:
        | 1 | 2 | 3 | 5 | 7 | 0 | 0 | 0 | 11 |

        Esses 0 vem da função calloc, por padrão ela incializa os valores com 0, quando executo o código sem fazer essa alocação de memória
         na variável total_primos_buffer no lugar desses 0's aparecem lixo de memória.
    */
    if(rank==ROOT){
            for(int i=0;i<total_primos;i++){
            printf(" %d ",total_primos_buffer[i]);
        }
    }
    MPI_Finalize();//Finaliza o MPI
    return 0;
}
int primo (int n) {    
    int resultado = 0;
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
        resultado++;
        break;
        }
    }
 return resultado;
}