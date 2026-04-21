#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000

/* ==================== SEGMENT TREE ==================== */

typedef struct {
    int *tree;
    int *arr;
    int n;
} SegmentTree;

// Build segment tree for range sum/min/max queries
void buildSegmentTree(SegmentTree *st, int node, int start, int end) {
    if (start == end) {
        st->tree[node] = st->arr[start];
    } else {
        int mid = (start + end) / 2;
        int leftChild = 2 * node;
        int rightChild = 2 * node + 1;
        
        buildSegmentTree(st, leftChild, start, mid);
        buildSegmentTree(st, rightChild, mid + 1, end);
        
        // For range sum
        st->tree[node] = st->tree[leftChild] + st->tree[rightChild];
    }
}

// Query range sum
int querySegmentTree(SegmentTree *st, int node, int start, int end, int l, int r) {
    if (r < start || end < l)
        return 0; // No overlap
    
    if (l <= start && end <= r)
        return st->tree[node]; // Complete overlap
    
    int mid = (start + end) / 2;
    int leftSum = querySegmentTree(st, 2 * node, start, mid, l, r);
    int rightSum = querySegmentTree(st, 2 * node + 1, mid + 1, end, l, r);
    
    return leftSum + rightSum;
}

// Update element in segment tree
void updateSegmentTree(SegmentTree *st, int node, int start, int end, int idx, int val) {
    if (start == end) {
        st->arr[idx] = val;
        st->tree[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid)
            updateSegmentTree(st, 2 * node, start, mid, idx, val);
        else
            updateSegmentTree(st, 2 * node + 1, mid + 1, end, idx, val);
        
        st->tree[node] = st->tree[2 * node] + st->tree[2 * node + 1];
    }
}

// Initialize segment tree
SegmentTree* initSegmentTree(int arr[], int n) {
    SegmentTree *st = (SegmentTree*)malloc(sizeof(SegmentTree));
    st->n = n;
    st->arr = (int*)malloc(n * sizeof(int));
    st->tree = (int*)malloc(4 * n * sizeof(int));
    
    for (int i = 0; i < n; i++)
        st->arr[i] = arr[i];
    
    buildSegmentTree(st, 1, 0, n - 1);
    return st;
}

/* ==================== INTERVAL TREE ==================== */

typedef struct Interval {
    int start;
    int end;
    int data;
} Interval;

typedef struct IntervalNode {
    Interval interval;
    int maxEnd; // Maximum end value in subtree
    struct IntervalNode *left;
    struct IntervalNode *right;
} IntervalNode;

