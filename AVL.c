#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
    int height;
};

int height(struct node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct node* newNode(int data) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return node;
}
struct node* rightRotate(struct node* y) {
    struct node* x = y->left;
    struct node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct node* leftRotate(struct node* x) {
    struct node* y = x->right;
    struct node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct node* n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}
struct node* insert(struct node* root, int data) {
  
    if (root == NULL)
        return newNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root;  
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    if (balance > 1 && data < root->left->data)
        return rightRotate(root);

    if (balance < -1 && data > root->right->data)
        return leftRotate(root);

    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
void displayTree(struct node* root, int space) {
    if (root == NULL)
        return;

    space += 5;

    displayTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    displayTree(root->left, space);
}

void displayBalanceFactors(struct node* root) {
    if (root != NULL) {
        displayBalanceFactors(root->left);
        printf("Node %d : Balance Factor = %d\n", root->data, getBalance(root));
        displayBalanceFactors(root->right);
    }
}

int main() {
    struct node* root = NULL;
    int choice, data;

    do {
        printf("\n--- AVL Tree Menu ---\n");
        printf("1. Insert node\n");
        printf("2. Display / Calculate Balance Factor of each node\n");
        printf("3. Display Tree\n");
        printf("4. Inorder Traversal\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            root = insert(root, data);
            printf("Node inserted.\n");
            break;

        case 2:
            if (root == NULL)
                printf("Tree is empty.\n");
            else
                displayBalanceFactors(root);
            break;

        case 3:
            if (root == NULL)
                printf("Tree is empty.\n");
            else {
                printf("AVL Tree (sideways view):\n");
                displayTree(root, 0);
            }
            break;

        case 4:
            if (root == NULL)
                printf("Tree is empty.\n");
            else {
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
            }
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}
