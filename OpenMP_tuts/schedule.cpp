#include <omp.h>
#include <iostream>
#define CHUNKSIZE 100
#define N     1000

int main()
{
	const int chunk = 10;
	int i;
	float a[N], b[N], c[N];

	/* Some initializations */
	for (i = 0; i < N; i++)
		a[i] = b[i] = i * 1.0;

	int tid = 0;
	int iter = 0;
#pragma omp parallel shared(a,b,c,chunk) private(i,tid,iter)
	{
		tid = omp_get_thread_num();
#pragma omp for schedule(static,chunk) nowait
		for (i = 0; i < N; i++) {
			c[i] = a[i] + b[i];
			iter++;
		}
		std::cout << "Thread " << tid << " ran " << iter << " times\n";
	}  /* end of parallel section */

	
	system("pause");
	return 0;
}