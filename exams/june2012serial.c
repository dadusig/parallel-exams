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

	for (i = 0; i < N; i++)
	{
		sum = sum + X[i];
	}

	average = sum/N;

	for (i = 0; i < N; i++)
	{
		X[i] = X[i] - average;
	}

	for (i = 0; i < N; i++)
	{
		Y[i] = Y[i] / average;
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
