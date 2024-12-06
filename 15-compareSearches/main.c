#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int compareCount = 0; // 비교 횟수를 저장하는 변수

void generateRandomArray(int *array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 범위의 난수 생성
    }
}

// 배열 출력
void printArray(int *array) {
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");

    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
}

// Partition 함수
int partition(int list[], int left, int right) {
    int pivot = list[left]; // 왼쪽 첫 번째 값을 피벗으로 설정
    int low = left + 1;
    int high = right;

    while (1) {
        while (low <= right && list[low] <= pivot) {
            low++;
            compareCount++; // 비교 횟수 증가
        }
        while (high >= left && list[high] > pivot) {
            high--;
            compareCount++; // 비교 횟수 증가
        }
        if (low < high) {
            // low와 high 값 교환
            int temp = list[low];
            list[low] = list[high];
            list[high] = temp;
        } else {
            break;
        }
    }

    // 피벗 값과 high 값을 교환
    int temp = list[left];
    list[left] = list[high];
    list[high] = temp;

    return high; // 최종적으로 피벗이 자리 잡은 위치 반환
}

// 퀵 정렬 함수
void quick_sort(int list[], int left, int right) {
    if (left < right) {
        int pivot = partition(list, left, right); // Partition 수행
        quick_sort(list, left, pivot - 1);       // 왼쪽 부분 정렬
        quick_sort(list, pivot + 1, right);      // 오른쪽 부분 정렬
    }
}

// 퀵 정렬 비교 횟수를 반환하는 함수
void getQuickSortCompareCount(int *array) {
    compareCount = 0; // 비교 횟수 초기화
    quick_sort(array, 0, SIZE - 1); // 퀵 정렬 수행
}

// 순차 탐색 평균 비교 횟수 계산
double getAverageLinearSearchCompareCount(int *array) {
    int totalComparisons = 0;

    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // 항상 배열에 존재하는 값을 선택
        int comparisons = 0;

        for (int j = 0; j < SIZE; j++) {
            comparisons++;
            if (array[j] == target) {
                break;
            }
        }

        totalComparisons += comparisons;
    }

    return (double)totalComparisons / 100.0; // 평균 비교 횟수 반환
}

// 이진 탐색 평균 비교 횟수 계산
double getAverageBinarySearchCompareCount(int *array) {
    int totalComparisons = 0;

    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE];
        int low = 0, high = SIZE - 1, comparisons = 0;

        while (low <= high) {
            comparisons++;
            int middle = (low + high) / 2;

            if (array[middle] == target) {
                break; // 값을 찾으면 탐색 종료
            } else if (array[middle] < target) {
                low = middle + 1; // 오른쪽 부분 탐색
            } else {
                high = middle - 1; // 왼쪽 부분 탐색
            }
        }

        totalComparisons += comparisons;
    }

    return (double)totalComparisons / 100.0;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int array[SIZE];

    generateRandomArray(array);

    printf("Average Linear Search Compare Count: %.2f\n",
           getAverageLinearSearchCompareCount(array));

    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    printf("Average Binary Search Compare Count: %.2f\n",
           getAverageBinarySearchCompareCount(array));

    printArray(array);

    return 0;
}

