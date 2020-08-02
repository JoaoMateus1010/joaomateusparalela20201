all:
	gcc -fopenmp -o parallel_sum_a parallel_sum_a.c
	gcc -fopenmp -o parallel_sum_b parallel_sum_b.c
a:
	gcc -fopenmp -o parallel_sum_a parallel_sum_a.c
	./parallel_sum_a
b:
	gcc -fopenmp -o parallel_sum_b parallel_sum_b.c
	./parallel_sum_b
clean:	
	rm parallel_sum_a parallel_sum_b