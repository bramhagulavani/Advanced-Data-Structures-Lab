#include <stdio.h>
#include <stdlib.h>

#define MAX 3   // Order (m = 3)

struct Node {
    int keys[MAX];
    struct Node *child[MAX + 1];
    int count;
    int isLeaf;
};

// Create node
struct Node* createNode(int isLeaf) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->count = 0;
    node->isLeaf = isLeaf;

    for (int i = 0; i <= MAX; i++)
        node->child[i] = NULL;

    return node;
}

// Insert into leaf (simple)
void insertLeaf(struct Node *node, int key) {
    int i = node->count - 1;

    while (i >= 0 && key < node->keys[i]) {
        node->keys[i + 1] = node->keys[i];
        i--;
    }

    node->keys[i + 1] = key;
    node->count++;
}

// Split leaf node
void splitLeaf(struct Node *node, int *upKey, struct Node **newNode) {
    int mid = (MAX + 1) / 2;

    *newNode = createNode(1);

    node->count = mid;

    (*newNode)->count = MAX - mid;

    for (int i = 0; i < (*newNode)->count; i++)
        (*newNode)->keys[i] = node->keys[mid + i];

    *upKey = (*newNode)->keys[0];
}

// Insert function
struct Node* insert(struct Node *root, int key) {

    // If tree empty
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = key;
        root->count = 1;
        return root;
    }

    // If root is leaf
    if (root->isLeaf) {

        if (root->count < MAX) {
            insertLeaf(root, key);
        } else {
            struct Node *newNode;
            int upKey;

            insertLeaf(root, key);
            splitLeaf(root, &upKey, &newNode);

            struct Node *newRoot = createNode(0);
            newRoot->keys[0] = upKey;
            newRoot->child[0] = root;
            newRoot->child[1] = newNode;
            newRoot->count = 1;

            return newRoot;
        }
    }

    return root;
}

// Search
int search(struct Node *root, int key) {
    if (root == NULL)
        return 0;

    int i = 0;

    while (i < root->count && key > root->keys[i])
        i++;

    if (root->isLeaf) {
        if (i < root->count && key == root->keys[i])
            return 1;
        return 0;
    }

    return search(root->child[i], key);
}

// Main
int main() {
    struct Node *root = NULL;
    int n, key, s;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter keys:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        root = insert(root, key);
    }

    printf("Enter key to search: ");
    scanf("%d", &s);

    if (search(root, s))
        printf("Key found\n");
    else
        printf("Key not found\n");

    return 0;
}