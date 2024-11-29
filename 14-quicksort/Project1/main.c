#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 // 배열 크기 정의

// 전역 변수
int comparisonCount = 0; // 비교 횟수
int moveCount = 0;       // 이동 횟수
int rounds = 0;
int isFirst = 0;         

// 랜덤 배열 생성 함수
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// 배열 출력 함수
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Quick Sort의 partition 함수
int partition(int array[], int low, int high) {
    int pivot = array[high]; // 마지막 요소를 피벗으로 설정
    moveCount++;             // temp에 pivot 값을 저장 (array[high] → pivot)

    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisonCount++;
        if (array[j] <= pivot) {
            i++;

            // 이동 횟수 계산: temp로 값을 저장하고 읽어오는 모든 작업 포함
            int temp = array[i]; // temp에 array[i] 값 저장
            moveCount++;         // temp에 값 저장
            array[i] = array[j]; // array[i]에 array[j] 값 저장
            moveCount++;         // array[i]에 값 저장
            array[j] = temp;     // array[j]에 temp 값 저장
            moveCount++;         // array[j]에 temp 값 저장
        }
    }

    // 마지막으로 pivot과 교환
    int temp = array[i + 1]; // temp에 array[i+1] 값 저장
    moveCount++;             // temp에 값 저장
    array[i + 1] = array[high]; // array[i+1]에 pivot 값 저장
    moveCount++;             // array[i+1]에 값 저장
    array[high] = temp;      // pivot 위치로 이동
    moveCount++;             // array[high]에 temp 값 저장

    return i + 1;
}

// Quick Sort 재귀 함수
void doQuickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        // 정렬 과정 출력 (40~60번째 값만 출력)
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n\n");
        }
        rounds++; // rounds 값 증가

        doQuickSort(array, low, pi - 1);  // 왼쪽 부분 배열 정렬
        doQuickSort(array, pi + 1, high); // 오른쪽 부분 배열 정렬
    }
}

// main 함수
int main(int argc, char *argv[]) {
    srand(time(NULL));
    int array[SIZE];
    int totalComparisons = 0;
    int totalMoveCount = 0;

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        } else {
            doQuickSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}

