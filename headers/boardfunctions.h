#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include "types.h"
#include "sleep.h"

#ifndef __BOARD_FUNCTIONS__ // Check if Game struct is not defined
#define __BOARD_FUNCTIONS__ // Define it to prevent redefinition

#define N 9

//displays each cell with proper coloring
void display_cell(int value, int isSelected, int errored,int initial);

//clears the screen
void clearScreen();

//displays the entire board
void display_board(Board elements, int selected_cell_row, int selected_cell_column, Board errorblock, Board initial_grid);

bool is_valid_board(int errorgrid[9][9]);

//checks the board with the initial board and finds duplicate elements and updates the error board
void check_board_show_Errors(Board a,Board errorblocks,Board initial_grid);

bool completevalid(Board a, Board errorboard);

//copies grid from source to destination
void copy_grid(Board src,Board destination);

//finds the first empty cell in grid 
bool find_empty_cell(Board grid, int *row, int *col);

//checks if move is safe or not
bool is_safe(Board grid, int row, int col, int num);

// Solves the sudoku board, has choice for speed, and rendering or not as well as selected row and column(used for rendering)
bool solve_sudoku(Board grid,int selected_cell_column,int selected_cell_row,Board errorgrid,Board initial_grid,int slow, int display);

//generates a new board
void generateboard(Board emptyboard);

#endif // __BOARD_FUNCTIONS__

