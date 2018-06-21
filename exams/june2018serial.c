#include <stdio.h>
#include <stdlib.h>
void print_vec(long *vec, int size);


#define N 10

int main(int argc, char const *argv[])
{
	int i, j, itime = 20;
	long A[N];

	for (i = 0; i < N; i++)
	{
		A[i] = rand() % 10;
	}

	print_vec(A, N);

	// εδινε τον παρακατω βρόγχο με - ή με +

	for (i = 0; i < itime; i++)
	{
		for (j = 2; j < N; j++)
		{
			A[j] = (A[j-2] + A[j-1] + A[j]) / 1; // δεν παραλληλοποιείται
			// A[j] = (A[j+2] + A[j+1] + A[j]) / 1; // παραλληλοποιειται με ενα δευτερο διανυσμα oldA
		}

		A[0] = 0;
		A[1] = 0;
	}

	print_vec(A, N);


	return 0;
}

void print_vec(long *vec, int size)
{
	for (int j = 0; j < size; j++) {
		printf("%ld\t", vec[j]);
	}
	printf("\n");
}
