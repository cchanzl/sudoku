all:  main sudoku

main: main.cpp sudoku.h
	g++ -Wall -g main.cpp -o main

sudoku: sudoku.cpp sudoku.h
	g++ -Wall -g sudoku.cpp -o sudoku

clean: 
	rm -f main.o sudoku.o
