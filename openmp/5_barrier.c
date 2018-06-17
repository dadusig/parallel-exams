#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char const *argv[])
{

	printf("Hello from the main thread\n");

	if (argc != 2) {
		printf("Please provide correct number of threads\n");
		return -1;
	}

	int numOfThreads = atoi(argv[1]);
	omp_set_num_threads(numOfThreads);

	#pragma omp parallel
	{
		int my_id = omp_get_thread_num();
		printf("I am thread %d\n", my_id);

		#pragma omp barrier

		printf("%d\n", my_id);
	}

	return 0;
}
