#include <stdio.h>

#define SIZE (1024 * 1024)  /* 1 MB array */

int main() {
    static int arr[SIZE];
    long long sum = 0;
    int i;  /* declare loop variable at the top */

    /* Sequential access (LRU friendly) */
    for (i = 0; i < SIZE; i += 16) {
        sum += arr[i];
    }

    /* Random access pattern (LFU might perform better) */
    for (i = 0; i < SIZE; i += 128) {
        sum += arr[(i * 37) % SIZE];
    }

    printf("Sum: %lld\n", sum);
    return 0;
}

