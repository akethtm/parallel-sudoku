// Parallelized by Aketh

#include <iostream>
#include <fstream>
#include "checkfns.h"
#include <omp.h>
#define ORDER 9

using namespace std;

//int sudoku[ORDER][ORDER] = {0};
int isClueGiven[ORDER][ORDER] = {0};
int prevPosition[ORDER][ORDER][2];

int placeNum(int row, int column);


void print(int matrix[ORDER][ORDER])
{
  for (int i = 0; i < ORDER; i++) {
    for (int j = 0; j < ORDER; j++)
      cout << matrix[i][j] << " ";
    cout << endl;
  }
    
  cout << endl;
  return;
}


void storePositions(int sudoku[ORDER][ORDER])  /* probably stores the next position to be solved */
{
  int temprow, tempcolumn;
  temprow = -1;
  tempcolumn = -1;
    
  for (int row = 0; row < 9; row++) {
    for (int column = 0; column < 9; column++) {
      if (isClueGiven[row][column] == 0) {
	prevPosition[row][column][0] = temprow;    /* previous position is stored and set zero for first one.why? */
	prevPosition[row][column][1] = tempcolumn; 
	temprow = row;
	tempcolumn = column;
      }
    }
  }
}


int goBack(int sudoku[ORDER][ORDER],int &row, int &column)
{
  int trow, tcolumn;
  
  if (row == 0 && column == 0)
    return 0;
  sudoku[row][column] = 0;
    
  trow = prevPosition[row][column][0];
  tcolumn = prevPosition[row][column][1];
  tcolumn -= 1;
    
  row = trow;
  column = tcolumn;
    
  return 1;
}


int placeNum(int sudoku[ORDER][ORDER],int row, int column)
{

  if(isClueGiven[row][column] == 1)
    return 1;

  for (int num = sudoku[row][column] + 1; num <= 9; num++) {

    if (checkRow(sudoku,row,num) && checkColumn(sudoku,column, num) && checkSquare(sudoku,row,column,num) ) {
      sudoku[row][column] = num;
      return 1;
    }
  }
     
  sudoku[row][column] = 0;
    
  return 0;
}


int solveSudoku(int sudoku[ORDER][ORDER], int start_num)
{
 
  long double start_time,end_time;
  //start_time = omp_get_wtime();
   
  
  for (int row = 0; row < 9; row++) {
    for (int column = 0; column < 9; column++) {
      if (!placeNum(sudoku,row, column))  // if I cannot place a number go back.
      {
	sudoku[row][column] = 0;
	if (!goBack(sudoku,row, column)) return 0;
      }
    }
  }

  //end_time = omp_get_wtime();
  //printf("time here is %LG \n ",end_time - start_time);
  return 1;
}


int main(int argc, char* argv[])
{

  int sudoku[ORDER][ORDER] = {0}, seed;
  int first_zero_row,first_zero_column;
  bool breakpoint;

  fstream file;
   
  if (argc == 2) 
    {
      file.open(argv[1], ios::in);
    
      if (file.is_open()) 
	{
	  for (int row = 0; row < ORDER; row++) {
	    for (int column = 0; column < ORDER; column++) {
	      file >> sudoku[row][column];
	      if (sudoku[row][column] !=0)
		isClueGiven[row][column] = 1;
	    }
	  }
	  print (sudoku);
	}  else
    cout << "Could not locate file ' " << argv[1] << "'. Enter elements manually" << endl;
    }
  
  if (argc > 2)
    cout << "More than one arguments. Enter elements manually\n";

  if (!file.is_open() ) {
    cout <<"Enter 81  elements (0s for cells without clues) :" << endl;

    for ( int row = 0; row < ORDER; row++) {
      for ( int column = 0; column < ORDER; column++) {
	cin >> sudoku[row][column];
	if (sudoku[row][column] !=0)
	  isClueGiven[row][column] = 1;
      }
    }

    print (sudoku);
  }
  
  for( int row = 0; row < ORDER; row++) {
    if(breakpoint) break; 
    for(int column = 0; column < ORDER; column++ ){
 
           if(sudoku[row][column] == 0) 
               {
                    first_zero_row = row; 
                    first_zero_column = column; 
                    breakpoint = true; 
                    break;
                }
                                             
        }
     } 

    //cout << "first_zero_row,first_zero_column are "<< first_zero_row << " and " << first_zero_column << endl;
    //cout << endl;

    storePositions(sudoku);
    #pragma omp parallel for default(shared)firstprivate(sudoku,isClueGiven,prevPosition)num_threads(2)
    for(seed=1;seed<=9;seed++)
       {            
              sudoku[first_zero_row][first_zero_column] = seed;
              for (int row = 0; row < ORDER; row++) {
                  for (int column = 0; column < ORDER; column++) {
                       if (sudoku[row][column] !=0) 
                           {
                              isClueGiven[row][column] = 1;
                           }
                  }
               }
       solveSudoku(sudoku,seed);
       print(sudoku); 
       }
    print(sudoku); 
     return 0;
}
