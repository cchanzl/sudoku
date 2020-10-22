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
  //check if position is out of range and locate sub-board
  int sb_row, sb_col;  //initilise top left hand corner of sub-board

  switch(position[0]){
  case 'A': case 'B': case 'C':
    sb_row = 0;
    break;
  case 'D': case 'E': case 'F':
    sb_row = 3;
    break;
  case 'G': case 'H': case 'I':
    sb_row = 6;
    break;
  default: return false;
  }

  switch(position[1]){
  case '1': case '2': case '3':
    sb_col = 0;
    break;
  case '4': case '5': case '6':
    sb_col = 3;
    break;
  case '7': case '8': case '9': 
    sb_col = 6;
    break;
  default: return false;
  }

  //check if a digit is already present in sub-board in that position
  for (int r = 0; r<=2; r++){
    for (int c = 0; c<=2; c++){
      if (board[sb_row+r][sb_col+c] == digit) return false;
    }
  }

  //convert position[] into int type for use in board[][]
  int row = static_cast<int>(position[0]) - 65;
  int col = static_cast<int>(position[1]) - 49;

  //check if there is already a move made in position
  if (board[row][col] != '.') return false;
    
  //check if digit is valid in its row and column
  for (int i = 0; i <= 8; i++){
    if (board[row][i] == digit) return false;
    if (board[i][col] == digit) return false;
  }

  //if all of the above checks are ok, assign digit to board
  board[row][col] = digit;

  return true;
}


/*answer to question 3*/
bool save_board(const char* filename, char board[9][9]) {
  ofstream out(filename);
  if (!out) {
    return false;
  }
  assert(out);

  for(int r = 0; r<9; r++){
    for(int c = 0; c<9; c++){
      out << board[r][c];
    }
    out << endl;
  }
  out.close();
  return true;
}


/*answer to question 4*/
bool solve_board(char board[9][9]){
  char board2[81][9];
  char interim_board[9][9];
  save_board("interim_board.dat", board);

  //step 1: create a secondary board to record possible moves
     
  for (int r = 0; r<=8; r++){
    for(int c = 0; c <=8; c++){ 
      int cell = r*9+c;   // cell reference for board2
      char position[2];
      position[0] = static_cast<char>(r + 65);  //convert to char to feed into make_move
      position[1] = static_cast<char>(c + 49);  //convert to char to feed into make_move

      for(int d =1; d<=9; d++){    //iterate through each possible digit
	load_board("interim_board.dat", interim_board);  //reloads board every iteration
	if( make_move(position, static_cast<char>(d-1+49), interim_board) ) board2[cell][d-1] = static_cast<char>(d-1+49);
	else board2[cell][d-1] = '.';
      }
    }
  }

  //to delete, to print out possible solutions for all 81 cells
  for (int r = 0; r<=8; r++){
    for(int c = 0; c <=8; c++){ 
      cout << "The possible solution for cell "<< r*9+c <<" is ";
      for(int z = 0; z<=8; z++){
	cout << board2[r*9+c][z];
      }
      cout << endl;
    }
  }

  //step 2: identify cells that has only 1 possible move and update the board

  display_board(board);
  
  for (int r = 0; r<=8; r++){
    for(int c = 0; c <=8; c++){
      int cell = r*9+c;
      int count = 0;  //start count of '.'
     
      for(int z = 0; z<=8; z++){
	if(board2[cell][z] == '.') count++;
      }
   
      if(count==8){
	for(int z = 0; z<=8; z++){
	  if(board2[cell][z] == '.');
	  else
	    board[r][c] = static_cast<char>(z+49);
	}
      }
    }
  }

  //step 3: check within each row if there is a cell with a unique solution

  char row_unique_digit[9][9];   //store unique digit for each row
  for (int r = 0; r<=8; r++){
    for(int z=0;z<=8;z++){
      int sum = 0;
      for(int c=0;c<=8;c++){
	int add = 0;
	if (board2[r*9+c][z] == '.') add = 0;
	else add = static_cast<int>(board2[r*9+c][z]) - 48; 
	sum += add;
      }
    
      if(sum == z+1)row_unique_digit[r][z] = static_cast<char>(z+49);
      else 
	row_unique_digit[r][z] = '.';
    }
    cout << row_unique_digit[r] << endl; //to check why there is \216^?
  }

  cout << endl; 
  for (int r = 0; r<=8; r++){
    for(int c = 0; c <=8; c++){
      for(int z = 0; z<=8; z++){
	if(board2[r*9+c][z]=='.');
	else if (board2[r*9+c][z]==row_unique_digit[r][z]){
	  board[r][c] = row_unique_digit[r][z];
	}
      }
    }
  }

  //step 4: check within each column if there is a cell with a unique solution

  
  
  //add final checking function to sum column, row and sub-boards!

  display_board(board);
  //solve_board(board);
  return is_complete(board);

}

