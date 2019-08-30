// gcc -std=c99 -Wall -lm -fopenmp -o go A1_3.c

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

    unsigned long long start = tick();
    // Gnome sort (dubbed stupid sort)
    int i = 1, j = 2;
    while (i < n)
    {
        if (v[i - 1] < v[i])
        {
            i = j++;
        }
        else
        {
            // swap [i-1] and [i]
            swap(&v[i], &v[i-1]);

            if (--i == 0)
                i = j++;
        }
    }

    // #pragma omp parallel for private(i, j)
    // {
    //     for 
    //     // parallelize this for loop
    //     #pragma omp for
        
    // }
    double time = (double)(tick() - start);
    display(n, v);
    printf("Time: %.2f\n", time);    

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