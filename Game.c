#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

char** initializeBoard(int n);
void displayBoard(char** board, int n);
bool isValidMove(char** board, int n, int row, int col);
//void makeMove(char** board, int n, int row, int col, char player);
bool checkWin(char** board,int n, char player);
bool checkDraw(char** board,int n);
void logBoard(FILE* logFile, char** board, int n);
void freeBoard(char** board, int n);
void computerMove(char** board, int n, int* row, int* col);

int main() {
    int n, mode;
    printf("Enter board size (3-10): ");
    scanf("%d", &n);

    if (n < 3 || n > 10) {
        printf("Invalid board size!\n");
        return 1;
    }
    printf("Choose game mode:\n");
    printf("1. User vs User\n");
    printf("2. User vs Computer\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    // Initialize board
    char** board = initializeBoard(n);

    // Open log file
    FILE* logFile = fopen("tictactoe_log.txt", "w");
    if (!logFile) {
        printf("Error opening log file!\n");
        freeBoard(board, n);
        return 1;
    }

    srand(time(NULL));

    int moves = 0; //maxMoves = n * n;
    char currentPlayer = 'X';
    int row, col;

    while (true) {
        displayBoard(board, n);
        
        if (mode == 1 || currentPlayer == 'X') {
            // User input
            printf("Player %c, enter your move (row col): ", currentPlayer);
            scanf("%d %d", &row, &col);

            if (!isValidMove(board, n, row, col)) {
                printf("Invalid move! Try again.\n");
                continue;
            }
        } else {
            // Computer move
            computerMove(board, n, &row, &col);
            printf("Computer chooses: %d %d\n", row, col);
        }

        board[row][col] = currentPlayer;
        moves++;

        // Log board state
        logBoard(logFile, board, n);

        if (checkWin(board, n, currentPlayer)) {
            displayBoard(board, n);
            if (mode == 2 && currentPlayer == 'O')
                printf("Computer wins!\n");
            else
                printf("Player %c wins!\n", currentPlayer);
            break;
        }
        if (checkDraw(board, n)) {
            displayBoard(board, n);
            printf("It's a draw!\n");
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    fclose(logFile);
    freeBoard(board, n);
    return 0;
}

// Initialize game board dynamically
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

// Display game board
void displayBoard(char** board, int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf(" %c ", board[i][j]);
            if (j < n - 1) printf("|");
        }
        printf("\n");
        if (i < n - 1) {
            for (int k = 0; k < n; k++) printf("--- ");
            printf("\n");
        }
    }
    printf("\n");
}

// Validate move
bool isValidMove(char** board, int n, int row, int col) {
    if (row < 0 || row >= n || col < 0 || col >= n) return false;
    if (board[row][col] != ' ') return false;
    return true;
}

// Check win condition
bool checkWin(char** board, int n, char player) {
    // Check rows
    for (int i = 0; i < n; i++) {
        bool win = true;
        for (int j = 0; j < n; j++) {
            if (board[i][j] != player) { win = false; break; }
        }
        if (win) return true;
    }

    // Check columns
    for (int j = 0; j < n; j++) {
        bool win = true;
        for (int i = 0; i < n; i++) {
            if (board[i][j] != player) { win = false; break; }
        }
        if (win) return true;
    }

    // Check main diagonal
    bool win = true;
    for (int i = 0; i < n; i++) {
        if (board[i][i] != player) { win = false; break; }
    }
    if (win) return true;

    // Check anti-diagonal
    win = true;
    for (int i = 0; i < n; i++) {
        if (board[i][n - i - 1] != player) { win = false; break; }
    }
    if (win) return true;

    return false;
}

// Check draw condition
bool checkDraw(char** board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

// Log board state to file
void logBoard(FILE* logFile, char** board, int n) {
    fprintf(logFile, "\nBoard State:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(logFile, " %c ", board[i][j]);
            if (j < n - 1) fprintf(logFile, "|");
        }
        fprintf(logFile, "\n");
        if (i < n - 1) {
            for (int k = 0; k < n; k++) fprintf(logFile, "--- ");
            fprintf(logFile, "\n");
        }
    }
    fprintf(logFile, "\n");
}

// Free dynamically allocated memory
void freeBoard(char** board, int n) {
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
}

// Generate random computer move
void computerMove(char** board, int n, int* row, int* col) {
    do {
        *row = rand() % n;
        *col = rand() % n;
    } while (!isValidMove(board, n, *row, *col));
} 

       
