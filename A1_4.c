// gcc -std=c99 -Wall -lm -fopenmp -o go A1_4.c

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

void display(int, int *);
void swap(int *, int *);

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__("rdtsc": "=A"(d));
    return d;
}

int main(int argc, char *argv[])
{
    int n = 10;
    int* v = (int *)malloc(n);

    // initialize random seed based on current time
    srand((unsigned) time(NULL));
    for (int i = 0; i < n; ++i)
    {
        v[i] = rand() % 20; //RAND_MAX;
    }
    display(n, v);

    printf("\n ==== OPENMP ====\n");

    unsigned long long start = tick();
    #pragma omp for
    for (int i = n - 1; i > 0; --i)
    {
        int imax = i;

        // parallelize this for loop
        #pragma omp critical
        for (int j = 0; j < i; ++j)
        {
            if (*(v + j) > *(v + imax))
                imax = j;
        }
        
        if (imax != i)
            swap(v + imax, v + i);
    }

    double t_omp = (double)(tick() - start);
    display(n, v);
    printf("Time-openmp: %.2f\n", t_omp);    

    free(v);
    return 0;
}

void display(int n, int *v)
{
    for (int i = 0; i < n; ++i)
        printf("%d\t", v[i]);
    printf("\n");
}

void swap(int *x, int *y)
{
    int z = *x;
    *x = *y;
    *y = z;
}