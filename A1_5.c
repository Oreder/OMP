// gcc -std=c99 -Wall -lm -fopenmp -o go A1_5.c

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

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
    int* v1 = (int *)malloc(n);
    int* v2 = (int *)malloc(n);

    for (int i = 0; i < n; ++i)
    {
        v1[i] = rand() % 25; //RAND_MAX;
        v2[i] = v1[i];
    }
    display(n, v1);
    display(n, v2);

    // unsigned long long start = tick();

    // for (int i = n - 1; i > 0; --i)
    // {
    //     int imax = i;
    //     for (int j = 0; j < i; ++j)
    //     {
    //         if (*(v1 + j) > *(v1 + imax))
    //             imax = j;
    //     }
        
    //     if (imax != i)
    //         swap(v1 + imax, v1 + i);
    // }
    // double t_org = (double)(clock() - start);
    
    // #pragma omp for
    // for (int i = n - 1; i > 0; --i)
    // {
    //     int imax = i;

    //     // parallelize this for loop
    //     #pragma omp critical
    //     for (int j = 0; j < i; ++j)
    //     {
    //         if (*(v2 + j) > *(v2 + imax))
    //             imax = j;
    //     }
        
    //     if (imax != i)
    //         swap(v2 + imax, v2 + i);
    // }

    // double t_omp = (double)(clock() - start - t_org);
    
    // printf("\n ==== ORIGIN ====\n");
    // display(n, v1);

    // printf("\n ==== OPENMP ====\n");
    // display(n, v2);

    // printf("Time-origin: %.2f\nTime-openmp: %.2f\n", t_org, t_omp);

    free(v1);
    free(v2);
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