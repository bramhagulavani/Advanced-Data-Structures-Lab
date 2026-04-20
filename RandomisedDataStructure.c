#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 5

struct Node {
    int key;
    struct Node* forward[MAX_LEVEL];
};

struct Node* createNode(int key, int level) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;

    for (int i = 0; i < MAX_LEVEL; i++)
        node->forward[i] = NULL;

    return node;
}

int randomLevel() {
    int level = 1;
    while ((rand() % 2) && level < MAX_LEVEL)
        level++;
    return level;
}

struct Node* insert(struct Node* header, int key) {
    struct Node* update[MAX_LEVEL];
    struct Node* temp = header;

    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (temp->forward[i] && temp->forward[i]->key < key)
            temp = temp->forward[i];
        update[i] = temp;
    }

    int level = randomLevel();
    struct Node* newNode = createNode(key, level);

    for (int i = 0; i < level; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }

    return header;
}

int search(struct Node* header, int key) {
    struct Node* temp = header;

    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (temp->forward[i] && temp->forward[i]->key < key)
            temp = temp->forward[i];
    }

    temp = temp->forward[0];

    if (temp && temp->key == key)
        return 1;
    return 0;
}

int main() {
    srand(time(NULL));

    struct Node* header = createNode(-1, MAX_LEVEL);

    int n, key;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        header = insert(header, key);
    }

    printf("Enter key to search: ");
    scanf("%d", &key);

    if (search(header, key))
        printf("Found\n");
    else
        printf("Not Found\n");

    return 0;
}