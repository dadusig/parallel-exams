#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
*  Αθροισμα του διανυσματος Α
*/

int *A;
int numOfThreads, N;

int sum;

pthread_mutex_t lock;


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

	int my_sum = 0;

	for (int i = my_start; i < my_end; i++)
	{
		my_sum += A[i];
	}

	pthread_mutex_lock(&lock);
	sum += my_sum;
	pthread_mutex_unlock(&lock);
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

	for (int i = 0; i < N; i++)
	{
		A[i] = rand() % 10;
	}

	pthread_t* tid = (pthread_t*) malloc(numOfThreads * sizeof(pthread_t));

	pthread_mutex_init(&lock, NULL);

	for (long i = 0; i < numOfThreads; i++)
	{
		pthread_create(&tid[i], NULL, thread_runner, (void*) i);
	}

	for (long i = 0; i < numOfThreads; i++)
	{
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&lock);

	print_vec(A, N);

	printf("sum = %d\n", sum);

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
