#include <stdio.h>
#include <stdlib.h>

#define SIZE_A 256     /* Region A (fits in cache) */
#define SIZE_B 1024     /* Region B (fits in cache) */
#define SIZE_C 2048    /* Region C (fits in cache) */
#define TOTAL_ROUNDS 1500

int regionA[SIZE_A];
int regionB[SIZE_B];
int regionC[SIZE_C];

void access_region(int *arr, int size, int rounds)
{
    int r, i;
    for (r = 0; r < rounds; r++) {
        for (i = 0; i < size; i += 4) {
            arr[i] += 1;
        }
    }
}

int main()
{
    int i, round;

    printf("ARC vs LRU stress test starting...\n");

    /* Initialize arrays */
    for (i = 0; i < SIZE_A; i++) regionA[i] = 0;
    for (i = 0; i < SIZE_B; i++) regionB[i] = 0;
    for (i = 0; i < SIZE_C; i++) regionC[i] = 0;

    /* Mix up access patterns */
    for (round = 0; round < TOTAL_ROUNDS; round++) {
	    if (round % 8 < 3)
    access_region(regionA, SIZE_A, 5);  /* small, frequent */
else if (round % 8 < 6)
    access_region(regionB, SIZE_B, 2);  /* medium reuse */
else
    access_region(regionC, SIZE_C, 1);  /* large, rare */

    }

    printf("Computation done.\n");
    return 0;
}

