execute:  main.o sudoku.o
	g++ -g main.o sudoku.o -o execute

main.o: main.cpp sudoku.h
	g++ -Wall -g -c main.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -Wall -g -c sudoku.cpp

clean:
	rm -f *.o execute
