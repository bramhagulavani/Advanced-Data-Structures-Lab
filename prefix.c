#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEnd;
};

struct TrieNode* createNode() {
    struct TrieNode *node = (struct TrieNode*)malloc(sizeof(struct TrieNode));

    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    node->isEnd = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;

    return node;
}

// Insert word
void insert(struct TrieNode *root, char *word) {
    struct TrieNode *temp = root;

    for (int i = 0; word[i] != '\0'; i++) {

        // Input validation
        if (word[i] < 'a' || word[i] > 'z') {
            printf("Invalid character in word: %c\n", word[i]);
            return;
        }

        int index = word[i] - 'a';

        if (temp->children[index] == NULL)
            temp->children[index] = createNode();

        temp = temp->children[index];
    }

    temp->isEnd = 1;
}

// Search full word
int search(struct TrieNode *root, char *word) {
    struct TrieNode *temp = root;

    for (int i = 0; word[i] != '\0'; i++) {

        if (word[i] < 'a' || word[i] > 'z')
            return 0;

        int index = word[i] - 'a';

        if (temp->children[index] == NULL)
            return 0;

        temp = temp->children[index];
    }

    return temp->isEnd;
}

// Prefix search
int startsWith(struct TrieNode *root, char *prefix) {
    struct TrieNode *temp = root;

    for (int i = 0; prefix[i] != '\0'; i++) {

        if (prefix[i] < 'a' || prefix[i] > 'z')
            return 0;

        int index = prefix[i] - 'a';

        if (temp->children[index] == NULL)
            return 0;

        temp = temp->children[index];
    }

    return 1;
}

void freeTrie(struct TrieNode *root) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL)
            freeTrie(root->children[i]);
    }
    free(root);
}

int main() {
    int n;
    char word[50], prefix[50];

    struct TrieNode *root = createNode();

    printf("Enter number of words: ");
    scanf("%d", &n);

    printf("Enter words:\n");
    for (int i = 0; i < n; i++) {
        scanf("%49s", word);   
        insert(root, word);
    }

    printf("Enter word to search: ");
    scanf("%49s", word);

    if (search(root, word))
        printf("Word found\n");
    else
        printf("Word not found\n");

    printf("Enter prefix to search: ");
    scanf("%49s", prefix);

    if (startsWith(root, prefix))
        printf("Prefix exists\n");
    else
        printf("Prefix does not exist\n");

    freeTrie(root);

    return 0;
}