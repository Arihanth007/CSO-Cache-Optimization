#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define cache_size 32768
#define max_size 3500

/* 
This code takes approximatly 5min to run on device with following config-
     *-memory
          description: System memory
          physical id: 0
          size: 8GiB
     *-cpu
          product: Intel(R) Core(TM) i5-7200U CPU @ 2.50GHz
          vendor: Intel Corp.
          physical id: 1
          bus info: cpu@0
          size: 3005MHz
          capacity: 3100MHz
          width: 64 bits
*/

int min(int a, int b)
{
  return (a < b ? a : b);
}

// int A[3500][3500], B[3500][3500], M[3500][3500];
int A[3500][3500], B[3500][3500], M[3500][3500], N[3500][3500];

int rand(void);
int main()
{
  int k, sum = 0, isPrint = 0;
  time_t t;
  clock_t start, end;
  double time_taken;

  /* Intializes random number generator */
  srand((unsigned)time(&t));

  FILE *in_file = fopen("2_input.txt", "r"); // read only
  if (in_file == NULL)
  {
    printf("Error! Could not open file\n");
    exit(-1); // must include stdlib.h
  }

  int bsize = cache_size / sizeof(int), i, j;

  // printf("Enter number of rows and columns of first matrix\n");
  // int m = max_size, n = max_size;
  int m, n, p;
  fscanf(in_file, "%d %d %d", &m, &n, &p);
  int q = n;

  printf("First matrix initialized\n");
  printf("A[%d][%d]\n", m, n);

  // printf("Enter elements of first matrix\n");
  int c, d;
  for (c = 0; c < m; c++)
  {
    for (i = 0; i < n; i += bsize)
    {
      for (d = i; d < min(i + bsize, n); d++)
      {
        // A[c][d] = (rand() % 600);
        fscanf(in_file, "%d", &A[c][d]);
      }
    }
  }

  // printf("Enter number of rows and columns of second matrix\n");
  // int p = max_size, q = max_size;

  // if (n != p)
  if (0)
    printf("The multiplication isn't possible.\n");
  else
  {
    printf("Second matrix initialized\n");
    printf("B[%d][%d]\n", n, p);
    for (c = 0; c < n; c++)
    {
      for (i = 0; i < p; i += bsize)
      {
        for (d = i; d < min(i + bsize, p); d++)
        {
          // B[c][d] = (rand() % 600);
          fscanf(in_file, "%d", &B[c][d]);
        }
      }
    }

    if (isPrint)
    {
      start = clock();
      for (c = 0; c < m; c++)
      {
        for (d = 0; d < p; d++)
        {
          for (k = 0; k < n; k++)
            sum = sum + A[c][k] * B[k][d];

          N[c][d] = sum;
          sum = 0;
        }
      }
      end = clock();
      time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Time taken for NON opt code = %f\n", time_taken);
    }

    // optimized
    // start = clock();
    // int i, j, jj, kk, bsize = cache_size / sizeof(int);
    // for (jj = 0; jj < n; jj += bsize)
    // { // for each bsize block
    //   for (i = 0; i < m; i++)
    //     for (j = jj; j < min(jj + bsize, q); j++)
    //       M[i][j] = 0;
    //   for (kk = 0; kk < n; kk += bsize)
    //   {
    //     for (i = 0; i < m; i++)
    //     { // for each row of A
    //       // for each column of the block of B
    //       for (j = jj; j < min(jj + bsize, p); j++)
    //       {
    //         sum = 0;
    //         // For each element of the sliver of A/column of B
    //         for (k = kk; k < min(kk + bsize, n); k++)
    //           sum += A[i][k] * B[k][j];

    //         M[i][j] += sum;
    //       }
    //     }
    //   }
    // }
    // end = clock();
    // time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time taken for opt code = %f\n", time_taken);

    start = clock();

    int ih, jh, kh, il, jl, kl, s = 32;
    for (ih = 0; ih < m; ih += s)
    {
      for (jh = 0; jh < p; jh += s)
      {
        M[ih][jh] = 0;
        for (kh = 0; kh < n; kh += s)
          for (il = 0; il < s; il++)
            for (kl = 0; kl < s; kl++)
              for (jl = 0; jl < s; jl++)
                M[ih + il][jh + jl] += A[ih + il][kh + kl] * B[kh + kl][jh + jl];
      }
    }
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for opt code = %f\n", time_taken);

    printf("Computed the product\n");

    if (isPrint)
    {
      int isEqual = 1;
      for (i = 0; i < m; i++)
        for (j = 0; j < p; j++)
          if (M[i][j] != N[i][j])
            isEqual = 0;

      printf("%d\n", isEqual);
    }

    FILE *out_file = fopen("2_output.txt", "w"); // write only
    if (out_file == NULL)
    {
      printf("Error! Could not open file\n");
      exit(-1); // must include stdlib.h
    }
    for (c = 0; c < m; c++)
    {
      for (d = 0; d < p; d++)
      {
        printf("%d\t", M[c][d]);
        fprintf(out_file, "%d\t", M[c][d]);
      }
      printf("\n");
      fprintf(out_file, "\n");
    }

    fclose(out_file);
  }

  fclose(in_file);
  return 0;
}