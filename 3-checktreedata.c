#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

// 트리 노드 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 스택 구조체 정의
typedef struct {
    TreeNode* stack[MAX_STACK_SIZE];
    int top;
} Stack;

// 큐 구조체 정의 (레벨별 순회를 위해 사용)
typedef struct QueueNode {
    TreeNode* node;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// 스택 초기화
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비어있는지 확인
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택에 노드 추가
void push(Stack* s, TreeNode* node) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->stack[++(s->top)] = node;
    }
}

// 스택에서 노드 꺼내기
TreeNode* pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->stack[(s->top)--];
    }
    return NULL;
}

// 큐 초기화
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// 큐가 비어있는지 확인
int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

// 큐에 노드 추가
void enqueue(Queue* q, TreeNode* node) {
    QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
    newQueueNode->node = node;
    newQueueNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newQueueNode;
    } else {
        q->rear->next = newQueueNode;
        q->rear = newQueueNode;
    }
}

// 큐에서 노드 제거
TreeNode* dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        return NULL;
    }
    
    QueueNode* temp = q->front;
    TreeNode* node = temp->node;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return node;
}

// 노드 생성 함수
TreeNode* createNode(int data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 노드를 적절한 위치에 배치하는 함수
void PlaceNode(TreeNode *node, int direction, int data) {
    TreeNode *newNode = createNode(data);
    if (direction == 0) {  // 왼쪽
        node->left = newNode;
    } else {  // 오른쪽
        node->right = newNode;
    }
}

// 트리 높이를 계산하는 반복적 함수 (레벨별 순회 방식)
int getHeightOfTree(TreeNode *root) {
    if (root == NULL) return 0;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    int height = 0;

    while (!isQueueEmpty(&q)) {
        int levelSize = 0;
        QueueNode* temp = q.front;
        // 현재 레벨에 있는 노드의 수를 센다.
        while (temp != NULL) {
            levelSize++;
            temp = temp->next;
        }

        // 레벨에 있는 모든 노드를 처리한다.
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = dequeue(&q);
            if (node->left != NULL) {
                enqueue(&q, node->left);
            }
            if (node->right != NULL) {
                enqueue(&q, node->right);
            }
        }
        height++;
    }

    return height;
}

// 트리의 모든 노드의 합계를 계산하는 반복적 함수
int getSumOfNodes(TreeNode *root) {
    if (root == NULL) return 0;
    
    Stack s;
    initStack(&s);
    push(&s, root);

    int sum = 0;
    
    while (!isEmpty(&s)) {
        TreeNode *node = pop(&s);
        sum += node->data;
        
        if (node->right) push(&s, node->right);
        if (node->left) push(&s, node->left);
    }

    return sum;
}

// 트리의 노드 개수를 계산하는 반복적 함수
int getNumberOfNodes(TreeNode *root) {
    if (root == NULL) return 0;

    Stack s;
    initStack(&s);
    push(&s, root);

    int count = 0;

    while (!isEmpty(&s)) {
        TreeNode *node = pop(&s);
        count++;
        
        if (node->right) push(&s, node->right);
        if (node->left) push(&s, node->left);
    }

    return count;
}

// 리프 노드 개수를 계산하는 반복적 함수
int getNumberOfLeafNodes(TreeNode *root) {
    if (root == NULL) return 0;

    Stack s;
    initStack(&s);
    push(&s, root);

    int leafCount = 0;

    while (!isEmpty(&s)) {
        TreeNode *node = pop(&s);
        
        if (node->left == NULL && node->right == NULL) {
            leafCount++;
        }
        
        if (node->right) push(&s, node->right);
        if (node->left) push(&s, node->left);
    }

    return leafCount;
}

// 트리를 생성하는 함수 (PlaceNode를 사용하여 재구성)
void GenerateLinkTree(TreeNode *root) {
    // 트리 구조 생성
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

int main() {
    // 트리 생성 및 루트 데이터 설정
    TreeNode *root = createNode(1);  // root->data = 1 설정
    GenerateLinkTree(root);

    // 출력
    printf("Sum of nodes: %d\n", getSumOfNodes(root));
    printf("Number of nodes: %d\n", getNumberOfNodes(root));
    printf("Height of Tree: %d\n", getHeightOfTree(root));
    printf("Number of leaf nodes: %d\n", getNumberOfLeafNodes(root));
    
    return 0;
}
