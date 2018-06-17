#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *A, *B, *C;
int numOfThreads, N;


void print_vec(int *vec, int size);

void* thread_runner(void* p)
{
	long my_id = (long) p;
	int i, numOfElements, my_start, my_end;

	numOfElements = N / numOfThreads;
	my_start = my_id * numOfElements;
	my_end = my_start + numOfElements;
	if (my_id == numOfThreads - 1)
		my_end = N;

	printf("\n%ld\n", my_id);
	printf("numOfElements = %d\n", numOfElements);
	printf("my_start = %d\n", my_start);
	printf("my_end = %d\n", my_end);

	for (i = my_start; i < my_end; i++)
	{
		C[i] = A[i] + B[i];
	}
}

int main(int argc, char const *argv[])
{

	if (argc != 3) {
		printf("Please provide correct number of threads and problem size\n");
		return -1;
	}

	numOfThreads = atoi(argv[1]);
	N = atoi(argv[2]);

	A = (int*) malloc(N*sizeof(int));
	B = (int*) malloc(N*sizeof(int));
	C = (int*) malloc(N*sizeof(int));

	for (int i = 0; i < N; i++)
	{
		A[i] = rand() % 10;
		B[i] = rand() % 10;
	}

	pthread_t* tid = (pthread_t*) malloc(numOfThreads * sizeof(pthread_t));

	for (long i = 0; i < numOfThreads; i++)
	{
		pthread_create(&tid[i], NULL, thread_runner, (void*) i);
	}

	for (long i = 0; i < numOfThreads; i++)
	{
		pthread_join(tid[i], NULL);
	}

	print_vec(A, N);
	print_vec(B, N);
	print_vec(C, N);

	return 0;
}

void print_vec(int *vec, int size)
{
	for (int j = 0; j < size; j++) {
		printf("%d\t", vec[j]);
	}
	printf("\n");
}






// for (long i = 0; i < numOfThreads; i++)
// {
// 	pthread_create(&tid[i], NULL, thread_runner, (void*) i);
// }
//
// for (long i = 0; i < numOfThreads; i++)
// {
// 	pthread_join(tid[i], NULL);
// }
