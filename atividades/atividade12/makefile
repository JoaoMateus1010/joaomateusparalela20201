
all: 
	gcc -I/usr/local/cuda/include/ transpose_opencl.c -o main -lOpenCL
	./main NVIDIA GPU 64 0

clean:
	rm main
