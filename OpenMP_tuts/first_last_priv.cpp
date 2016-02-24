#include <stdio.h>
#include <iostream>
#include <omp.h>

int main(void)
{
	int i = 10;

#pragma omp parallel private(i)
	{
		printf("thread %d: i = %d\n", omp_get_thread_num(), i);
		i = 1000 + omp_get_thread_num();
	}

	printf("Private i = %d\n", i);


#pragma omp parallel firstprivate(i)
	{
		printf("thread %d: i = %d\n", omp_get_thread_num(), i);
		i = 1000 + omp_get_thread_num();
	}

	printf("First Private i = %d\n", i);


#pragma omp parallel for lastprivate(i)
	for (int j = 0; j < 1;j++)
	{
		printf("thread %d: i = %d\n", omp_get_thread_num(), i);
		i = 1000 + omp_get_thread_num();
	}

	printf("Last Private : i = %d\n", i);

	system("pause");
	return 0;
}