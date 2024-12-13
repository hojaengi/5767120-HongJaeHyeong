#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

int compareCount = 0;
int searchCount = 0;

int getHeight(Node* node) {
    return node ? node->height : 0;
}

Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

Node* insertAVL(Node* root, int key) {
    if (!root) return createNode(key);

    compareCount++;
    if (key < root->key) {
        root->left = insertAVL(root->left, key);
    } else if (key > root->key) {
        root->right = insertAVL(root->right, key);
    } else {
        return root;
    }

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

    int balance = getHeight(root->left) - getHeight(root->right);

    if (balance > 1 && key < root->left->key) return rotateRight(root);
    if (balance < -1 && key > root->right->key) return rotateLeft(root);
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* deleteAVL(Node* root, int key) {
    if (!root) return root;

    compareCount++;
    if (key < root->key) {
        root->left = deleteAVL(root->left, key);
    } else if (key > root->key) {
        root->right = deleteAVL(root->right, key);
    } else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node* temp = root->right;
            while (temp->left) temp = temp->left;
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

    int balance = getHeight(root->left) - getHeight(root->right);

    if (balance > 1 && getHeight(root->left->left) >= getHeight(root->left->right)) return rotateRight(root);
    if (balance > 1 && getHeight(root->left->left) < getHeight(root->left->right)) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getHeight(root->right->right) >= getHeight(root->right->left)) return rotateLeft(root);
    if (balance < -1 && getHeight(root->right->right) < getHeight(root->right->left)) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* insertBST(Node* root, int key) {
    if (!root) return createNode(key);

    compareCount++;
    if (key < root->key) {
        root->left = insertBST(root->left, key);
    } else if (key > root->key) {
        root->right = insertBST(root->right, key);
    }

    return root;
}

Node* deleteBST(Node* root, int key) {
    if (!root) return root;

    compareCount++;
    if (key < root->key) {
        root->left = deleteBST(root->left, key);
    } else if (key > root->key) {
        root->right = deleteBST(root->right, key);
    } else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node* temp = root->right;
            while (temp->left) temp = temp->left;
            root->key = temp->key;
            root->right = deleteBST(root->right, temp->key);
        }
    }

    return root;
}

Node* search(Node* root, int key) {
    if (!root || root->key == key) {
        compareCount++;
        return root;
    }

    compareCount++;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;

        if (A == 0) {
            root = insertAVL(root, B);
        } else if (A == 1) {
            root = deleteAVL(root, B);
        } else {
            searchCount++;
            search(root, B);
        }
    }
}

void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;

        if (A == 0) {
            root = insertBST(root, B);
        } else if (A == 1) {
            root = deleteBST(root, B);
        } else {
            searchCount++;
            search(root, B);
        }
    }
}

int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // 과제에서 제시된 AVL에 대한 2000회 Batch 작업을 수행한다.
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    // 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
    freeTree(root);
    root = NULL;
    compareCount = searchCount = 0;

    // 과제에서 제시된 Binary Search Tree Batch를 수행한다.
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);
    return 0;
}
