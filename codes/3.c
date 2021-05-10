/* C program for Merge Sort */
/*Instructions:

This code takes approximatly 3 secs to run on device with following config-
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define cache_size 32768
#define max_size 6000000

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
int arr[max_size + 5], tim[max_size + 5], arr_iter[max_size + 5], L[max_size + 5], R[max_size + 5], cnt = 0;

int min(int a, int b)
{
    return (a < b ? a : b);
}

void merge3(int gArray[], int low, int mid1,
            int mid2, int high, int destArray[])
{
    int i = low, j = mid1, k = mid2, l = low;

    while ((i < mid1) && (j < mid2) && (k < high))
    {
        if (gArray[i] < gArray[j])
        {
            if (gArray[i] < gArray[k])
            {
                destArray[l++] = gArray[i++];
            }
            else
            {
                destArray[l++] = gArray[k++];
            }
        }
        else
        {
            if (gArray[j] < gArray[k])
            {
                destArray[l++] = gArray[j++];
            }
            else
            {
                destArray[l++] = gArray[k++];
            }
        }
    }

    while ((i < mid1) && (j < mid2))
    {
        if (gArray[i] < gArray[j])
        {
            destArray[l++] = gArray[i++];
        }
        else
        {
            destArray[l++] = gArray[j++];
        }
    }

    while ((j < mid2) && (k < high))
    {
        if (gArray[j] < gArray[k])
        {
            destArray[l++] = gArray[j++];
        }
        else
        {
            destArray[l++] = gArray[k++];
        }
    }

    while ((i < mid1) && (k < high))
    {
        if (gArray[i] < gArray[k])
        {
            destArray[l++] = gArray[i++];
        }
        else
        {
            destArray[l++] = gArray[k++];
        }
    }

    while (i < mid1)
        destArray[l++] = gArray[i++];

    while (j < mid2)
        destArray[l++] = gArray[j++];

    while (k < high)
        destArray[l++] = gArray[k++];
}

void mergeSort3WayRec(int gArray[], int low,
                      int high, int destArray[])
{
    // cnt++;
    if (high - low < 2)
        return;

    int mid1 = low + ((high - low) / 3);
    int mid2 = low + 2 * ((high - low) / 3) + 1;

    mergeSort3WayRec(destArray, low, mid1, gArray);
    mergeSort3WayRec(destArray, mid1, mid2, gArray);
    mergeSort3WayRec(destArray, mid2, high, gArray);

    merge3(destArray, low, mid1, mid2, high, gArray);
}

void mergeSort3Way(int gArray[], int n)
{
    if (n == 0)
        return;

    int fArray[n], i;

    for (i = 0; i < n; i++)
        fArray[i] = gArray[i];

    mergeSort3WayRec(fArray, 0, n, gArray);

    for (i = 0; i < n; i++)
        gArray[i] = fArray[i];
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1, n2 = r - m, bsize = cache_size / sizeof(int), i, j, k;

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    // cnt++;
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void mergeSort2(int arr[], int n)
{
    int curr_size;
    int left_start;

    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
    {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
        {
            // cnt++;
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);

            // printf("curr_size: %d, left_start: %d, mid: %d, right_end: %d\n", curr_size, left_start, mid, right_end);
            merge(arr, left_start, mid, right_end);
        }
    }
}

// This function sorts array from left index to
// to right index which is of size atmost RUN
void insertionSort(int arr[], int left, int right)
{
    int i;
    for (i = left + 1; i <= right; i++)
    {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Iterative Timsort function to sort the
// array[0...n-1] (similar to merge sort)
void timSort(int arr[], int n)
{
    // int RUN = cache_size / sizeof(int);
    int RUN = 32, i, size, left;

    // Sort individual subarrays of size RUN
    for (i = 0; i < n; i += RUN)
        insertionSort(arr, i, min((i + RUN - 1), (n - 1)));

    for (size = RUN; size < n; size = 2 * size)
    {
        for (left = 0; left < n; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1),
                            (n - 1));

            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int rand(void);

/* Driver code */
int main()
{
    time_t t;
    clock_t start, end;
    double time_taken;

    /* Intializes random number generator */
    srand((unsigned)time(&t));
    // int arr_size = max_size;
    int arr_size;

    FILE *in_file = fopen("3_input.txt", "r"); // read only
    if (in_file == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1); // must include stdlib.h
    }
    fscanf(in_file, "%d", &arr_size);
    printf("Array of size %d is going to be sorted\n", arr_size);
    // arr_size = 2000000;

    int bsize = cache_size / sizeof(int), i, j;
    for (j = 0; j < arr_size; j += bsize)
        for (i = j; i < min(j + bsize, arr_size); i++)
        {
            fscanf(in_file, "%d", &arr[i]);
            // fscanf(in_file, "%d", &tim[i]);
            // tim[i] = (rand() % 10000000);
            // arr[i] = (rand() % 10000000);
            // tim[i] = arr[i];
            // arr[i] = tim[i];
            // arr_iter[i] = arr[i];
        }

    fclose(in_file);

    // start = clock();
    // mergeSort(arr, 0, arr_size - 1);
    // end = clock();
    // time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time taken for recursive code = %f\n", time_taken);

    // start = clock();
    // mergeSort2(arr_iter, arr_size);
    // end = clock();
    // time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time taken for iterative code = %f\n", time_taken);

    // start = clock();
    // timSort(tim, arr_size);
    // end = clock();
    // time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time taken for tim sort = %f\n", time_taken);

    start = clock();
    mergeSort3Way(arr, arr_size);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for 3-way code = %f\n", time_taken);

    // printf("Total iterations = %d\n", cnt);

    // int isEqual = 1;
    // for (int i = 0; i < arr_size; i++)
    //     if (arr[i] != tim[i])
    //         isEqual = 0;
    // printf("\nArray is sorted, result: %d\n", isEqual);

    // printArray(tim, arr_size);
    // printArray(arr, arr_size);

    FILE *out_file = fopen("3_output.txt", "w"); // write only
    if (out_file == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1); // must include stdlib.h
    }
    for (i = 0; i < arr_size; i++)
    {
        fprintf(out_file, "%d\t", tim[i]);
    }
    fclose(out_file);

    return 0;
}