#include <stdio.h>

void selection_sort_less_complicated(int unsorted[], int length);
void selection_sort(int[], int);

int main() {
    int unsorted[] = {11, 23, 8, 9, 1, 3, 5, 2};
    int length = sizeof(unsorted) / sizeof(unsorted[0]);

    printf("Before sorting: \n");
    for (int i = 0; i < length; i++) {
        printf("%d, ", unsorted[i]);
    }

    printf("\n");
    // selection_sort(unsorted, length);
    selection_sort_less_complicated(unsorted, length);

    printf("After sorting: \n");
    for (int i = 0; i < length; i++) {
        printf("%d, ", unsorted[i]);
    }

    printf("\n");
    return 0;
}

void selection_sort_less_complicated(int unsorted[], int length)
{
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
