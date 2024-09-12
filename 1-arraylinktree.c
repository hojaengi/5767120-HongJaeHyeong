#include <stdio.h>
#include <stdlib.h>

// TreeNode 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 배열을 이용한 트리 생성 함수
void GenerateArrayTree(int *tree) {
    // 트리 순서에 맞는 수 입력
    int list[] = {1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15};

    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }

    // 생성된 트리 출력
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n");
}

// 배열을 이용한 전위 순회
void ArrayPreOrder(int *tree, int index, int size) {
    if (index >= size || tree[index] == 0) return;
    printf("%d ", tree[index]);        // 현재 노드 출력
    ArrayPreOrder(tree, 2 * index + 1, size); // 왼쪽 자식
    ArrayPreOrder(tree, 2 * index + 2, size); // 오른쪽 자식
}

// 배열을 이용한 중위 순회
void ArrayInOrder(int *tree, int index, int size) {
    if (index >= size || tree[index] == 0) return;
    ArrayInOrder(tree, 2 * index + 1, size);  // 왼쪽 자식
    printf("%d ", tree[index]);               // 현재 노드 출력
    ArrayInOrder(tree, 2 * index + 2, size);  // 오른쪽 자식
}

// 배열을 이용한 후위 순회
void ArrayPostOrder(int *tree, int index, int size) {
    if (index >= size || tree[index] == 0) return;
    ArrayPostOrder(tree, 2 * index + 1, size); // 왼쪽 자식
    ArrayPostOrder(tree, 2 * index + 2, size); // 오른쪽 자식
    printf("%d ", tree[index]);                // 현재 노드 출력
}

// 배열 트리 순회
void ArrayOrders(int *tree, int size) {
    printf("Array PreOrder: ");
    ArrayPreOrder(tree, 0, size);
    printf("\n");

    printf("Array InOrder: ");
    ArrayInOrder(tree, 0, size);
    printf("\n");

    printf("Array PostOrder: ");
    ArrayPostOrder(tree, 0, size);
    printf("\n");
}

// 노드를 주어진 방향에 따라 배치하는 함수 (0:left, 1:right)
void PlaceNode(TreeNode *node, int direction, int data) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode;
    } else {
        node->right = newNode;
    }
}

// 링크드 리스트 방식 트리 생성
void GenerateLinkTree(TreeNode *root) {
    root->data = 1;
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);

    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);

    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);

    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);

    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);

    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);

    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

// 링크드 리스트 전위 순회
void LinkPreOrder(TreeNode *node) {
    if (node == NULL) return;
    printf("%d ", node->data);    // 현재 노드 출력
    LinkPreOrder(node->left);     // 왼쪽 자식
    LinkPreOrder(node->right);    // 오른쪽 자식
}

// 링크드 리스트 중위 순회
void LinkInOrder(TreeNode *node) {
    if (node == NULL) return;
    LinkInOrder(node->left);      // 왼쪽 자식
    printf("%d ", node->data);    // 현재 노드 출력
    LinkInOrder(node->right);     // 오른쪽 자식
}

// 링크드 리스트 후위 순회
void LinkPostOrder(TreeNode *node) {
    if (node == NULL) return;
    LinkPostOrder(node->left);    // 왼쪽 자식
    LinkPostOrder(node->right);   // 오른쪽 자식
    printf("%d ", node->data);    // 현재 노드 출력
}

// 링크드 리스트 트리 순회
void LinkOrders(TreeNode *root) {
    printf("Link PreOrder: ");
    LinkPreOrder(root);
    printf("\n");

    printf("Link InOrder: ");
    LinkInOrder(root);
    printf("\n");

    printf("Link PostOrder: ");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    int arr[15];  // 배열 트리
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));  // 링크드 리스트 트리 root 생성

    // 각각의 방식(array법, link법)에 따른 트리 생성
    GenerateArrayTree(arr);
    GenerateLinkTree(root);

    // 각 생성한 트리를 순회
    ArrayOrders(arr, 15);
    LinkOrders(root);

    return 0;
}
