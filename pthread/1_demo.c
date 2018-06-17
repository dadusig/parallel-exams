#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
*  Every thread just says hi by printing his id
*
*  Why long my_id and not just int?
*
*  Because we are working on 64bit architectures and sizeof(void*) !=  sizeof(int)
*  which causes an compiler warning. But you can use int instead of long and ignore the warning.
*  No pro, bro!
*/

void* thread_runner(void* p)
{
	long my_id = (long) p;
	printf("I'm a thread %ld\n", my_id);
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
