#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
};

struct Node *root = NULL;

struct Node* createNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

void leftRotate(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

    printf("Balancing: Left Rotation at node %d\n", x->data);
}

void rightRotate(struct Node *x) {
    struct Node *y = x->left;
    x->left = y->right;

    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;

    printf("Balancing: Right Rotation at node %d\n", x->data);
}

void fixViolation(struct Node *pt) {
    struct Node *parent_pt = NULL;
    struct Node *grand_parent_pt = NULL;

    while ((pt != root) && (pt->color == RED) &&
           (pt->parent->color == RED)) {

        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        if (parent_pt == grand_parent_pt->left) {
            struct Node *uncle_pt = grand_parent_pt->right;

            if (uncle_pt != NULL && uncle_pt->color == RED) {
                printf("Balancing: Recoloring at node %d\n", grand_parent_pt->data);
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                // Case 2: Left-Right Rotation
                if (pt == parent_pt->right) {
                    leftRotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                rightRotate(grand_parent_pt);
                int temp = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = temp;
                pt = parent_pt;
            }
        }
        else {
            struct Node *uncle_pt = grand_parent_pt->left;

            if (uncle_pt != NULL && uncle_pt->color == RED) {
                printf("Balancing: Recoloring at node %d\n", grand_parent_pt->data);
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->left) {
                    rightRotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                leftRotate(grand_parent_pt);
                int temp = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = temp;
                pt = parent_pt;
            }
        }
    }
    root->color = BLACK;
}

void bstInsert(struct Node **root_ref, struct Node *pt) {
    if (*root_ref == NULL) {
        *root_ref = pt;
        return;
    }

    if (pt->data < (*root_ref)->data) {
        bstInsert(&(*root_ref)->left, pt);
        (*root_ref)->left->parent = *root_ref;
    } else if (pt->data > (*root_ref)->data) {
        bstInsert(&(*root_ref)->right, pt);
        (*root_ref)->right->parent = *root_ref;
    }
}

void insert(int data) {
    struct Node *pt = createNode(data);
    bstInsert(&root, pt);
    fixViolation(pt);
    printf("Inserted: %d\n", data);
}

void displayTree(struct Node *root, int space) {
    if (root == NULL)
        return;

    space += 10;
    displayTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d(%c)\n", root->data, root->color == RED ? 'R' : 'B');

    displayTree(root->left, space);
}

void inorder(struct Node *root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d(%c) ", root->data, root->color == RED ? 'R' : 'B');
    inorder(root->right);
}

int main() {
    int choice, n, value;

    while (1) {
        printf("\n--- Red-Black Tree Menu ---\n");
        printf("1. Create RBT\n");
        printf("2. Display the Tree\n");
        printf("3. Inorder Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter number of nodes: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++) {
                printf("Enter value: ");
                scanf("%d", &value);
                insert(value);
            }
            break;

        case 2:
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nTree Structure (Value(Color)):\n");
                displayTree(root, 0);
                printf("\n");
            }
            break;

        case 3:
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("Inorder Traversal (Value(Color)):\n");
                inorder(root);
                printf("\n");
            }
            break;

        case 4:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}