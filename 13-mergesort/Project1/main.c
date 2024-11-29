#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// 전역 변수
int comparisonCount = 0; // 비교 횟수
int moveCount = 0;       // 이동 횟수
int rounds = 0;          // 출력 조건을 위한 변수
int temp[SIZE];          // 병합 정렬에 사용할 임시 배열
int isFirst = 0;         // 첫 번째 출력 여부를 판단
int totalComparisons = 0; // 총 비교 횟수
int totalMoves = 0;       // 총 이동 횟수

// 배열 병합 함수
void merge(int array[], int left, int mid, int right) {
    int i = left;       // 왼쪽 부분 배열 인덱스
    int j = mid + 1;    // 오른쪽 부분 배열 인덱스
    int k = left;       // 병합 결과 배열 인덱스

    // 두 부분 배열을 병합
    while (i <= mid && j <= right) {
        comparisonCount++; // 비교 횟수 증가
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
            moveCount++; // 이동 횟수 증가
        } else {
            temp[k++] = array[j++];
            moveCount++; // 이동 횟수 증가
        }
    }

    // 왼쪽 배열의 남은 요소 복사
    while (i <= mid) {
        temp[k++] = array[i++];
        moveCount++; // 이동 횟수 증가
    }

    // 오른쪽 배열의 남은 요소 복사
    while (j <= right) {
        temp[k++] = array[j++];
        moveCount++; // 이동 횟수 증가
    }

    // temp 배열의 값을 원래 배열로 복사
    for (i = left; i <= right; i++) {
        array[i] = temp[i];
        moveCount++; // 이동 횟수 증가
    }

    // 정렬 과정 출력 조건 (10번째마다)
    if (rounds % 10 == 0 && isFirst == 0) {
        // 배열 처음부터 10번째까지 출력
        for (int i = 0; i < 10; i++) {
            printf("%3d ", array[i]);
        }
        printf("| ");

        // 중앙값 기준 중앙-1 ~ 중앙+10 위치 출력
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) {
            printf("%3d ", array[i]);
        }
        printf("\n\n");
    }
    rounds++;
}

// 병합 정렬 재귀 함수
void doMergeSort(int array[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        // 왼쪽 부분 배열 정렬
        doMergeSort(array, left, mid);

        // 오른쪽 부분 배열 정렬
        doMergeSort(array, mid + 1, right);

        // 두 부분 배열 병합
        merge(array, left, mid, right);
    }
}

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

// main 함수
int main() {
    int array[SIZE];

    srand(time(0));

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array, 0, SIZE - 1);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        } else {
            doMergeSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}

