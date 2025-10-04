#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 10

char **board;
int N;
FILE *logFile;

void initBoard() {
    board = (char **)malloc(N * sizeof(char *));
    for(int i = 0; i < N; i++) {
        board[i] = (char *)malloc(N * sizeof(char));
        for(int j = 0; j < N; j++)
            board[i][j] = ' ';
    }
}


void displayBoard() {
    printf("\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf(" %c ", board[i][j]);
            if(j < N-1) printf("|");
        }
        printf("\n");
        if(i < N-1) {
            for(int j = 0; j < N; j++) {
                printf("---");
                if(j < N-1) printf("|");
            }
            printf("\n");
        }
    }
    printf("\n");
}


int checkWin(char symbol) {
    
    for(int i = 0; i < N; i++) {
        int row = 1, col = 1;
        for(int j = 0; j < N; j++) {
            if(board[i][j] != symbol) row = 0;
            if(board[j][i] != symbol) col = 0;
        }
        if(row || col) return 1;
    }
    
    int diag1 = 1, diag2 = 1;
    for(int i = 0; i < N; i++) {
        if(board[i][i] != symbol) diag1 = 0;
        if(board[i][N-i-1] != symbol) diag2 = 0;
    }
    return (diag1 || diag2);
}


int checkDraw() {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(board[i][j] == ' ') return 0;
    return 1;
}


void playerMove(char symbol) {
    int row, col;
    do {
        printf("Enter row and column (0-%d): ", N-1);
        scanf("%d %d", &row, &col);
    } while(row < 0 || row >= N || col < 0 || col >= N || board[row][col] != ' ');
    board[row][col] = symbol;
    fprintf(logFile, "Player (%c) played at %d,%d\n", symbol, row, col);
}


void computerMove(char symbol) {
    int row, col;
    do {
        row = rand() % N;
        col = rand() % N;
    } while(board[row][col] != ' ');
    board[row][col] = symbol;
    printf("Computer (%c) played at %d,%d\n", symbol, row, col);
    fprintf(logFile, "Computer (%c) played at %d,%d\n", symbol, row, col);
}

void freeBoard() {
    for(int i = 0; i < N; i++)
        free(board[i]);
    free(board);
}

int main() {
    srand(time(0));
    logFile = fopen("tictactoe_log.txt", "w");

    printf("Enter board size (3-10): ");
    scanf("%d", &N);
    if(N < 3 || N > MAX) {
        printf("Invalid size!\n");
        return 0;
    }

    initBoard();

    int mode;
    printf("Select Game Mode:\n");
    printf("1. User vs User (2 players)\n");
    printf("2. User vs Computer (2 players)\n");
    printf("3. Multi-Player (3 players)\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    char players[3] = {'X','O','Z'};
    int isComputer[3] = {0,0,0}; 
    int totalPlayers = (mode == 3 ? 3 : 2);

    if(mode == 1) {
        printf("Mode: User vs User.\n");
    }
    else if(mode == 2) {
        printf("Mode: User vs Computer.\n");
        isComputer[1] = 1; 
    }
    else if(mode == 3) {
        printf("Mode: Multi-Player (3 players).\n");
        printf("Configure each player (0=Human, 1=Computer):\n");
        for(int i = 0; i < 3; i++) {
            printf("Player %d (%c): ", i+1, players[i]);
            scanf("%d", &isComputer[i]);
        }
    }
    else {
        printf("Invalid choice!\n");
        return 0;
    }

    int turn = 0;
    while(1) {
        displayBoard();
        int current = turn % totalPlayers;
        printf("Turn %d: Player %d (%c)\n", turn+1, current+1, players[current]);

        if(isComputer[current])
            computerMove(players[current]);
        else
            playerMove(players[current]);

        if(checkWin(players[current])) {
            displayBoard();
            printf("Player %d (%c) wins!\n", current+1, players[current]);
            fprintf(logFile, "Player %d (%c) wins!\n", current+1, players[current]);
            break;
        }
        if(checkDraw()) {
            displayBoard();
            printf("Game is a draw!\n");
            fprintf(logFile, "Game is a draw!\n");
            break;
        }
        turn++;
    }

    fclose(logFile);
    freeBoard();
    return 0;
}
