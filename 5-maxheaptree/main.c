#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    struct TreeNode* left, * right;
} TreeNode;

// 새로운 노드 생성 함수
TreeNode* new_node(int key) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

// 레벨별 출력 함수
void print_level_order(TreeNode* root) {
    if (root == NULL) return;

    // 큐를 이용해 레벨별 출력
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    int level = 1; // 트리 레벨 출력용
    printf("트리 레벨별 출력\n");
    while (front < rear) {
        int level_size = rear - front;
        printf("[%d] ", level++);
        for (int i = 0; i < level_size; i++) {
            TreeNode* node = queue[front++];
            printf("%d ", node->key);

            if (node->left != NULL) queue[rear++] = node->left;
            if (node->right != NULL) queue[rear++] = node->right;
        }
        printf("\n");
    }

    free(queue);
}

void print_level_order_as_line(TreeNode* root) {
    if (root == NULL) return;

    // 큐를 이용한 넓이 우선 탐색
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode* node = queue[front++];
        printf("%d ", node->key);

        if (node->left != NULL) queue[rear++] = node->left;
        if (node->right != NULL) queue[rear++] = node->right;
    }
    printf("\n");
    free(queue);
}


// 부모-자식 교환 함수 (값 교환)
void swap(TreeNode* a, TreeNode* b) {
    int temp = a->key;
    a->key = b->key;
    b->key = temp;
}

// 최대 힙 트리에 삽입하는 함수 (노드 이동 횟수 반환)
int insert_max_heap(TreeNode** root, int key) {
    int move_count = 0;

    if (*root == NULL) {
        *root = new_node(key);
        print_level_order_as_line(*root); // 트리 상태를 한 줄로 출력
        return move_count;
    }

    // 힙 삽입을 위한 큐 구현 (넓이 우선 탐색)
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = *root;

    TreeNode* inserted_node = NULL;
    while (front < rear) {
        TreeNode* node = queue[front++];

        // 빈 자리에 노드 삽입
        if (node->left == NULL) {
            node->left = new_node(key);
            inserted_node = node->left;
            break;
        } else {
            queue[rear++] = node->left;
        }

        if (node->right == NULL) {
            node->right = new_node(key);
            inserted_node = node->right;
            break;
        } else {
            queue[rear++] = node->right;
        }
    }

    free(queue);

    // 삽입된 노드에서 부모로 올라가며 최대 힙 성질 유지
    TreeNode* current = inserted_node;
    TreeNode* parent = *root;

    while (current != *root) {
        queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));
        front = rear = 0;
        queue[rear++] = *root;

        while (front < rear) {
            TreeNode* node = queue[front++];
            if (node->left == current || node->right == current) {
                parent = node;
                break;
            }
            if (node->left != NULL) queue[rear++] = node->left;
            if (node->right != NULL) queue[rear++] = node->right;
        }

        free(queue);

        // 부모 노드와 비교, 교체
        if (parent->key < current->key) {
            // 값 교체
            swap(parent, current);

            // 노드가 이동했으므로 이동 횟수 증가
            move_count++;

            // 노드가 이동한 후 상태를 한 줄로 출력
            print_level_order_as_line(*root);
        }

        current = parent; // 부모로 이동
    }

    // 추가된 후 최종 트리 상태를 한 줄로 출력
    print_level_order_as_line(*root);

    return move_count;
}


// 최대 힙 트리에서 삭제 함수 (노드 이동 횟수 반환)
int delete_max_heap(TreeNode** root) {
    if (*root == NULL) return 0; // 빈 트리인 경우

    // 큐를 사용하여 트리의 마지막 노드 찾기
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = *root;

    TreeNode* last_node = NULL;
    TreeNode* parent_of_last = NULL;

    while (front < rear) {
        TreeNode* node = queue[front++];

        if (node->left != NULL) {
            parent_of_last = node;
            queue[rear++] = node->left;
        }
        if (node->right != NULL) {
            parent_of_last = node;
            queue[rear++] = node->right;
        }

        last_node = node;
    }

    free(queue);

    // 마지막 노드를 루트로 이동
    if (last_node == *root) {
        free(*root);  // 트리에 한 개의 노드만 있는 경우
        *root = NULL;
        return 0;
    }

    (*root)->key = last_node->key; // 루트에 마지막 노드의 값을 복사

    // 마지막 노드 삭제
    if (parent_of_last->right == last_node) {
        free(parent_of_last->right);
        parent_of_last->right = NULL;
    } else {
        free(parent_of_last->left);
        parent_of_last->left = NULL;
    }

    // 루트에서 최대 힙 성질을 유지하도록 자식들과 비교하여 교환
    TreeNode* current = *root;
    int move_count = 0;

    while (current->left != NULL) {
        TreeNode* larger_child = current->left;

        if (current->right != NULL && current->right->key > current->left->key) {
            larger_child = current->right;
        }

        if (current->key >= larger_child->key) {
            break;
        }

        // 값 교체
        swap(current, larger_child);

        // 노드가 이동했으므로 이동 횟수 증가
        move_count++;

        // 노드가 이동한 후 상태를 한 줄로 출력
        print_level_order_as_line(*root);

        current = larger_child;
    }

    // 삭제된 후 최종 트리 상태를 한 줄로 출력
    print_level_order_as_line(*root);

    return move_count;
}


// 주어진 배열을 사용해 최대 힙 트리를 생성하는 함수
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        insert_max_heap(&root, inputData[i]);
    }
    return root;
}

// 사용자 인터페이스 함수
void runUserInterface(TreeNode** root) {
    for (;;) { // 무한 루프
        char command;
        int move_count;
        int key;

        printf("------------------------------\n");
        printf("|  i  :  노드 추가           |\n");
        printf("|  d  :  노드 삭제           |\n");
        printf("|  p  :  레벨별 출력         |\n");
        printf("|  c  :  종료               |\n");
        printf("------------------------------\n");

        printf("메뉴 입력: ");
        scanf(" %c", &command);

        switch (command) {
        case 'i': // 노드 추가
            printf("추가할 값 입력: ");
            scanf("%d", &key);
            move_count = insert_max_heap(root, key);
            printf("노드가 이동된 횟수: %d\n", move_count);
            break;

        case 'd': // 노드 삭제
            move_count = delete_max_heap(root);
            printf("노드가 이동된 횟수: %d\n", move_count);
            break;

        case 'p': // 레벨별 출력
            print_level_order(*root);
            break;

        case 'c': // 종료
            return; // 함수 종료로 프로그램을 끝냄

        default:
            printf("잘못된 입력입니다.\n");
        }
    }
}

int main() {
    // 입력 데이터가 없는 상태로 시작
    int inputData[] = {}; // 빈 배열
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 트리 생성 (초기 트리는 비어 있음)
    TreeNode* root = generateMaxHeapTree(inputData, size);

    // 사용자 인터페이스 실행
    runUserInterface(&root);

    // 트리의 모든 노드를 해제 (해제하는 코드 추가 필요)
    return 0;
}

