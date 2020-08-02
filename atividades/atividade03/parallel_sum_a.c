#include <stdio.h>
#include <omp.h>

int main (int argc , char *argv[]) {
    int max;
    int ts = omp_get_max_threads();
    sscanf (argv[1], "%d", &max); 
    int sums[ts];
    #pragma omp parallel
    {
        int t = omp_get_thread_num();
        int lo = t*(max / ts)+1;
        int hi = t*(max / ts)+(max / ts);                            
        sums[t] = 0;
        for (int i = lo; i <= hi; i++){
            sums[t] = sums[t] + i;
        }
        //tratamento do resto
        if((max%ts)>t){            
            sums[t]+=((omp_get_max_threads()-1)*(max / ts)+(max / ts))+t+1;
            
        }
        
    }
    int sum = 0;
    for (int t = 0; t < ts; t++){
        sum = sum + sums[t];
    }
    printf ("%d\n", sum);

    return 0;
}