// Create new interval node
IntervalNode* createIntervalNode(int start, int end, int data) {
    IntervalNode *node = (IntervalNode*)malloc(sizeof(IntervalNode));
    node->interval.start = start;
    node->interval.end = end;
    node->interval.data = data;
    node->maxEnd = end;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Insert interval into interval tree
IntervalNode* insertInterval(IntervalNode *root, int start, int end, int data) {
    if (root == NULL)
        return createIntervalNode(start, end, data);
    
    if (start < root->interval.start)
        root->left = insertInterval(root->left, start, end, data);
    else
        root->right = insertInterval(root->right, start, end, data);
    
    // Update maxEnd
    if (root->maxEnd < end)
        root->maxEnd = end;
    
    return root;
}

// Check if two intervals overlap
int doOverlap(Interval a, Interval b) {
    return (a.start <= b.end && b.start <= a.end);
}

// Search for overlapping intervals
void searchOverlappingIntervals(IntervalNode *root, Interval query, Interval results[], int *count) {
    if (root == NULL)
        return;
    
    // If query overlaps with current interval
    if (doOverlap(root->interval, query)) {
        results[*count] = root->interval;
        (*count)++;
    }
    
    // If left subtree exists and maxEnd >= query start, search left
    if (root->left != NULL && root->left->maxEnd >= query.start)
        searchOverlappingIntervals(root->left, query, results, count);
    
    // Always search right if possible
    if (root->right != NULL)
        searchOverlappingIntervals(root->right, query, results, count);
}

/* ==================== MENU FUNCTIONS ==================== */

void displaySegmentTreeMenu() {
    printf("\n=== SEGMENT TREE OPERATIONS ===\n");
    printf("1. Build Segment Tree\n");
    printf("2. Query Range Sum\n");
    printf("3. Update Element\n");
    printf("4. Display Array\n");
    printf("5. Back to Main Menu\n");
    printf("Enter choice: ");
}

void displayIntervalTreeMenu() {
    printf("\n=== INTERVAL TREE OPERATIONS ===\n");
    printf("1. Build Interval Tree\n");
    printf("2. Insert Interval\n");
    printf("3. Search Overlapping Intervals\n");
    printf("4. Display Intervals\n");
    printf("5. Back to Main Menu\n");
    printf("Enter choice: ");
}

void displayArray(int arr[], int n) {
    printf("\nArray: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void displayIntervals(IntervalNode *root) {
    if (root == NULL)
        return;
    
    displayIntervals(root->left);
    printf("[%d - %d] (Data: %d, MaxEnd: %d)\n", root->interval.start, root->interval.end, root->interval.data, root->maxEnd);
    displayIntervals(root->right);
}

/* ==================== MAIN MENU ==================== */

int main() {
    int choice;
    SegmentTree *segTree = NULL;
    IntervalNode *intervalTree = NULL;
    
    while (1) {
        printf("\n\n===== INTERVAL & SEGMENT TREE PROGRAM =====\n");
        printf("1. Segment Tree Operations\n");
        printf("2. Interval Tree Operations\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            
            case 1: { // Segment Tree
                int segChoice;
                int arr[MAX_N], n = 0;
                
                while (1) {
                    displaySegmentTreeMenu();
                    scanf("%d", &segChoice);
                    
                    switch (segChoice) {
                        case 1: {
                            printf("\nEnter number of elements: ");
                            scanf("%d", &n);
                            printf("Enter elements: ");
                            for (int i = 0; i < n; i++)
                                scanf("%d", &arr[i]);
                            
                            if (segTree != NULL) {
                                free(segTree->arr);
                                free(segTree->tree);
                                free(segTree);
                            }
                            
                            segTree = initSegmentTree(arr, n);
                            printf("\nSegment Tree built successfully!\n");
                            displayArray(arr, n);
                            break;
                        }
                        
                        case 2: {
                            if (segTree == NULL) {
                                printf("\nSegment Tree not built! Build it first.\n");
                                break;
                            }
                            int l, r;
                            printf("\nEnter range [l, r]: ");
                            scanf("%d %d", &l, &r);
                            
                            if (l < 0 || r >= segTree->n || l > r) {
                                printf("\nInvalid range!\n");
                                break;
                            }
                            
                            int sum = querySegmentTree(segTree, 1, 0, segTree->n - 1, l, r);
                            printf("Range sum [%d, %d] = %d\n", l, r, sum);
                            break;
                        }
                        
                        case 3: {
                            if (segTree == NULL) {
                                printf("\nSegment Tree not built! Build it first.\n");
                                break;
                            }
                            int idx, val;
                            printf("\nEnter index and new value: ");
                            scanf("%d %d", &idx, &val);
                            
                            if (idx < 0 || idx >= segTree->n) {
                                printf("\nInvalid index!\n");
                                break;
                            }
                            
                            updateSegmentTree(segTree, 1, 0, segTree->n - 1, idx, val);
                            printf("Updated arr[%d] = %d\n", idx, val);
                            displayArray(segTree->arr, segTree->n);
                            break;
                        }
                        
                        case 4: {
                            if (segTree == NULL) {
                                printf("\nSegment Tree not built!\n");
                                break;
                            }
                            displayArray(segTree->arr, segTree->n);
                            break;
                        }
                        
                        case 5:
                            goto mainMenu;
                        
                        default:
                            printf("\nInvalid choice!\n");
                    }
                }
                break;
            }
            
            case 2: { // Interval Tree
                int intChoice;
                Interval intervals[MAX_N];
                int intervalCount = 0;
                
                while (1) {
                    displayIntervalTreeMenu();
                    scanf("%d", &intChoice);
                    
                    switch (intChoice) {
                        case 1: {
                            printf("\nEnter number of intervals: ");
                            scanf("%d", &intervalCount);
                            
                            if (intervalTree != NULL) {
                                // Free old tree (simple approach - create new)
                                intervalTree = NULL;
                            }
                            
                            intervalTree = NULL;
                            
                            for (int i = 0; i < intervalCount; i++) {
                                printf("Enter interval %d [start end]: ", i + 1);
                                int start, end;
                                scanf("%d %d", &start, &end);
                                intervalTree = insertInterval(intervalTree, start, end, i + 1);
                                intervals[i].start = start;
                                intervals[i].end = end;
                                intervals[i].data = i + 1;
                            }
                            
                            printf("\nInterval Tree built successfully!\n");
                            break;
                        }
                        
                        case 2: {
                            if (intervalTree == NULL) {
                                printf("\nInterval Tree not built! Build it first.\n");
                                break;
                            }
                            
                            printf("\nEnter interval [start end]: ");
                            int start, end;
                            scanf("%d %d", &start, &end);
                            intervalTree = insertInterval(intervalTree, start, end, intervalCount + 1);
                            intervalCount++;
                            printf("Interval inserted!\n");
                            break;
                        }
                        
                        case 3: {
                            if (intervalTree == NULL) {
                                printf("\nInterval Tree not built! Build it first.\n");
                                break;
                            }
                            
                            printf("\nEnter query interval [start end]: ");
                            int qstart, qend;
                            scanf("%d %d", &qstart, &qend);
                            
                            Interval query;
                            query.start = qstart;
                            query.end = qend;
                            
                            Interval results[MAX_N];
                            int count = 0;
                            
                            searchOverlappingIntervals(intervalTree, query, results, &count);
                            
                            if (count == 0)
                                printf("\nNo overlapping intervals found.\n");
                            else {
                                printf("\nOverlapping intervals found: %d\n", count);
                                for (int i = 0; i < count; i++)
                                    printf("  [%d - %d]\n", results[i].start, results[i].end);
                            }
                            break;
                        }
                        
                        case 4: {
                            if (intervalTree == NULL) {
                                printf("\nInterval Tree not built!\n");
                                break;
                            }
                            printf("\nAll Intervals (In-order):\n");
                            displayIntervals(intervalTree);
                            break;
                        }
                        
                        case 5:
                            goto mainMenu;
                        
                        default:
                            printf("\nInvalid choice!\n");
                    }
                }
                break;
            }
            
            case 3:
                printf("\nExiting program. Goodbye!\n");
                exit(0);
            
            default:
                printf("\nInvalid choice!\n");
                
        }
        
        mainMenu:;
    }
    
    return 0;
}