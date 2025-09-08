#include <stdio.h>

int main() {
    int unsorted[5] = {40, 80, 20, 10, 7};

    printf("Before sorting...\n");
    for (int i = 0; i < 5; i++) {
        printf("%d, ", unsorted[i]);
    }
    printf("\n");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            if (unsorted[i] > unsorted[i + 1]) {
                int temp = unsorted[i];
                unsorted[i] = unsorted[i+1];
                unsorted[i+1] = temp;
                i = 0;
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
