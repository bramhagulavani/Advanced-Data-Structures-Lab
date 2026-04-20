#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 26

struct Node {
    struct Node *child[SIZE];
};

struct Node* createNode() {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));

    for (int i = 0; i < SIZE; i++)
        node->child[i] = NULL;

    return node;
}

// Insert suffix
void insert(struct Node *root, char *str) {
    struct Node *temp = root;

    for (int i = 0; str[i] != '\0'; i++) {
        int index = str[i] - 'a';

        if (temp->child[index] == NULL)
            temp->child[index] = createNode();

        temp = temp->child[index];
    }
}

void buildSuffixTree(struct Node *root, char *str) {
    int n = strlen(str);

    for (int i = 0; i < n; i++) {
        insert(root, str + i);
    }
}

int search(struct Node *root, char *pattern) {
    struct Node *temp = root;

    for (int i = 0; pattern[i] != '\0'; i++) {
        int index = pattern[i] - 'a';

        if (temp->child[index] == NULL)
            return 0;

        temp = temp->child[index];
    }

    return 1;
}

int main() {
    char str[1000], pattern[100];

    struct Node *root = createNode();

    printf("Enter string: ");
    scanf("%s", str);

    buildSuffixTree(root, str);

    printf("Enter pattern: ");
    scanf("%s", pattern);

    if (search(root, pattern))
        printf("Pattern found\n");
    else
        printf("Pattern not found\n");

    return 0;
}