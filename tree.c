#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 2

/* Point structure */
struct Point
{
    int x, y;
};

/* Boundary structure */
struct Boundary
{
    int xMin, yMin, xMax, yMax;
};

/* Quad Tree Node */
struct QuadTree
{
    struct Boundary boundary;
    struct Point points[CAPACITY];
    int count;

    int divided;
    struct QuadTree *nw, *ne, *sw, *se;
};

/* Create Quad Tree */
struct QuadTree *createNode(struct Boundary boundary)
{
    struct QuadTree *node = (struct QuadTree *)malloc(sizeof(struct QuadTree));
    node->boundary = boundary;
    node->count = 0;
    node->divided = 0;
    node->nw = node->ne = node->sw = node->se = NULL;
    return node;
}

/* Check if point lies inside boundary */
int contains(struct Boundary b, struct Point p)
{
    return (p.x >= b.xMin && p.x <= b.xMax &&
            p.y >= b.yMin && p.y <= b.yMax);
}

/* Subdivide */
void subdivide(struct QuadTree *qt)
{
    int midX = (qt->boundary.xMin + qt->boundary.xMax) / 2;
    int midY = (qt->boundary.yMin + qt->boundary.yMax) / 2;

    struct Boundary nw = {qt->boundary.xMin, midY + 1, midX, qt->boundary.yMax};
    struct Boundary ne = {midX + 1, midY + 1, qt->boundary.xMax, qt->boundary.yMax};
    struct Boundary sw = {qt->boundary.xMin, qt->boundary.yMin, midX, midY};
    struct Boundary se = {midX + 1, qt->boundary.yMin, qt->boundary.xMax, midY};

    qt->nw = createNode(nw);
    qt->ne = createNode(ne);
    qt->sw = createNode(sw);
    qt->se = createNode(se);

    qt->divided = 1;
}

/* Insert point */
int insert(struct QuadTree *qt, struct Point p)
{
    if (!contains(qt->boundary, p))
        return 0;

    if (qt->count < CAPACITY)
    {
        qt->points[qt->count++] = p;
        return 1;
    }

    if (!qt->divided)
        subdivide(qt);

    if (insert(qt->nw, p))
        return 1;
    if (insert(qt->ne, p))
        return 1;
    if (insert(qt->sw, p))
        return 1;
    if (insert(qt->se, p))
        return 1;

    return 0;
}

/* Check if two boundaries overlap */
int intersect(struct Boundary a, struct Boundary b)
{
    return !(b.xMin > a.xMax || b.xMax < a.xMin ||
             b.yMin > a.yMax || b.yMax < a.yMin);
}

/* Range Query */
void rangeQuery(struct QuadTree *qt, struct Boundary range)
{
    if (qt == NULL)
        return;

    if (!intersect(qt->boundary, range))
        return;

    for (int i = 0; i < qt->count; i++)
    {
        if (contains(range, qt->points[i]))
        {
            printf("Point Found: (%d, %d)\n",
                   qt->points[i].x, qt->points[i].y);
        }
    }

    if (qt->divided)
    {
        rangeQuery(qt->nw, range);
        rangeQuery(qt->ne, range);
        rangeQuery(qt->sw, range);
        rangeQuery(qt->se, range);
    }
}

/* Display */
void displayHelper(struct QuadTree *qt, int *index)
{
    if (qt == NULL)
        return;

    for (int i = 0; i < qt->count; i++)
    {
        printf("Point %d (%d, %d)\n",
               (*index)++, qt->points[i].x, qt->points[i].y);
    }

    if (qt->divided)
    {
        displayHelper(qt->nw, index);
        displayHelper(qt->ne, index);
        displayHelper(qt->sw, index);
        displayHelper(qt->se, index);
    }
}

void display(struct QuadTree *qt)
{
    int index = 1;
    displayHelper(qt, &index);
}

/* Main */
int main()
{
    int choice;
    struct Point p;

    struct Boundary boundary;
    printf("==============================\n");
    printf("*Define the 2D Space Boundary*\n");

    printf("Enter minimum X coordinate: ");
    scanf("%d", &boundary.xMin);

    printf("Enter minimum Y coordinate: ");
    scanf("%d", &boundary.yMin);

    printf("Enter maximum X coordinate: ");
    scanf("%d", &boundary.xMax);

    printf("Enter maximum Y coordinate: ");
    scanf("%d", &boundary.yMax);
    printf("==============================\n\n");

    struct QuadTree *qt = createNode(boundary);

    while (1)
    {
        printf("\n------ QUAD TREE MENU ------\n");
        printf("1. Insert Point\n");
        printf("2. Range Query\n");
        printf("3. Display All Points\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            printf("\nEnter point coordinates:\n");
            printf("X (horizontal position): ");
            scanf("%d", &p.x);

            printf("Y (vertical position): ");
            scanf("%d", &p.y);

            if (insert(qt, p))
                printf("Point inserted successfully!\n");
            else
                printf("Point is outside the boundary!\n");
            break;

        case 2:
        {
            struct Boundary range;

            printf("\nEnter range for search:\n");
            printf("Minimum X (left boundary): ");
            scanf("%d", &range.xMin);

            printf("Minimum Y (bottom boundary): ");
            scanf("%d", &range.yMin);

            printf("Maximum X (right boundary): ");
            scanf("%d", &range.xMax);

            printf("Maximum Y (top boundary): ");
            scanf("%d", &range.yMax);

            printf("\nPoints inside given range:\n");
            rangeQuery(qt, range);
            break;
        }

        case 3:
            printf("\nStored Points:\n");
            display(qt);
            break;

        case 4:
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}