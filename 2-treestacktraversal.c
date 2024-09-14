#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체 정의
typedef struct TreeNode {
  int data;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

// 스택을 위한 구조체 정의
typedef struct Stack {
  TreeNode *nodes[100]; // 스택 크기 가정
  int top;
} Stack;

// 스택 초기화 함수
void initStack(Stack *s) { s->top = -1; }

// 스택이 비었는지 확인
int isEmpty(Stack *s) { return s->top == -1; }

// 스택에 값 추가
void push(Stack *s, TreeNode *node) {
  s->nodes[++(s->top)] = node;
  printf("push(%d)\n", node->data);
}

// 스택에서 값 제거
TreeNode *pop(Stack *s) {
  TreeNode *node = s->nodes[(s->top)--];
  printf("pop(%d)\n", node->data);
  return node;
}

// 트리 노드 배치 함수
void PlaceNode(TreeNode *node, int direction, int data) {
  TreeNode *newNode = malloc(sizeof(TreeNode));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  if (direction == 0) {
    node->left = newNode;
  } else {
    node->right = newNode;
  }
}

// 트리 생성 함수
void GenerateLinkTree(TreeNode *root) {
  PlaceNode(root, 0, 2);                // root->left = 2
  PlaceNode(root, 1, 9);                // root->right = 9
  PlaceNode(root->left, 0, 3);          // 2의 왼쪽 = 3
  PlaceNode(root->left, 1, 5);          // 2의 오른쪽 = 5
  PlaceNode(root->right, 0, 10);        // 9의 왼쪽 = 10
  PlaceNode(root->right, 1, 13);        // 9의 오른쪽 = 13
  PlaceNode(root->left->left, 0, 4);    // 3의 왼쪽 = 4
  PlaceNode(root->left->right, 0, 6);   // 5의 왼쪽 = 6
  PlaceNode(root->left->right, 1, 7);   // 5의 오른쪽 = 7
  PlaceNode(root->right->left, 0, 11);  // 10의 왼쪽 = 11
  PlaceNode(root->right->left, 1, 12);  // 10의 오른쪽 = 12
  PlaceNode(root->right->right, 0, 14); // 13의 왼쪽 = 14
  PlaceNode(root->right->right, 1, 15); // 13의 오른쪽 = 15
}

// 전위 순회 (스택 사용)
void LinkPreOrder(TreeNode *root) {
  Stack s;
  initStack(&s);
  push(&s, root);

  while (!isEmpty(&s)) {
    TreeNode *node = pop(&s);
    printf("visit(%d)\n", node->data);
    if (node->right != NULL)
      push(&s, node->right);
    if (node->left != NULL)
      push(&s, node->left);
  }
}

// 중위 순회 (스택 사용)
void LinkInOrder(TreeNode *root) {
  Stack s;
  initStack(&s);
  TreeNode *current = root;

  while (!isEmpty(&s) || current != NULL) {
    if (current != NULL) {
      push(&s, current);
      current = current->left;
    } else {
      current = pop(&s);
      printf("visit(%d)\n", current->data);
      current = current->right;
    }
  }
}

// 후위 순회 (스택 사용)
void LinkPostOrder(TreeNode *root) {
  Stack s1, s2;
  initStack(&s1);
  initStack(&s2);
  push(&s1, root);

  while (!isEmpty(&s1)) {
    TreeNode *node = pop(&s1);
    push(&s2, node);
    if (node->left != NULL)
      push(&s1, node->left);
    if (node->right != NULL)
      push(&s1, node->right);
  }

  while (!isEmpty(&s2)) {
    TreeNode *node = pop(&s2);
    printf("visit(%d)\n", node->data);
  }
}

// 트리 순회 실행 함수
void LinkOrders(TreeNode *root) {
  printf("전위 순회:\n");
  LinkPreOrder(root);
  printf("\n중위 순회:\n");
  LinkInOrder(root);
  printf("\n후위 순회\n");
  LinkPostOrder(root);
}

int main() {
  TreeNode *root = malloc(sizeof(TreeNode));
  root->data = 1;
  root->left = NULL;
  root->right = NULL;

  // 트리 생성
  GenerateLinkTree(root);

  // 생성한 트리 순회
  LinkOrders(root);

  return 0;
}
