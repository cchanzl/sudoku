#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(const char board[9][9]);
bool make_move(const char position[2], char digit, char board [9][9]);
bool save_board(const char* filename, char board[9][9]);
bool solve_board(char board[9][9]);
void copyarray(char array1[9][9], char array2[9][9]);
bool is_numeric(const char board[9][9]);
bool is_valid(const char board[9][9]);

#endif
