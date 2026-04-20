#include <stdio.h>
#include <stdlib.h>

struct node
{
    char data;
    struct node *left;
    struct node *right;
    int rthread;  
};

struct node* leftMost(struct node* root)
{
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

void inorderThreaded(struct node* root)
{
    struct node* curr = leftMost(root);

    while (curr != NULL)
    {
        printf("%c ", curr->data);

        if (curr->rthread == 1)
            curr = curr->right;
        else
            curr = leftMost(curr->right);
    }
}

void display(struct node* root)
{
    printf("        %c\n", root->data);
    printf("       /   \\\n");
    printf("      %c     %c\n", root->left->data, root->right->data);
    printf("     /     /   \\\n");
    printf("    %c     %c     %c\n",
           root->left->left->data,
           root->right->left->data,
           root->right->right->data);
    printf("   /\n");
    printf("  %c\n", root->left->left->left->data);
}

int main()
{
    int choice;
    struct node *root, *left, *right;
    struct node *leftleft, *leftleftleft;
    struct node *rightleft, *rightright;

    root = malloc(sizeof(struct node));
    left = malloc(sizeof(struct node));
    right = malloc(sizeof(struct node));
    leftleft = malloc(sizeof(struct node));
    leftleftleft = malloc(sizeof(struct node));
    rightleft = malloc(sizeof(struct node));
    rightright = malloc(sizeof(struct node));

    printf("Enter root: ");
    scanf(" %c", &root->data);
    printf("Enter left child: ");
    scanf(" %c", &left->data);
    printf("Enter right child: ");
    scanf(" %c", &right->data);
    printf("Enter left of left: ");
    scanf(" %c", &leftleft->data);
    printf("Enter left of left of left: ");
    scanf(" %c", &leftleftleft->data);
    printf("Enter left of right: ");
    scanf(" %c", &rightleft->data);
    printf("Enter right of right: ");
    scanf(" %c", &rightright->data);


    root->left = left;      root->right = right;
    left->left = leftleft; left->right = NULL;
    leftleft->left = leftleftleft; leftleft->right = NULL;
    right->left = rightleft; right->right = rightright;

    leftleftleft->left = leftleftleft->right = NULL;
    rightleft->left = rightleft->right = NULL;
    rightright->left = rightright->right = NULL;

    root->rthread = left->rthread = right->rthread = 0;
    leftleft->rthread = leftleftleft->rthread = 0;
    rightleft->rthread = rightright->rthread = 0;

    

    leftleftleft->right = leftleft;
    leftleftleft->rthread = 1;

    leftleft->right = left;
    leftleft->rthread = 1;

    left->right = root;
    left->rthread = 1;

    rightleft->right = right;
    rightleft->rthread = 1;

    do
    {
        printf("\n1.Display Tree\n2.Inorder Threaded Traversal\n3.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                display(root);
                break;

            case 2:
                printf("Inorder Threaded: ");
                inorderThreaded(root);
                printf("\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
