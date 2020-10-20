execute:  main.cpp sudoku.cpp
	g++ -g main.cpp sudoku.cpp -o execute

clean:
	rm -f *.o execute
