#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include<stdlib.h>
#include "boarddisplay.c"

#define N 9

bool slow=true;

bool find_empty_cell(int grid[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (grid[*row][*col] == 0) {
                return true; // Found an empty cell
            }
        }
    }
    return false; // No empty cell found
}

bool is_safe(int grid[N][N], int row, int col, int num) {

    // Check if 'num' is not present in the current row, column, and box

    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}



bool solve_sudoku(int grid[N][N],int selected_cell_column,int selected_cell_row,int errorgrid[N][N],bool slow) {
    int row, col;
    // Find an empty cell (0) in the grid
    if (!find_empty_cell(grid, &row, &col)) {
        return true; // No empty cells, Sudoku is solved
    }

    if(slow)
    {sleep(100);
    }

    // Try placing digits from 1 to 9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        displayBoard(grid,selected_cell_column,selected_cell_row,errorgrid);

        if (is_safe(grid, row, col, num)) {
            // If the digit is safe, place it
            grid[row][col] = num;
            // Recursively solve the remaining grid
            if (solve_sudoku(grid,selected_cell_column,selected_cell_row,errorgrid,slow)) {
                return true; // Found a solution
            }

            // If placing the digit leads to an incorrect solution, backtrack
            grid[row][col] = 0;
        }
    }

    // If no digit can be placed in the empty cell, backtrack
    return false;
}

int main() {
    int mode=2;
    int selected_cell_row = 4, selected_cell_column = 4;

    printf("Sudoku game\n How to play?:\n");
    printf("Press 'a' to use ai solver in game\n");
    printf("Press 'b' to enter manually in game\n");
    printf("Navigate using arrow keys\n");
    printf("Enter 0 to clear the number\n");
    printf("Enter Esc to quit\n");
    printf("Press any key to continue");
    getch();
    //initial grid
    int sudokuGrid[N][N] = {
        {5, 3, 0, 6, 0, 8, 9, 0, 2},
        {6, 0, 2, 1, 0, 5, 0, 4, 0},
        {1, 0, 0, 3, 4, 2, 5, 0, 7},
        {0, 0, 0, 0, 6, 1, 4, 0, 3},
        {4, 0, 6, 8, 0, 0, 7, 0, 0},
        {7, 0, 0, 9, 2, 0, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 0, 0},
        {2, 8, 0, 4, 1, 9, 0, 3, 5},
        {3, 4, 0, 2, 8, 0, 1, 0, 0}
    };

    //used for coloring the duplicate numbers. if duplicate the 0 changes to 1
    int errorgrid[N][N]= 
        {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
        };




    int key;
    do {
        //makes the cursor jump from one end to other end
        selected_cell_row = selected_cell_row > (BOARDSIZE - 1) ? 0 : selected_cell_row;
        selected_cell_column = selected_cell_column > (BOARDSIZE - 1) ? 0 : selected_cell_column;
        selected_cell_row = selected_cell_row < 0 ? (BOARDSIZE - 1) : selected_cell_row;
        selected_cell_column = selected_cell_column < 0 ? (BOARDSIZE - 1) : selected_cell_column;

        //manual entry mode
        if(mode==2)
        {     
            checkBoardShowErrors(sudokuGrid,errorgrid);
            displayBoard(sudokuGrid, selected_cell_row, selected_cell_column, errorgrid);
        }

        //algorithmic solving mode
        if(mode==1)
        {
            if(validboard(errorgrid))
            {
                if (solve_sudoku(sudokuGrid,selected_cell_row,selected_cell_column,errorgrid,slow)) {
                    displayBoard(sudokuGrid,selected_cell_row,selected_cell_column,errorgrid);
                    printf("This is the required Sudoku solution\n");
                }
                else {
                    displayBoard(sudokuGrid,selected_cell_row,selected_cell_column,errorgrid);
                    printf("No solution exists.\n");
                }
            }
            else{
                displayBoard(sudokuGrid,selected_cell_row,selected_cell_column,errorgrid);
                printf("Not valid board.\n");
            }
            mode=2;
        }
        //

        
        fflush(stdin);
        key = getch();

        // handle numkeys   
        if (key >= 48 && key <= 57) 
        {  
            sudokuGrid[selected_cell_row][selected_cell_column] = key - 48;
        }

        //handle arrwokeys
        if (key == 0 || key == 224) {
            key = getch(); // Extended key code

            if (key == 72) { // Up arrow
                selected_cell_row--;
            } else if (key == 80) { // Down arrow
                selected_cell_row++;
            } else if (key == 77) { // Right arrow
                selected_cell_column++;
            } else if (key == 75) { // Left arrow
                selected_cell_column--;
            }
        }

        if(key==97)
        {
            mode=1;
        }
        if(key==98)
        {
            mode=2;
        }

    } while (key != 27);



    return 0;
}
