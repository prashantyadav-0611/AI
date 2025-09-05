#include <stdio.h>
#include <stdlib.h>

#define MAX 100   // maximum number of steps to store
#define MAXCAP 1000  // max jug capacity supported

typedef struct {
    int jug1;
    int jug2;
} State;

int capacity1, capacity2;   // jug capacities
int target;                 // target water amount
int targetJug;              // jug where target should appear (1 or 2)

int visited[MAXCAP+1][MAXCAP+1]; // mark visited states
State path[MAX];                 // store solution path
int path_len = 0;

// record path
void push_state(int j1, int j2) {
    if (path_len < MAX) {
        path[path_len].jug1 = j1;
        path[path_len].jug2 = j2;
        path_len++;
    }
}

void pop_state() {
    if (path_len > 0) path_len--;
}

// check goal
int is_goal(int j1, int j2) {
    if (targetJug == 1 && j1 == target) return 1;
    if (targetJug == 2 && j2 == target) return 1;
    return 0;
}

// recursive DFS
int dfs(int j1, int j2) {
    if (visited[j1][j2]) return 0;
    visited[j1][j2] = 1;

    push_state(j1, j2);

    if (is_goal(j1, j2)) return 1;

    // Fill jug1
    if (dfs(capacity1, j2)) return 1;

    // Fill jug2
    if (dfs(j1, capacity2)) return 1;

    // Empty jug1
    if (dfs(0, j2)) return 1;

    // Empty jug2
    if (dfs(j1, 0)) return 1;

    // Pour jug1 -> jug2
    int pour1to2 = (j1 < (capacity2 - j2)) ? j1 : (capacity2 - j2);
    if (dfs(j1 - pour1to2, j2 + pour1to2)) return 1;

    // Pour jug2 -> jug1
    int pour2to1 = (j2 < (capacity1 - j1)) ? j2 : (capacity1 - j1);
    if (dfs(j1 + pour2to1, j2 - pour2to1)) return 1;

    // backtrack
    pop_state();
    return 0;
}

int main() {
    printf("Enter capacity of jug X: ");
    scanf("%d", &capacity1);

    printf("Enter capacity of jug Y: ");
    scanf("%d", &capacity2);

    printf("Enter target amount of water: ");
    scanf("%d", &target);

    printf("In which jug do you want the target (1 for X, 2 for Y)? ");
    scanf("%d", &targetJug);

    if (dfs(0, 0)) {
        printf("\nSolution steps:\n");
        for (int i = 0; i < path_len; i++) {
            printf("(%d, %d)\n", path[i].jug1, path[i].jug2);
        }
    } else {
        printf("No solution found.\n");
    }

    return 0;
}
