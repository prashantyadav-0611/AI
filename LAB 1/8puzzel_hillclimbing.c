#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

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
    int cost;
} State;

// Compute heuristic: misplaced tiles
int misplacedTiles(State s) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (s.puzzle[i][j] != 0 && s.puzzle[i][j] != goal[i][j])
                count++;
    return count;
}

// Print puzzle
void printState(State s) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", s.puzzle[i][j]);
        printf("\n");
    }
    printf("Heuristic (misplaced tiles): %d\n\n", s.cost);
}

// Find blank position
void findBlank(State s, int *x, int *y) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (s.puzzle[i][j] == 0) {
                *x = i; *y = j;
                return;
            }
}

// Check goal
int isGoal(State s) {
    return (s.cost == 0);
}

// Hill climbing algorithm
void hillClimb(State initial) {
    State current = initial;
    current.cost = misplacedTiles(current);

    printf("Initial State:\n");
    printState(current);

    while (1) {
        int x, y;
        findBlank(current, &x, &y);

        State bestNeighbor = current;
        int improved = 0;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                State neighbor = current;
                // swap blank with neighbor
                neighbor.puzzle[x][y] = current.puzzle[nx][ny];
                neighbor.puzzle[nx][ny] = 0;
                neighbor.cost = misplacedTiles(neighbor);

                if (neighbor.cost < bestNeighbor.cost) {
                    bestNeighbor = neighbor;
                    improved = 1;
                }
            }
        }

        if (!improved) {
            printf("Reached local optimum (or goal):\n");
            printState(current);
            return;
        }

        current = bestNeighbor;

        if (isGoal(current)) {
            printf("Goal reached!\n");
            printState(current);
            return;
        }
    }
}

int main() {
    State initial = {
        {{2, 8, 3},
         {1, 6, 4},
         {7, 0, 5}},
        0
    };

    clock_t start = clock();
    hillClimb(initial);
    clock_t end = clock();

    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %.6f seconds\n", timeTaken);

    return 0;
}
