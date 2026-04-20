#include <stdio.h>
int heap[100];
int n = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* MIN HEAPIFY */
void minHeapify(int i)
{
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && heap[left] < heap[smallest])
        smallest = left;

    if(right < n && heap[right] < heap[smallest])
        smallest = right;

    if(smallest != i)
    {
        swap(&heap[i], &heap[smallest]);
        minHeapify(smallest);
    }
}

/* MAX HEAPIFY */
void maxHeapify(int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && heap[left] > heap[largest])
        largest = left;

    if(right < n && heap[right] > heap[largest])
        largest = right;

    if(largest != i)
    {
        swap(&heap[i], &heap[largest]);
        maxHeapify(largest);
    }
}

void buildMinHeap()
{
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for(int i = 0; i < n; i++)
        scanf("%d", &heap[i]);

    for(int i = n/2 - 1; i >= 0; i--)
        minHeapify(i);

    printf("\nMin Heap Created Successfully\n");
}

void buildMaxHeap()
{
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for(int i = 0; i < n; i++)
        scanf("%d", &heap[i]);

    for(int i = n/2 - 1; i >= 0; i--)
        maxHeapify(i);

    printf("\nMax Heap Created Successfully\n");
}

/* DISPLAY HEAP TREE */
void displayTree()
{
    if(n == 0)
    {
        printf("\nHeap is empty\n");
        return;
    }
    printf("\nHeap Tree Structure:\n\n");

    int level = 0;
    int index = 0;

    while(index < n)
    {
        int nodes = 1 << level;
        int space = 8 >> level;

        for(int s = 0; s < space; s++)
            printf("   ");

        for(int i = 0; i < nodes && index < n; i++)
        {
            printf("%3d", heap[index++]);

            for(int s = 0; s < space; s++)
                printf("      ");
        }
        printf("\n\n");
        level++;
    }
}
int main()
{
    int choice;

    while(1)
    {
        printf("\n------ HEAP MENU ------\n");
        printf("1. Create Min Heap\n");
        printf("2. Create Max Heap\n");
        printf("3. Display Heap Tree\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                buildMinHeap();
                break;

            case 2:
                buildMaxHeap();
                break;

            case 3:
                displayTree();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid Choice\n");
        }
    }
    return 0;
}