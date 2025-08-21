#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 3
#define MAX_STATES 50000

// Goal state
int goal[N][N] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// Directions: up, down, left, right
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// State structure
typedef struct {
    int puzzle[N][N];
    int depth;
    int cost;   // heuristic (misplaced tiles)
} State;

// Priority Queue Node
typedef struct {
    State state;
    int priority;
} PQNode;

PQNode pq[MAX_STATES];
int pqSize = 0;

// Visited states
State visited[MAX_STATES];
int visitedCount = 0;

// Function to compute heuristic (misplaced tiles)
int misplacedTiles(State s) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (s.puzzle[i][j] != 0 && s.puzzle[i][j] != goal[i][j])
                count++;
        }
    }
    return count;
}

// Priority Queue helpers
void pushPQ(State s, int priority) {
    if (pqSize < MAX_STATES) {
        pq[pqSize].state = s;
        pq[pqSize].priority = priority;
        pqSize++;
    }
}

State popPQ() {
    int bestIndex = 0;
    for (int i = 1; i < pqSize; i++) {
        if (pq[i].priority < pq[bestIndex].priority)
            bestIndex = i;
    }
    State bestState = pq[bestIndex].state;
    // Shift left
    for (int i = bestIndex; i < pqSize - 1; i++) {
        pq[i] = pq[i + 1];
    }
    pqSize--;
    return bestState;
}

int isPQEmpty() {
    return pqSize == 0;
}

// Compare states
int isSame(State a, State b) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a.puzzle[i][j] != b.puzzle[i][j])
                return 0;
    return 1;
}

// Check if visited
int isVisited(State s) {
    for (int i = 0; i < visitedCount; i++) {
        if (isSame(visited[i], s))
            return 1;
    }
    return 0;
}

// Find blank (0 position)
void findBlank(State s, int *x, int *y) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (s.puzzle[i][j] == 0) {
                *x = i;
                *y = j;
                return;
            }
}

// Print puzzle
void printState(State s) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", s.puzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Check if goal
int isGoal(State s) {
    return misplacedTiles(s) == 0;
}

// Best-First Search using misplaced tiles heuristic
void bestFirstSearch(State initial) {
    pqSize = 0;
    visitedCount = 0;

    initial.cost = misplacedTiles(initial);
    pushPQ(initial, initial.cost);

    while (!isPQEmpty()) {
        State current = popPQ();

        if (isVisited(current))
            continue;

        visited[visitedCount++] = current;

        if (isGoal(current)) {
            printf("Goal found at depth %d\n", current.depth);
            printState(current);
            return;
        }

        int x, y;
        findBlank(current, &x, &y);

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                State next = current;
                // Swap blank
                next.puzzle[x][y] = current.puzzle[nx][ny];
                next.puzzle[nx][ny] = 0;
                next.depth = current.depth + 1;
                next.cost = misplacedTiles(next);

                if (!isVisited(next)) {
                    pushPQ(next, next.cost);
                }
            }
        }
    }

    printf("Goal not found.\n");
}

int main() {
    State initial = {
        {{1, 2, 3},
         {4, 0, 6},
         {7, 5, 8}},
        0,
        0
    };

    printf("Initial State:\n");
    printState(initial);

    clock_t start = clock();
    bestFirstSearch(initial);
    clock_t end = clock();

    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %.6f seconds\n", timeTaken);

    return 0;
}
