#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct Node
{
    int data;
    int color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

struct Node *root = NULL;
struct Node *TNULL;

struct Node* createNode(int key)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->data = key;
    node->color = RED;
    node->left = TNULL;
    node->right = TNULL;
    node->parent = NULL;
    return node;
}

void leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    x->right = y->left;

    if (y->left != TNULL)
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
}

void rightRotate(struct Node *x)
{
    struct Node *y = x->left;
    x->left = y->right;

    if (y->right != TNULL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void fixInsert(struct Node *k)
{
    struct Node *u;

    while (k->parent->color == RED)
    {
        if (k->parent == k->parent->parent->right)
        {
            u = k->parent->parent->left;

            if (u->color == RED)
            {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else
            {
                if (k == k->parent->left)
                {
                    k = k->parent;
                    rightRotate(k);
                }

                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        }
        else
        {
            u = k->parent->parent->right;

            if (u->color == RED)
            {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else
            {
                if (k == k->parent->right)
                {
                    k = k->parent;
                    leftRotate(k);
                }

                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }

        if (k == root)
            break;
    }

    root->color = BLACK;
}

void insert(int key)
{
    struct Node *node = createNode(key);
    struct Node *y = NULL;
    struct Node *x = root;

    while (x != TNULL)
    {
        y = x;

        if (node->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;

    if (y == NULL)
        root = node;
    else if (node->data < y->data)
        y->left = node;
    else
        y->right = node;

    if (node->parent == NULL)
    {
        node->color = BLACK;
        return;
    }

    if (node->parent->parent == NULL)
        return;

    fixInsert(node);
}

struct Node* search(struct Node *node, int key)
{
    if (node == TNULL || key == node->data)
        return node;

    if (key < node->data)
        return search(node->left, key);

    return search(node->right, key);
}

void inorder(struct Node *node)
{
    if (node != TNULL)
    {
        inorder(node->left);
        printf("%d ", node->data);
        inorder(node->right);
    }
}

int main()
{
    int choice, key;

    TNULL = (struct Node*)malloc(sizeof(struct Node));
    TNULL->color = BLACK;
    TNULL->left = NULL;
    TNULL->right = NULL;

    root = TNULL;

    while (1)
    {
        printf("\n1.Insert\n2.Search\n3.Display\n4.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter key: ");
                scanf("%d", &key);
                insert(key);
                break;

            case 2:
                printf("Enter key: ");
                scanf("%d", &key);
                if (search(root, key) != TNULL)
                    printf("Key Found\n");
                else
                    printf("Key Not Found\n");
                break;

            case 3:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                exit(0);
        }
    }
}