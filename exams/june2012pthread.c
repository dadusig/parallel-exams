#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void print_vec(int *vec, int size);

#define N 20
int X[N], Y[N];
int i;
int numOfThreads = 4;
int sum = 0, average;

pthread_mutex_t lock;
pthread_barrier_t barrier;




void* thread_runner(void *p)
{
	int my_id = (int) p;
	int numberOfElements = N / numOfThreads;
	int my_start = my_id * numberOfElements;
	int my_end = my_start + numberOfElements;
	int my_sum = 0;

	for (int i = my_start; i < my_end; i++)
	{
		my_sum = my_sum + X[i];
	}

	pthread_mutex_lock(&lock);
	sum += my_sum;
	pthread_mutex_unlock(&lock);

	pthread_barrier_wait(&barrier);

	if (my_id == 0)
	{
		average = sum/N;
	}

	pthread_barrier_wait(&barrier);

	for (int i = my_start; i < my_end; i++)
	{
		X[i] = X[i] - average;
	}

	for (int i = my_start; i < my_end; i++)
	{
		Y[i] = Y[i] / average;
	}

}

int main(int argc, char const *argv[])
{
	pthread_mutex_init(&lock, NULL);
	pthread_barrier_init(&barrier, NULL, numOfThreads);

	for (i = 0; i < N; i++)
	{
		X[i] = rand() % 10;
		Y[i] = rand() % 10;
	}

	// print_vec(X, N);
	// print_vec(Y, N);

	pthread_t tid[4];

	for (int i = 0; i < numOfThreads; i++)
	{
		pthread_create(&tid[i], NULL, thread_runner, (void*) i );
	}

	for (int i = 0; i < numOfThreads; i++)
	{
		pthread_join(tid[i], NULL);
	}

	print_vec(X, N);
	print_vec(Y, N);

	printf("sum = %d, average = %d\n", sum, average);

	pthread_mutex_destroy(&lock);

	return 0;
}


void print_vec(int *vec, int size)
{
	for (int j = 0; j < size; j++) {
		printf("%d\t", vec[j]);
	}
	printf("\n");
}
