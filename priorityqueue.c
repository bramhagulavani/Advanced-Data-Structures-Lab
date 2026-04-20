#include <stdio.h>
int heap[100];
int n = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Insert
void insert(int value) {
    int i = n;
    heap[n++] = value;

    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Delete (remove min)
void deleteMin() {
    if (n == 0) {
        printf("Queue empty\n");
        return;
    }

    printf("Deleted: %d\n", heap[0]);

    heap[0] = heap[n - 1];
    n--;

    int i = 0;

    while (1) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;

        if (left < n && heap[left] < heap[smallest])
            smallest = left;

        if (right < n && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else
            break;
    }
}

// Peek
void peek() {
    if (n == 0)
        printf("Queue empty\n");
    else
        printf("Top element: %d\n", heap[0]);
}

int main() {
    int choice, val;

    while (1) {
        printf("\n1.Insert \n2.Delete \n3.Peek \n4.Exit\n");
        printf("\nEnter the choice:");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                insert(val);
                break;

            case 2:
                deleteMin();
                break;

            case 3:
                peek();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}