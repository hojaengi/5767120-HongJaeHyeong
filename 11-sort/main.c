#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

#define SIZE 100

void generateRandomData(int randomData[]) {
    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % 1000; // 0 ~ 999 범위의 랜덤 값
    }
}

void doSelectionSort(int data[]) {
    int selectionData[SIZE];
    for (int i = 0; i < SIZE; i++) {
        selectionData[i] = data[i]; // 원본 데이터 복사
    }
    printf("Selection Sort:\n");
    selection_sort(selectionData, SIZE);
}

void doInsertionSort(int data[]) {
    int insertionData[SIZE];
    for (int i = 0; i < SIZE; i++) {
        insertionData[i] = data[i]; // 원본 데이터 복사
    }
    printf("\nInsertion Sort:\n");
    insertion_sort(insertionData, SIZE);
    printf("Insertion Sort Result: ");
    print_list(insertionData, SIZE);
}

void doBubbleSort(int data[]) {
    int bubbleData[SIZE];
    for (int i = 0; i < SIZE; i++) {
        bubbleData[i] = data[i]; // 원본 데이터 복사
    }
    printf("\nBubble Sort:\n");
    bubble_sort(bubbleData, SIZE);
    printf("Bubble Sort Result: ");
    print_list(bubbleData, SIZE);
}

int main() {
    int randomData[SIZE];
    generateRandomData(randomData);

    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}

