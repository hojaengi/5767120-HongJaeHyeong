#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

int compareCount = 0; // 비교 횟수

void generateRandomArray(int *array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000;
    }
}

// 배열 출력
void printArray(int *array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++) {
        printf("%4d ", array[i]);
    }
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%4d ", array[i]);
    }
    printf("\n\n");
}

// Quick Sort
void QuickSort(int *array, int left, int right) {
    if (left >= right) return;
    int pivot = array[left], low = left + 1, high = right;

    while (low <= high) {
        while (low <= right && array[low] <= pivot) low++;
        while (high > left && array[high] >= pivot) high--;
        if (low < high) {
            int temp = array[low];
            array[low] = array[high];
            array[high] = temp;
        }
    }
    array[left] = array[high];
    array[high] = pivot;

    QuickSort(array, left, high - 1);
    QuickSort(array, high + 1, right);
}

// 이진 탐색
int BinarySearch(int *array, int key, int low, int high) {
    while (low <= high) {
        int middle = (low + high) / 2;
        
        compareCount++;
        if (array[middle] == key) {return middle;}

        compareCount++;
        if (array[middle] < key) {low = middle + 1;}
        else {
            high = middle - 1;}
    }
    return -1;
}

// 보간 탐색
int InterpolationSearch(int *array, int key, int low, int high) {
    while (low <= high && key >= array[low] && key <= array[high]) {

        int pos = low + ((double)(key - array[low]) / (array[high] - array[low])) * (high - low);

        compareCount++;
        if (array[pos] == key) {return pos;}

        compareCount++;
        if (array[pos] < key) {low = pos + 1;}

        else {
            high = pos - 1;}
    }
    return -1;
}

// 평균 비교 횟수
double getAverageBinarySearchCompareCount(int *array) {
    int totalCompares = 0;
    for (int i = 0; i < 1000; i++) {
        compareCount = 0;
        int key = array[rand() % SIZE];
        BinarySearch(array, key, 0, SIZE - 1);
        totalCompares += compareCount;
    }
    return (double)totalCompares / 1000;
}

double getAverageInterpolationSearchCompareCount(int *array) {
    int totalCompares = 0;
    for (int i = 0; i < 1000; i++) {
        compareCount = 0;
        int key = array[rand() % SIZE];
        InterpolationSearch(array, key, 0, SIZE - 1);
        totalCompares += compareCount;
    }
    return (double)totalCompares / 1000;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    for (int i = 0; i < 3; i++) {
            printf("", i + 1);

    int array[SIZE];
    generateRandomArray(array);

    QuickSort(array, 0, SIZE - 1);
    printArray(array);

    printf("Average Compare Count of Binary Search: %.2f\n", getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n", getAverageInterpolationSearchCompareCount(array));
    printf("\n");
 }

    return 0;
}

