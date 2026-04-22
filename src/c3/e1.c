#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
static int binsearch(int x, int v[], int n) {
    int low = 0;
    int mid = 0;
    int high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;

        if (x < v[mid]) {
            high = mid - 1;
        } else if (x > v[mid]) {
            low = mid + 1;
        } else {
            return mid; /* found match */
        }
    }

    return -1; /* no match */
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
static int optimal_binsearch(int x, int v[], int n) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (v[mid] >= x) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return (low < n && v[low] == x) ? v[low] : -1;
}

static double run_benchmark(int (*search)(int, int[], int), int iterations,
                            int v[], int n) {
    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        search(i % n, v, n);
    }
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Our binary search makes two tests inside the loop, when one would suffice (at
// the price of more tests outside). Write a version with only one test inside
// the loop and measure the difference in run-time.
int main(void) {
    constexpr int N = 1000000;

    static int v[N];
    for (int i = 0; i < N; i++) {
        v[i] = i;
    }

    printf("original: %f\n", run_benchmark(binsearch, N, v, N));
    printf("one test: %f\n", run_benchmark(optimal_binsearch, N, v, N));

    return EXIT_SUCCESS;
}
