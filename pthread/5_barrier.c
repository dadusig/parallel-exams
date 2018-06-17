#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_barrier_t barrier;

void* thread_runner(void* p)
{
	long my_id = (long) p;

	printf("I'm a thread %ld\n", my_id);

	pthread_barrier_wait(&barrier);

	printf("%ld\n", my_id);
}

int main(int argc, char const *argv[])
{

	printf("Hello from the main thread\n");

	if (argc != 2) {
		printf("Please provide correct number of threads\n");
		return -1;
	}

	int numOfThreads = atoi(argv[1]);

	pthread_t tid[numOfThreads];

	pthread_barrier_init(&barrier, NULL, numOfThreads);

	for (long i = 0; i < numOfThreads; i++)
	{
		pthread_create(&tid[i], NULL, thread_runner, (void*) i);
	}

	for (long i = 0; i < numOfThreads; i++)
	{
		pthread_join(tid[i], NULL);
	}

	return 0;
}
