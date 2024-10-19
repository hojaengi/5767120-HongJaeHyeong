#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// 생성 함수
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// 초기화 함수
void init(HeapType* h) {
    h->heap_size = 0;
}

// 요소 교환 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 힙 재정렬 함수 (최대 힙 특성 유지)
void resortHeap(int inputData[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && inputData[left] > inputData[largest])
        largest = left;
    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        resortHeap(inputData, n, largest);
    }
}

// 최대 힙 구축 및 삽입 과정 출력 함수
void BuildMaxHeap(int inputData[], int n) {
    for (int i = 1; i <= n; i++) {
        // 현재 배열 상태 출력 (i번째까지의 힙 구성)
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");

        // 현재까지의 힙 재정렬
        for (int k = i / 2 - 1; k >= 0; k--) {
            resortHeap(inputData, i, k);
        }
    }
}

// 힙 정렬 수행 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    // 최대 힙 생성 (과정 출력 포함)
    BuildMaxHeap(inputData, n);

    // 힙 정렬 과정 출력
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);  // 최대값을 배열 끝으로 이동
        resortHeap(inputData, i, 0);         // 남은 힙 재정렬

        // 힙 재정렬 후 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main(void) {
    int inputData[] = {34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86};
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 힙 정렬 실행
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // 정렬된 결과 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}

