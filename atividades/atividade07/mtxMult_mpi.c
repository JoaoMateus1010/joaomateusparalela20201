// Nota 0,5
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
    double linha_a_buffer[chunk],coluna_b_buffer[chunk],resultado=0;
    double buffer_results_partial[chunk];          
    if(rank==ROOT){
        a=AlocMat(n,n);
        b=AlocMat(n,n);        
        b=Transpose(b,n);                                              
        c=AlocMat(n,n);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(rank==ROOT) c[i][j]=0;
	    // Era para fazer o broadcast de B e distribuir A por linhas. 
            MPI_Scatter(a[i],chunk,MPI_DOUBLE,linha_a_buffer,chunk,MPI_DOUBLE,ROOT,MPI_COMM_WORLD);  
            MPI_Scatter(b[j],chunk,MPI_DOUBLE,coluna_b_buffer,chunk,MPI_DOUBLE,ROOT,MPI_COMM_WORLD); 
            for(int k=0;k<chunk;k++){
                linha_a_buffer[k]=linha_a_buffer[k]*coluna_b_buffer[k];                                
            }            
            MPI_Reduce(linha_a_buffer,buffer_results_partial,chunk,MPI_DOUBLE,MPI_SUM,ROOT,MPI_COMM_WORLD);
            if(rank==ROOT){
                for(int k=0;k<chunk;k++){                    
                    resultado+=buffer_results_partial[k];
                }                
                c[i][j]=resultado;  
                resultado=0;
            }
        }        
    }         
    //if(rank==ROOT) showMtx(c,n);
    if(rank==ROOT) end = MPI_Wtime();    
    if(rank==ROOT) printf("%f",(end-start));
    MPI_Finalize();//Finaliza o MPI
}

// Para que serve isto?
double** Transpose(double** MTX,int n){
    double** ret=AlocMat(n,n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            ret[i][j]=MTX[j][i];
        }
    }
    return ret;
}
