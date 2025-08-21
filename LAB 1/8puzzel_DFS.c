#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // for clock()

#define N 3
#define MAX_STATES 50000   // limit visited states
#define MAX_DEPTH 30       // depth limit for DFS

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
} State;

// Stack for DFS
State stack[MAX_STATES];
int top = -1;

// Visited states storage
State visited[MAX_STATES];
int visitedCount = 0;

void push(State s) {
    if (top < MAX_STATES - 1) {
        stack[++top] = s;
    }
}

State pop() {
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}

// Check if state is goal
int isGoal(State s) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (s.puzzle[i][j] != goal[i][j])
                return 0;
    return 1;
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

// DFS algorithm
int DFS(State initial) {
    push(initial);

    while (!isEmpty()) {
        State current = pop();

        if (isVisited(current))
            continue;

        visited[visitedCount++] = current;

        if (isGoal(current)) {
            printf("Goal reached at depth %d\n", current.depth);
            printState(current);
            return 1; // solved
        }

        if (current.depth >= MAX_DEPTH)
            continue;

        int x, y;
        findBlank(current, &x, &y);

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                State next = current;
                // swap blank
                next.puzzle[x][y] = current.puzzle[nx][ny];
                next.puzzle[nx][ny] = 0;
                next.depth = current.depth + 1;

                if (!isVisited(next)) {
                    push(next);
                }
            }
        }
    }
    printf("Goal not found within depth %d.\n", MAX_DEPTH);
    return 0; // not solved
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
    int result = DFS(initial);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (result)
        printf("Puzzle solved in %.6f seconds.\n", cpu_time_used);
    else
        printf("Puzzle not solved (time taken: %.6f seconds).\n", cpu_time_used);

    return 0;
}
