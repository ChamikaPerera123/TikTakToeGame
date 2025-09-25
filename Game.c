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
