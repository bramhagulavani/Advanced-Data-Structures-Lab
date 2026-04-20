#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

// Structure for Min Heap Node
struct MinHeapNode {
    int vertex;
    int distance;
};

// Structure for Min Heap
struct MinHeap {
    int size;
    struct MinHeapNode heap[MAX];
};

// Swap function
void swap(struct MinHeapNode *a, struct MinHeapNode *b) {
    struct MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify (Min Heap)
void heapify(struct MinHeap *h, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size && h->heap[left].distance < h->heap[smallest].distance)
        smallest = left;

    if (right < h->size && h->heap[right].distance < h->heap[smallest].distance)
        smallest = right;

    if (smallest != i) {
        swap(&h->heap[i], &h->heap[smallest]);
        heapify(h, smallest);
    }
}

// Extract minimum node
struct MinHeapNode extractMin(struct MinHeap *h) {
    struct MinHeapNode root = h->heap[0];
    h->heap[0] = h->heap[h->size - 1];
    h->size--;
    heapify(h, 0);
    return root;
}

// Insert into heap
void insertHeap(struct MinHeap *h, int v, int dist) {
    int i = h->size++;
    h->heap[i].vertex = v;
    h->heap[i].distance = dist;

    // Fix min heap property
    while (i && h->heap[(i - 1) / 2].distance > h->heap[i].distance) {
        swap(&h->heap[i], &h->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Dijkstra Algorithm
void dijkstra(int graph[MAX][MAX], int V, int src) {
    int dist[MAX];

    struct MinHeap h;
    h.size = 0;

    // Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }

    dist[src] = 0;
    insertHeap(&h, src, 0);

    while (h.size > 0) {
        struct MinHeapNode minNode = extractMin(&h);
        int u = minNode.vertex;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {

                dist[v] = dist[u] + graph[u][v];
                insertHeap(&h, v, dist[v]);
            }
        }
    }

    // Print result
    printf("\nVertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

// Main function
int main() {
    int V = 5;

    int graph[MAX][MAX] = {
        {0, 10, 0, 5, 0},
        {0, 0, 1, 2, 0},
        {0, 0, 0, 0, 4},
        {0, 3, 9, 0, 2},
        {7, 0, 6, 0, 0}
    };

    int source = 0;

    dijkstra(graph, V, source);

    return 0;
}