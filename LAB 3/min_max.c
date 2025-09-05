#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define n 3

typedef struct State {
    struct State* parent;
    char state_array[n][n];
    int score;
} State;

int get_score(char board[n][n]) {
    // Rows
    for (int i = 0; i < n; i++) {
        if (board[i][0] != '_' && 
            board[i][0] == board[i][1] && 
            board[i][1] == board[i][2]) {
            return (board[i][0] == 'X') ? 1 : -1;
        }
    }
    // Cols
    for (int i = 0; i < n; i++) {
        if (board[0][i] != '_' && 
            board[0][i] == board[1][i] && 
            board[1][i] == board[2][i]) {
            return (board[0][i] == 'X') ? 1 : -1;
        }
    }
    // Diagonals
    if (board[0][0] != '_' && 
        board[0][0] == board[1][1] && 
        board[1][1] == board[2][2]) {
        return (board[0][0] == 'X') ? 1 : -1;
    }
    if (board[0][2] != '_' && 
        board[0][2] == board[1][1] && 
        board[1][1] == board[2][0]) {
        return (board[0][2] == 'X') ? 1 : -1;
    }
    return 0;
}

int moves_left(char board[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == '_') return 1;
        }
    }
    return 0;
}

int generate_tree(State* s, int depth, int is_max) {
    int score = get_score(s->state_array);
    if (score == 1 || score == -1) return score;
    if (!moves_left(s->state_array)) return 0;

    char board[n][n];
    memcpy(board, s->state_array, sizeof(board));

    if (is_max) { // AI's turn (X)
        int best = INT_MIN;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = 'X';
                    State child = {s, {{0}}, score};
                    memcpy(child.state_array, board, sizeof(board));
                    best = (best > generate_tree(&child, depth + 1, 0)) ? best : generate_tree(&child, depth + 1, 0);
                    board[i][j] = '_'; // undo move
                }
            }
        }
        return best;
    } else { // Human's turn (O)
        int best = INT_MAX;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = 'O';
                    State child = {s, {{0}}, score};
                    memcpy(child.state_array, board, sizeof(board));
                    int val = generate_tree(&child, depth + 1, 1);
                    best = (best < val) ? best : val;
                    board[i][j] = '_'; // undo move
                }
            }
        }
        return best;
    }
}

int* find_best_move(State* s) {
    int best_val = INT_MIN;
    int best_move_x = -1, best_move_y = -1;
    char board[n][n];
    memcpy(board, s->state_array, sizeof(board));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == '_') {
                board[i][j] = 'X';
                State child = {s, {{0}}, s->score};
                memcpy(child.state_array, board, sizeof(board));
                int move_val = generate_tree(&child, 0, 0);
                board[i][j] = '_'; // undo

                if (move_val > best_val) {
                    best_val = move_val;
                    best_move_x = i;
                    best_move_y = j;
                }
            }
        }
    }
    int* move = (int*)malloc(2 * sizeof(int));
    move[0] = best_move_x;
    move[1] = best_move_y;
    return move;
}

void print_board(char board[n][n]) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void tic_tac_toe(State* s) {
    int winner = 0;
    while (1) {
        // AI Move
        int* best_move = find_best_move(s);
        int x = best_move[0], y = best_move[1];
        free(best_move);

        if (x != -1 && y != -1) {
            s->state_array[x][y] = 'X';
            printf("AI plays at: %d %d\n", x, y);
        }

        print_board(s->state_array);
        winner = get_score(s->state_array);
        if (winner != 0 || !moves_left(s->state_array)) break;

        // Human Move
        int hx, hy;
        printf("Enter your move (row col): ");
        scanf("%d %d", &hx, &hy);

        if (hx >= 0 && hx < n && hy >= 0 && hy < n && s->state_array[hx][hy] == '_') {
            s->state_array[hx][hy] = 'O';
        } else {
            printf("Invalid move. Try again.\n");
            continue; // repeat this turn
        }

        print_board(s->state_array);
        winner = get_score(s->state_array);
        if (winner != 0 || !moves_left(s->state_array)) break;
    }

    if (winner == 1) printf("AI (X) wins!\n");
    else if (winner == -1) printf("You (O) win!\n");
    else printf("Draw!\n");
}

int main() {
    char board[n][n] = {
        {'_', '_', '_'},
        {'_', '_', '_'},
        {'_', '_', '_'}
    };

    State* s = (State*)malloc(sizeof(State));
    s->parent = NULL;
    memcpy(s->state_array, board, sizeof(board));
    s->score = 0;

    printf("Tic Tac Toe - You (O) vs AI (X)\n");
    print_board(s->state_array);

    tic_tac_toe(s);

    free(s);
    return 0;
}
