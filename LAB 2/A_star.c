#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define MAXN 50       // maximum grid size
#define MAXSTATES 10000  // heap capacity

// Each cell keeps track of g (distance from start) and h (heuristic)
typedef struct {
    int g;
    int h;
} Cell;

// A state represents a position in the grid with its own board
typedef struct State {
    struct State* parent;
    Cell board[MAXN][MAXN];
    int x, y;
} State;

// Moves: left, right, up, down
int drow[] = {0, 0, -1, 1};
int dcol[] = {-1, 1, 0, 0};

int is_valid(int x, int y, int n) {
    return (x >= 0 && x < n && y >= 0 && y < n);
}

int is_goal(int x, int y, int tx, int ty) {
    return (x == tx && y == ty);
}

int manhattan(int x, int y, int tx, int ty) {
    return abs(x - tx) + abs(y - ty);
}

// Print path recursively by following parent links
void print_path(State* s) {
    if (!s) return;
    print_path(s->parent);
    printf("(%d,%d)\n", s->x, s->y);
}

// ---------- Min-Heap for A* (priority queue) ----------
typedef struct {
    State* arr[MAXSTATES];
    int size;
} MinHeap;

int f_value(State* s) {
    return s->board[s->x][s->y].g + s->board[s->x][s->y].h;
}

void swap(State** a, State** b) {
    State* tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify_up(MinHeap* h, int idx) {
    while (idx > 0) {
        int p = (idx - 1) / 2;
        if (f_value(h->arr[idx]) < f_value(h->arr[p])) {
            swap(&h->arr[idx], &h->arr[p]);
            idx = p;
        } else break;
    }
}

void heapify_down(MinHeap* h, int idx) {
    while (1) {
        int left = 2*idx + 1, right = 2*idx + 2, small = idx;
        if (left < h->size && f_value(h->arr[left]) < f_value(h->arr[small]))
            small = left;
        if (right < h->size && f_value(h->arr[right]) < f_value(h->arr[small]))
            small = right;
        if (small != idx) {
            swap(&h->arr[idx], &h->arr[small]);
            idx = small;
        } else break;
    }
}

void push(MinHeap* h, State* s) {
    if (h->size >= MAXSTATES) return;
    h->arr[h->size] = s;
    heapify_up(h, h->size);
    h->size++;
}

State* pop(MinHeap* h) {
    if (h->size == 0) return NULL;
    State* top = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    heapify_down(h, 0);
    return top;
}

// ---------- A* search ----------
void a_star(State* start, int n, int tx, int ty) {
    MinHeap pq = { .size = 0 };
    push(&pq, start);

    int visited[MAXN][MAXN] = {0};

    while (pq.size > 0) {
        State* cur = pop(&pq);

        if (visited[cur->x][cur->y]) continue;
        visited[cur->x][cur->y] = 1;

        if (is_goal(cur->x, cur->y, tx, ty)) {
            printf("\nPath found:\n");
            print_path(cur);
            return;
        }

        // explore neighbors
        for (int k = 0; k < 4; k++) {
            int nx = cur->x + drow[k];
            int ny = cur->y + dcol[k];

            if (is_valid(nx, ny, n)) {
                if (cur->board[nx][ny].h == INT_MAX) continue; // water

                State* child = malloc(sizeof(State));
                *child = *cur; // copy state
                child->parent = cur;
                child->x = nx;
                child->y = ny;

                child->board[nx][ny].g = cur->board[cur->x][cur->y].g + 1;
                child->board[nx][ny].h = manhattan(nx, ny, tx, ty);

                push(&pq, child);
            }
        }
    }
    printf("No solution found!\n");
}

// ---------- Main ----------
int main() {
    int n, sx, sy, tx, ty;
    Cell grid[MAXN][MAXN];

    printf("Enter grid size (n): ");
    scanf("%d", &n);

    // initialize all cells
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++) {
            grid[r][c].g = INT_MAX;
            grid[r][c].h = 0;
        }

    printf("Enter source (x y): ");
    scanf("%d %d", &sx, &sy);
    grid[sx][sy].g = 0;

    printf("Enter destination (x y): ");
    scanf("%d %d", &tx, &ty);

    // mark obstacles
    char ch;
    do {
        int ox, oy;
        printf("Enter water cell (x y): ");
        scanf("%d %d", &ox, &oy);
        if (is_valid(ox, oy, n)) {
            grid[ox][oy].g = INT_MAX;
            grid[ox][oy].h = INT_MAX;
        }
        printf("More obstacles? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y');

    // precompute heuristics
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            if (grid[r][c].h != INT_MAX)
                grid[r][c].h = manhattan(r, c, tx, ty);

    // initial state
    State* start = malloc(sizeof(State));
    start->parent = NULL;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            start->board[r][c] = grid[r][c];
    start->x = sx;
    start->y = sy;

    a_star(start, n, tx, ty);

    return 0;
}
