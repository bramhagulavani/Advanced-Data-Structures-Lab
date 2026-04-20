#include <stdio.h>
#include <stdlib.h>

#define MAX 3   // Order m = 3 (can change)

struct BTreeNode {
    int keys[MAX];
    struct BTreeNode *child[MAX + 1];
    int count;
};

// Create node
struct BTreeNode* createNode() {
    struct BTreeNode *node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->count = 0;

    for (int i = 0; i <= MAX; i++)
        node->child[i] = NULL;

    return node;
}

// Split node
void splitNode(int key, int *upKey, struct BTreeNode *node,
               int pos, struct BTreeNode *child,
               struct BTreeNode **newNode) {

    int mid = MAX / 2;
    *newNode = createNode();

    int i;

    for (i = mid + 1; i < MAX; i++) {
        (*newNode)->keys[i - (mid + 1)] = node->keys[i];
        (*newNode)->child[i - mid] = node->child[i + 1];
    }

    (*newNode)->count = MAX - mid - 1;
    node->count = mid;

    if (pos <= mid) {
        insertNode(key, pos, node, child);
    } else {
        insertNode(key, pos - mid - 1, *newNode, child);
    }

    *upKey = node->keys[node->count - 1];
    (*newNode)->child[0] = node->child[node->count];
    node->count--;
}

// Insert in node
void insertNode(int key, int pos, struct BTreeNode *node, struct BTreeNode *child) {
    int i;
    for (i = node->count; i > pos; i--) {
        node->keys[i] = node->keys[i - 1];
        node->child[i + 1] = node->child[i];
    }

    node->keys[pos] = key;
    node->child[pos + 1] = child;
    node->count++;
}

// Insert value
int setValue(int key, int *upKey, struct BTreeNode *node,
             struct BTreeNode **child) {

    int pos;

    if (!node) {
        *upKey = key;
        *child = NULL;
        return 1;
    }

    if (key < node->keys[0])
        pos = 0;
    else {
        for (pos = node->count - 1; pos > 0 && key < node->keys[pos]; pos--);
        if (key == node->keys[pos]) {
            printf("Duplicate key\n");
            return 0;
        }
        pos++;
    }

    if (setValue(key, upKey, node->child[pos], child)) {
        if (node->count < MAX) {
            insertNode(*upKey, pos, node, *child);
        } else {
            struct BTreeNode *newNode;
            splitNode(*upKey, upKey, node, pos, *child, &newNode);
            *child = newNode;
            return 1;
        }
    }
    return 0;
}

// Insert function
struct BTreeNode* insert(struct BTreeNode *root, int key) {
    int upKey;
    struct BTreeNode *child;

    if (setValue(key, &upKey, root, &child)) {
        struct BTreeNode *newRoot = createNode();
        newRoot->keys[0] = upKey;
        newRoot->child[0] = root;
        newRoot->child[1] = child;
        newRoot->count = 1;
        return newRoot;
    }
    return root;
}

// Search
int search(struct BTreeNode *root, int key) {
    if (!root)
        return 0;

    int i = 0;

    while (i < root->count && key > root->keys[i])
        i++;

    if (i < root->count && key == root->keys[i])
        return 1;

    return search(root->child[i], key);
}

// Main
int main() {
    struct BTreeNode *root = NULL;
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