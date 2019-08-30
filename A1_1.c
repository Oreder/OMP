// gcc -std=c99 -Wall -lm -fopenmp -o go A1_1.c

#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int thread_id;
    int glob_nloops, priv_nloops;
    glob_nloops = 0;

    // parallelize this chunk of code
    #pragma omp parallel private(priv_nloops, thread_id)
    {
        priv_nloops = 0;
        thread_id = omp_get_thread_num();

        // parallelize this for loop
        #pragma omp for
        for (int i = 0; i < 10; ++i)
        {
            ++priv_nloops;
            printf("thread(%d): %d\n", thread_id, i);
        }
        printf("\n");

        // make this a "critical" code section
        #pragma omp critical
        {
            //printf("Thread %d is adding its iterations (%d) to sum (%d), ",
            //       thread_id, priv_nloops, glob_nloops);
            glob_nloops += priv_nloops;
            printf(" total nloops is now %d.\n", glob_nloops);
        }
    }
    printf("\nTotal # loop iterations is %d\n",
           glob_nloops);
    return 0;
}