#include <stdio.h>

int main() {
    int unsorted[5] = {40, 80, 20, 10, 7};

    printf("Before sorting...\n");
    for (int i = 0; i < 5; i++) {
        printf("%d, ", unsorted[i]);
    }
    printf("\n");

    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (unsorted[i] > unsorted[j]) {
                int temp = unsorted[j];
                unsorted[j] = unsorted[i];
                unsorted[i] = temp;
            }
        }
    }

    printf("After sorting.... \n");
    for (int i = 0; i < 5; i++) {
        printf("%d, ", unsorted[i]);
    }
    printf("\n");
    return 0;
}
