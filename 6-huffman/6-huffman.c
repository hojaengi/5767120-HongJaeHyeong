#include <stdio.h>
#include <stdlib.h>

// 허프만 트리의 노드 정의
typedef struct Node {
    char character;
    int frequency;
    struct Node *left, *right;
} Node;

// 최소 힙 구조체 정의
typedef struct MinHeap {
    int size;
    int capacity;
    Node** array;
} MinHeap;

// 새 노드 생성 함수
Node* newNode(char character, int frequency) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->character = character;
    temp->frequency = frequency;
    temp->left = temp->right = NULL;
    return temp;
}

// 최소 힙 생성 함수
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node**)malloc(minHeap->capacity * sizeof(Node*));
    return minHeap;
}

// 두 노드를 교환하는 함수
void swapNode(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

// 최소 힙 정렬 함수
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 최소 힙에서 최솟값 추출
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// 최소 힙에 노드 삽입
void insertMinHeap(MinHeap* minHeap, Node* node) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// 현재 힙 상태 출력 함수
void printHeap(MinHeap* minHeap) {
    for (int i = 0; i < minHeap->size; ++i) {
        printf("%d ", minHeap->array[i]->frequency);
    }
    printf("\n");
}

// 최소 힙 생성 (변화 과정 출력 포함)
MinHeap* buildMinHeap(char characters[], int frequencies[], int size) {
    MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i) {
        Node* node = newNode(characters[i], frequencies[i]);
        insertMinHeap(minHeap, node);
        printHeap(minHeap);  // 힙 상태 출력
    }

    return minHeap;
}

// 허프만 트리 구축 및 과정 출력
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    Node *left, *right, *top;
    MinHeap* minHeap = buildMinHeap(characters, frequencies, size);

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        printf("// %d + %d -> %d\n", left->frequency, right->frequency, left->frequency + right->frequency);

        top = newNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
        printHeap(minHeap);  // 힙 상태 출력
    }

    return extractMin(minHeap);
}

// 허프만 코드 출력
void printCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; ++i) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

// 허프만 코드 생성 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int arr[size], top = 0;
    printCodes(root, arr, top);
}

// main 함수
int main() {
    char characters[] = {'a', 'e', 'i', 'o', 'u', 's', 't'};
    int frequencies[] = {10, 15, 12, 3, 4, 13, 1};
    int size = sizeof(characters) / sizeof(characters[0]);

    GenerateHuffmanCodes(characters, frequencies, size);

    return 0;
}

