#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

char** initializeBoard(int n);
void displayBoard(char** board, int n);
bool isValidMove(char** board, int n, int row, int col);
void makeMove(char** board, int n, int row, int col, char player);
bool checkWin(char** board,int n, char player);
bool checkDraw(char** board,int n);
void logBoard(FILE* logFile, char** board, int n);

int main() {
    int n, row, col;
    char player = 'X';
    FILE* logFile = fopen("tictactoe_log.txt", "w");

    printf("Enter board size (3-10): ");
    scanf("%d", &n);

    if (n < 3 || n > 10) {
        printf("Invalid size. Exiting.\n");
        return 1;
    }

    // Dynamic allocation of board
    char** board = initializeBoard(n);

    int moves = 0;
    while (true) {
        displayBoard(board, n);
        printf("Player %c, enter your move (row and column): ", player);
        scanf("%d %d", &row, &col);

        if (!isValidMove(board, n, row, col)) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        makeMove(board, row, col, player);
        moves++;

        // Log current state
        logBoard(logFile, board, n);

        if (checkWin(board, n, player)) {
            displayBoard(board, n);
            printf("Player %c wins!\n", player);
            break;
        }

        if (checkDraw(board, n)) {
            displayBoard(board, n);
            printf("It's a draw!\n");
            break;
        }

        // Switch player
        player = (player == 'X') ? 'O' : 'X';
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);

    fclose(logFile);
    return 0;
}

// Initialize the game board
char** initializeBoard(int n) {
    char** board = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        board[i] = (char*)malloc(n * sizeof(char));
        for (int j = 0; j < n; j++) {
            board[i][j] = ' ';
        }
    }
    return board;
}

// Display the game board
void displayBoard(char** board, int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf(" %c ", board[i][j]);
            if (j < n - 1) printf("|");
        }
        printf("\n");
        if (i < n - 1) {
            for (int j = 0; j < n; j++) {
                printf("---");
                if (j < n - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

// Check if move is valid
bool isValidMove(char** board, int n, int row, int col) {
    return (row >= 0 && row < n && col >= 0 && col < n && board[row][col] == ' ');
}

// Place the move
void makeMove(char** board, int row, int col, char player) {
    board[row][col] = player;
}

// Check win condition
bool checkWin(char** board, int n, char player) {
    // Check rows
    for (int i = 0; i < n; i++) {
        bool win = true;
        for (int j = 0; j < n; j++) {
            if (board[i][j] != player) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }

    // Check columns
    for (int j = 0; j < n; j++) {
        bool win = true;
        for (int i = 0; i < n; i++) {
            if (board[i][j] != player) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }

    // Check main diagonal
    bool win = true;
    for (int i = 0; i < n; i++) {
        if (board[i][i] != player) {
            win = false;
            break;
        }
    }
    if (win) return true;

    // Check anti-diagonal
    win = true;
    for (int i = 0; i < n; i++) {
        if (board[i][n - 1 - i] != player) {
            win = false;
            break;
        }
    }
    if (win) return true;

    return false;
}

// Check draw
bool checkDraw(char** board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

// Log the current board to file
void logBoard(FILE* logFile, char** board, int n) {
    fprintf(logFile, "\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(logFile, " %c ", board[i][j]);
            if (j < n - 1) fprintf(logFile, "|");
        }
        fprintf(logFile, "\n");
        if (i < n - 1) {
            for (int j = 0; j < n; j++) {
                fprintf(logFile, "---");
                if (j < n - 1) fprintf(logFile, "+");
            }
            fprintf(logFile, "\n");
        }
    }
    fprintf(logFile, "\n");
}

