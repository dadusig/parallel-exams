#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
*  Συγχρονισμός με φράγμα

Η έξοδος που θέλω είναι:

Hello from the main thread
I'm a thread 0
I'm a thread 1
I'm a thread 3
I'm a thread 4
I'm a thread 5
I'm a thread 2
I'm a thread 6
I'm a thread 7
5
7
2
6
3
0
1
4

και όχι η αρχική:

Hello from the main thread
I'm a thread 0
I'm a thread 2
I'm a thread 6
I'm a thread 7
5
7
I'm a thread 1
2
I'm a thread 5
6
3
I'm a thread 4
0
I'm a thread 3
1
4

*/

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
