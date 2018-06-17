#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_barrier_t barrier;

typedef struct
{
    long a;
    long b;
}thread_args_t;

void* thread_runner(void* p)
{
	thread_args_t *params = (thread_args_t*) p;
	printf("I'm a thread my_id = a = %ld, b = %ld\n", params->a, params->b);
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

	thread_args_t params[numOfThreads];

	for (long i = 0; i < numOfThreads; i++)
	{
		params[i].a = i;
		params[i].b = 5;
		pthread_create(&tid[i], NULL, thread_runner, &params[i]);
	}

	for (long i = 0; i < numOfThreads; i++)
	{
		pthread_join(tid[i], NULL);
	}

	return 0;
}
