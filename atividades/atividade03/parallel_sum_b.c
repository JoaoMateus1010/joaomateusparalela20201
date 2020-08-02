#include <stdio.h>
#include <omp.h>

#define CHUNK_SIZE (3)

int main (int argc , char *argv[]) {
    int max;
    int ts = omp_get_max_threads();
    sscanf (argv[1], "%d", &max); 
    int sums[ts];    
    #pragma omp parallel    
    {        
        int t = omp_get_thread_num();            
        sums[t] = 0;
        int i=0;
        for(int ct=0;ct<(max/CHUNK_SIZE);ct=ct+CHUNK_SIZE+t){            
            int lo = ts*i*(CHUNK_SIZE)+1+t*CHUNK_SIZE;
            int hi = ts*i*(CHUNK_SIZE)+(CHUNK_SIZE)+(t*CHUNK_SIZE);
            hi=(hi>max)?max:hi;   
            //printf("%d -> [%d:%d]  i=%d \n",t,lo,hi,i);                                     
            for (int i = lo; i <= hi; i++){
                sums[t] = sums[t] + i;
            }
            i++;
        }        
        
    }
    int sum = 0;
    for (int t = 0; t < ts; t++){
        sum = sum + sums[t];
    }
    printf ("%d\n", sum);

    return 0;
}