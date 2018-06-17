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

	int *A, *B;

	int N = atoi(argv[2]);

	A = (int*) malloc(N*sizeof(int));
	B = (int*) malloc(N*sizeof(int));

	for (int i = 0; i < N; i++)
	{
		A[i] = rand() % 10;
		B[i] = rand() % 10;
	}

	int numberOfElements = N / numOfThreads;

	int i, dot = 0;

	#pragma omp parallel for default(none) shared(N, A, B) private(i) reduction(+:dot)
	for (i = 0; i < N; i++)
	{
		dot += A[i]*B[i];
	}

	print_vec(A, N);
	print_vec(B, N);
	printf("sum = %d\n", dot);

	return 0;
}
