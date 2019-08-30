// gcc -std=c99 -Wall -lm -fopenmp A2_5.c -o go 

#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

double mean(int, double *);
double sd(int, double *);
double ttest(int, int, double *, double *);

int main(int argc, char *argv[])
{  
  FILE *fid;
  int nr = 0;
  char buf[255];
  
  // open the file
  fid = fopen(argv[1], "r");

  // count the number of lines
  while (fgets(buf, 255, fid) != NULL)
    nr++;

  // go back to beginning of file
  fseek(fid, 0, SEEK_SET);

  // load in the data
  double c1[nr], c2[nr];
  for (int i = 0; i < nr; i++) {
    fscanf(fid, "%lf,%lf\n", &c1[i], &c2[i]);
  }
  
  // close file
  fclose(fid);

  // print the data to the screen
  for (int i = 0; i < nr; i++)
  {
    printf("c1[%d] = %.0f\tc2[%d] = %.0f\n", i, c1[i], i, c2[i]);
  }

  // compute a t statistic for the difference between means
  double tobs = ttest(nr, nr, c1, c2);
  printf("tobs = %.5f\n", tobs);

  // initialize random seed based on current time
  srand((unsigned) time(NULL));

  // bootstrap the t value
  int nboot = 1e6;
  int tcount = 0;
  double tboot;
  double c1boot[nr], c2boot[nr], allc[nr+nr];
  
  // combine c1 and c2 into allc
  for (int i = 0; i<nr; i++) 
  {
    allc[i]    = c1[i];
    allc[i+nr] = c2[i];
  }
  
  // bootstrap loop
  #pragma omp parallel for private(c1boot,c2boot,tboot) reduction(+: tcount)
  for (int i=0; i<nboot; i++)
  {
    // resample from allc into c1boot and c2boot
    for (int j = 0; j < nr; j++) c1boot[j] = allc[rand()%(nr+nr)];
    for (int j = 0; j < nr; j++) c2boot[j] = allc[rand()%(nr+nr)];
    
    // perform t-test
    tboot = ttest(nr, nr, c1boot, c2boot);
    
    // increment counter
    if (tboot >= tobs) 
      tcount++;
  }

  printf("\n- Total counts: %d (per %d boots)\n- Percent: %.2f\n", tcount, nboot, (double)(tcount * 100.0 / nboot));

  return 0;
}

// helper functions

double mean(int n, double *v)
{
  double sum = 0.0;
  for (int i = 0; i < n; i++)
    sum += v[i];
  return sum / n;
}

double sd(int n, double *v)
{
  double smean = mean(n, v);
  double sum = 0.0;
  for (int i = 0; i < n; i++) 
  {
    sum += (v[i] - smean) * (v[i] - smean);
  }
  return sqrt(sum / (n-1));
}

double ttest(int n1, int n2, double *v1, double *v2)
{
  double sd1 = sd(n1, v1);
  double sd2 = sd(n2, v2);
  double m1 = mean(n1, v1);
  double m2 = mean(n2, v2);
  return (m2-m1) / sqrt(((sd1*sd1)/n1) + ((sd2*sd2)/n2));
}