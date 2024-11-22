#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%03d ", list[i]);
    }
    printf("\n");
}

void selection_sort(int list[], int n) {
    int i, j, least, temp, compareCount = 0;

    for (i = 0; i < n - 1; i++) {
        least = i;
        for (j = i + 1; j < n; j++) {
            compareCount++;
            if (list[least] > list[j]) {
                least = j;
            }
        }
        SWAP(list[i], list[least], temp);

        // 특정 단계 출력 (10, 30, 50, 70, 90, 마지막 단계)
        if ((i + 1) % 20 == 10 || i == 29 || i == 49 || i == 69 || i == 89 || i == n - 2) {
            printf("Step %02d: ", i + 1);
            print_list(list, n);
        }
    }
}

void insertion_sort(int list[], int n) {
    int i, j, key, compareCount = 0;

    for (i = 1; i < n; i++) {
        key = list[i];
        for (j = i - 1; j >= 0; j--) {
            compareCount++;
            if (list[j] > key) {
                list[j + 1] = list[j];
            } else {
                break;
            }
        }
        list[j + 1] = key;
    }
    printf("Insertion Sort Compare Average: %d\n", compareCount);
}

void bubble_sort(int list[], int n) {
    int i, j, temp, flag, compareCount = 0;

    for (i = 0; i < n - 1; i++) {
        flag = 0;
        for (j = 0; j < n - 1 - i; j++) {
            compareCount++;
            if (list[j] > list[j + 1]) {
                SWAP(list[j], list[j + 1], temp);
                flag = 1;
            }
        }
        if (flag == 0) break;
    }
    printf("Bubble Sort Compare Average: %d\n", compareCount);
}

