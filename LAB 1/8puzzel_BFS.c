#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 3
#define MAX_STATES 50000   // limit visited states

int goal[N][N] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// Directions: up, down, left, right
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

typedef struct {
    int puzzle[N][N];
    int depth;
} State;

// Queue for BFS
State queue[MAX_STATES];
int front = 0, rear = 0;

// Visited states
State visited[MAX_STATES];
int visitedCount = 0;

void enqueue(State s) {
    if (rear < MAX_STATES)
        queue[rear++] = s;
}

State dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

int isGoal(State s) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (s.puzzle[i][j] != goal[i][j])
                return 0;
    return 1;
}

int isSame(State a, State b) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a.puzzle[i][j] != b.puzzle[i][j])
                return 0;
    return 1;
}

int isVisited(State s) {
    for (int i = 0; i < visitedCount; i++) {
        if (isSame(visited[i], s))
            return 1;
    }
    return 0;
}

void findBlank(State s, int *x, int *y) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (s.puzzle[i][j] == 0) {
                *x = i;
                *y = j;
                return;
            }
}

void printState(State s) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", s.puzzle[i][j]);
        printf("\n");
    }
    printf("\n");
}

// BFS algorithm
int BFS(State initial) {
    front = rear = 0;
    visitedCount = 0;

    enqueue(initial);

    while (!isEmpty()) {
        State current = dequeue();

        if (isVisited(current))
            continue;

        visited[visitedCount++] = current;

        if (isGoal(current)) {
            printf("Goal reached at depth %d!\n", current.depth);
            printState(current);
            return 1; // solved
        }

        int x, y;
        findBlank(current, &x, &y);

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                State next = current;
                // swap
                next.puzzle[x][y] = current.puzzle[nx][ny];
                next.puzzle[nx][ny] = 0;
                next.depth = current.depth + 1;

                if (!isVisited(next))
                    enqueue(next);
            }
        }
    }
    printf("Goal not found.\n");
    return 0;
}

int main() {
    State initial = {
        {{1, 2, 3},
         {4, 0, 6},
         {7, 5, 8}}, // initial state
        0
    };

    printf("Initial State:\n");
    printState(initial);

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int result = BFS(initial);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (result)
        printf("Puzzle solved in %.6f seconds.\n", cpu_time_used);
    else
        printf("Puzzle not solved (time taken: %.6f seconds).\n", cpu_time_used);

    return 0;
}
