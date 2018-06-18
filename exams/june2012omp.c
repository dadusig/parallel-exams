#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_vec(int *vec, int size);

#define N 20
int X[N], Y[N];
int i;

int main(int argc, char const *argv[])
{

	int sum = 0, average;

	for (i = 0; i < N; i++)
	{
		X[i] = rand() % 10;
		Y[i] = rand() % 10;
	}

	// print_vec(X, N);
	// print_vec(Y, N);

	#pragma omp parallel default(none) shared(sum, X, Y, average) private(i)
	{
		#pragma omp for reduction(+:sum)
		for (i = 0; i < N; i++)
		{
			sum = sum + X[i];
		}

		#pragma omp single
		average = sum/N;

		#pragma omp for
		for (i = 0; i < N; i++)
		{
			X[i] = X[i] - average;
		}

		#pragma omp for
		for (i = 0; i < N; i++)
		{
			Y[i] = Y[i] / average;
		}

	}


	print_vec(X, N);
	print_vec(Y, N);

	printf("sum = %d, average = %d\n", sum, average);



	return 0;
}


void print_vec(int *vec, int size)
{
	for (int j = 0; j < size; j++) {
		printf("%d\t", vec[j]);
	}
	printf("\n");
}
