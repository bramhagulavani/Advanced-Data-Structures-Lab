#include <stdio.h>
#include <string.h>

#define MAX 100

// Patient structure
struct Patient {
    char name[50];
    int priority;
};

struct Patient heap[MAX];
int n = 0;

// Swap patients
void swap(struct Patient *a, struct Patient *b) {
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}

// Insert patient
void insert(char name[], int priority) {
    int i = n;

    strcpy(heap[n].name, name);
    heap[n].priority = priority;
    n++;

    // Heapify up
    while (i > 0 && heap[(i - 1) / 2].priority > heap[i].priority) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Treat patient (delete min)
void treatPatient() {
    if (n == 0) {
        printf("No patients\n");
        return;
    }

    printf("Treating Patient: %s (Priority %d)\n", heap[0].name, heap[0].priority);

    heap[0] = heap[n - 1];
    n--;

    int i = 0;

    // Heapify down
    while (1) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;

        if (left < n && heap[left].priority < heap[smallest].priority)
            smallest = left;

        if (right < n && heap[right].priority < heap[smallest].priority)
            smallest = right;

        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else
            break;
    }
}

// Peek next patient
void peek() {
    if (n == 0)
        printf("No patients\n");
    else
        printf("Next Patient: %s (Priority %d)\n", heap[0].name, heap[0].priority);
}

// Main
int main() {
    int choice, priority;
    char name[50];

    while (1) {
        printf("\n--- Hospital Emergency System ---\n");
        printf("1. Add Patient\n");
        printf("2. Treat Patient\n");
        printf("3. View Next Patient\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter patient name: ");
                scanf("%s", name);

                printf("Enter priority (1=Critical, 2=Serious, 3=Normal): ");
                scanf("%d", &priority);

                insert(name, priority);
                break;

            case 2:
                treatPatient();
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