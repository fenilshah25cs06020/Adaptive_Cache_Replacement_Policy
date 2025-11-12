#include <stdio.h>
#include <stdlib.h>

#define N 65536

int main() {
    int i, k;
    int *arr = malloc(sizeof(int) * N);

    /* Phase 1: sequential scan (recency) */
    for (i = 0; i < N; i++)
        arr[i]++;

    /* Phase 2: repeatedly touch small set (frequency) */
    for (k = 0; k < 100000; k++)
        arr[k % 64]++;

    /* Phase 3: random accesses (mixed) */
    for (k = 0; k < 500000; k++)
        arr[rand() % N]++;

    printf("Done.\n");
    free(arr);
    return 0;
}

