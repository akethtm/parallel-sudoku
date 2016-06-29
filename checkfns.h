#ifndef CHECKFNS_H
#define CHECKFNS_H
#define ORDER 9

int checkRow(int sudoku[ORDER][ORDER], int row, int num); 
int checkColumn(int sudoku[ORDER][ORDER], int column, int num);
int checkSquare(int sudoku[ORDER][ORDER], int row, int column, int num);
int checkSolution(int sudoku[ORDER][ORDER]) ;

#endif /* CHECKS_H */
