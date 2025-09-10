#include <stdio.h>

void selection_sort_crude(int[], int);
void selection_sort(int[], int);

int main() {
    int unsorted[] = {4, 9, 11, 2, -1, 23, 1, -5, 101, -89};
    int length = sizeof(unsorted) / sizeof(unsorted[0]);

    printf("Before Sorting: \n");

    for (int i = 0; i < length; i++) {
        printf("%d ", unsorted[i]);
    }

    printf("\n");

    // selection_sort_crude(unsorted, length);
    selection_sort(unsorted, length);

    for (int i = 0; i < length; i++) {
        printf("%d ", unsorted[i]);
    }

    printf("\n");
    return 0;
}

void selection_sort_crude(int unsorted[], int length)
{
    printf("\nCrude Selection sort\n");

    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (unsorted[i] > unsorted[j]) {
                int temp = unsorted[i];
                unsorted[i] = unsorted[j];
                unsorted[j] = temp;
            }
        }
    }
}

void selection_sort(int unsorted[], int length)
{
    printf("\nSelection sort\n");

    for (int i = 0; i < length; i++) {
        int min = i;
        for (int j = i + 1; j < length; j++) {
            if (unsorted[min] > unsorted[j]) {
                min = j;
            }
        }

        if (min != i) {
            int temp = unsorted[i];
            unsorted[i] = unsorted[min];
            unsorted[min] = temp;
        }
    }
}
