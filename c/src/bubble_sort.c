#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "helper.h"

void bubble_sort(int[], int);
void selection_sort(int*, int);
int is_sorted(int[], int, int);

int main() {
    struct timeval start;
    struct timeval end;
    float elapsed;

    int length = 1000;
    printf("Enter the length of the array: \n");
    scanf("%d", &length);

    calculate_memory_usage(length);
    int *data = fill_unique_random_data_hashset(length);

    if (data == NULL) {
        return 1;
    }

    calculate_memory_usage(length);
    gettimeofday(&start, 0);
    selection_sort(data, length);
    gettimeofday(&end, 0);

    elapsed = time_diff(start, end);
    printf("\nTime taken to sort %d numbers using bubble sort is: %f msec\n", length, elapsed);
    free(data);
    return 0;
}

void selection_sort(int *data, int length)
{
    for (int i = 0; i < length; i++) {
        int min = i;
        for (int j = i + 1; j < length; j++) {
            if (data[min] > data[j]) {
                min = j;
            }
        }

        if (min != i) {
            int temp = data[i];
            data[i] = data[min];
            data[min] = temp;
        }
    }
}

