#include <stdio.h>
#include <stdlib.h>

// 이진 트리 노드 구조체 정의
typedef struct tree_node {
    int data;
    struct tree_node* right;
    struct tree_node* left;
} TreeNode;

// 스레드 이진 트리 노드 구조체 정의
typedef struct thread_node {
    int data;
    struct thread_node* left;
    struct thread_node* right;
    int isThreaded; // 오른쪽 자식이 스레드인지 여부를 표시
} ThreadNode;

// 새로운 이진 트리 노드 생성
TreeNode* new_node(int key) {
    TreeNode* temp = malloc(sizeof(TreeNode));
    temp->data = key;
    temp->right = temp->left = NULL;
    return temp;
}

// 이진 탐색 트리에 노드 추가
TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL) {
        return new_node(key);
    }
    if (key < root->data) {
        root->left = insert_node(root->left, key);
    } else {
        root->right = insert_node(root->right, key);
    }
    return root;
}

// 이진 트리 중위 순회 함수
void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("[%02d] ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

// 스레드 이진 트리 생성
ThreadNode* createThreadNode(int key) {
    ThreadNode* newNode = malloc(sizeof(ThreadNode));
    newNode->data = key;
    newNode->left = newNode->right = NULL;
    newNode->isThreaded = 0;
    return newNode;
}

// 이진 트리를 스레드 이진 트리로 변환
void ConvertToThreadTree(TreeNode* root, ThreadNode** threadRoot, ThreadNode** lastVisited) {
    if (root == NULL) return;

    // 왼쪽 서브트리 방문
    ConvertToThreadTree(root->left, threadRoot, lastVisited);

    // 현재 노드를 스레드 이진 트리로 변환
    ThreadNode* newThreadNode = createThreadNode(root->data);
    if (*lastVisited) {
        (*lastVisited)->right = newThreadNode; // 스레드 설정
        (*lastVisited)->isThreaded = 1; // 현재 노드가 스레드임을 표시
    } else {
        *threadRoot = newThreadNode; // 스레드 이진 트리의 루트 노드 설정
    }
    *lastVisited = newThreadNode;

    // 오른쪽 서브트리 방문
    ConvertToThreadTree(root->right, threadRoot, lastVisited);
}

// 스레드 이진 트리 중위 순회 (반복 방식)
void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;

    // 가장 왼쪽 노드로 이동
    while (current && current->left) {
        current = current->left;
    }

    // 중위 순회
    while (current) {
        printf("[%02d] ", current->data);

        // 스레드가 설정된 경우 오른쪽으로 이동
        if (current->isThreaded) {
            current = current->right;
        } else {
            // 그렇지 않은 경우, 오른쪽 서브트리의 가장 왼쪽 노드로 이동
            current = current->right;
            while (current && current->left) {
                current = current->left;
            }
        }
    }
}

int main(void) {
    int inputData[] = {4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11};
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 이진 탐색 트리 구성
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_node(root, inputData[i]);
    }

    // 이진 트리 중위 순회 출력
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    // 스레드 이진 트리 생성
    ThreadNode* threadRoot = NULL;
    ThreadNode* lastVisited = NULL;
    ConvertToThreadTree(root, &threadRoot, &lastVisited);

    // 스레드 이진 트리 중위 순회 출력
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(threadRoot);
    printf("\n");
    
    free(root);
    free(threadRoot);
    return 0;
}

