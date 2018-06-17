#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void print_vec(int *vec, int size)
{
	for (int j = 0; j < size; j++) {
		printf("%d\t", vec[j]);
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{

	printf("Hello from the main thread\n");

	if (argc != 3) {
		printf("Please provide correct number of threads and problem size\n");
		return -1;
	}

	int numOfThreads = atoi(argv[1]);
	omp_set_num_threads(numOfThreads);

	int *A, *B, *C;

	int N = atoi(argv[2]);

	A = (int*) malloc(N*sizeof(int));
	B = (int*) malloc(N*sizeof(int));
	C = (int*) malloc(N*sizeof(int));

	for (int i = 0; i < N; i++)
	{
		A[i] = rand() % 10;
		B[i] = rand() % 10;
	}

	for (int i = 0; i < N; i++)
	{
		C[i] = A[i] + B[i];
	}

	print_vec(A, N);
	print_vec(B, N);
	print_vec(C, N);

	return 0;
}
