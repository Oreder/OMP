// gcc -std=c99 -Wall -lm -fopenmp -o go A1_2.c

#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int count = 0;
    // parallelize this chunk of code
    #pragma omp parallel
    {
        // parallelize this for loop
        #pragma omp for
        for (int i = 0; i < 10; ++i)
        {
           printf("%d ", i);
        }
        // printf("\n");
        // count++;
    }
    // printf("\n");
    // count++;
    printf("Total: %d\n", count);

    // omp for
    #pragma omp for
    for (int i = 0; i < 10; ++i)
    {
        printf("%d ", i);
    }
    printf("\n");

    return 0;
}