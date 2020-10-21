#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!" << '\n';
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+" << '\n';
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/*answer to question 1*/
bool is_complete(const char board[9][9]) {
  for ( int r = 0; r<9; r++){
    for (int c = 0; c<9; c++){
      //isdigit checks whether each position has a digit
      if(!isdigit(board[r][c]))return false; 
    }
  }
  return true;
}



/*answer to question 2*/
bool make_move(const char position[2], char digit, char board [9][9]){
  //checks if position is out of range
  switch(position[0]){
  case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I':;
      break;
  default: return false;
  }

  switch(position[1]){
  case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':;
      break;
  default: return false;
  }

  //convert position[] into int type for use in board[]
  int row = static_cast<int>(position[0]) - 65;
  int col = static_cast<int>(position[1]) - 49;

  //checks if there is already a move made in position
  //if ( board[row][col] != ' ') return false;
  
  //checks if digit is valid in its column
  for ( int i = 0; i <= 8; i++){
    if (board[row][i] == digit) return false;
  }
  //checks if digit is valid in its row
  for ( int i = 0; i <= 8; i++){
    if (board[i][col] == digit) return false;
  }
  //checks if digit is valid in its sub-board


  //if all of the above checks are ok
  board[row][col] = digit;

  return true;
}



/*answer to question 3*/






/*answer to question 4*/
