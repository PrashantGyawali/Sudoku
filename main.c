#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include<stdlib.h>
#include "boarddisplay.c"

#define N 9

bool slow=true;



//finds the first empty cell in grid 
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

//checks if move is safe or not
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

// Solves the sudoku board, has choice for speed, and rendering or not as well as selected row and column(used for rendering)
bool solve_sudoku(int grid[N][N],int selected_cell_column,int selected_cell_row,int errorgrid[N][N],int initial_grid[N][N],bool slow,bool display) {
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
        if(display)
        {
            display_board(grid,selected_cell_column,selected_cell_row,errorgrid,initial_grid);
        }

        if (is_safe(grid, row, col, num)) {
            // If the digit is safe, place it
            grid[row][col] = num;
            // Recursively solve the remaining grid
            if (solve_sudoku(grid,selected_cell_column,selected_cell_row,errorgrid,initial_grid,slow,display)) {
                return true; // Found a solution
            }

            // If placing the digit leads to an incorrect solution, backtrack
            grid[row][col] = 0;
        }
    }

    // If no digit can be placed in the empty cell, backtrack
    return false;
}


void generateboard(int emptyboard[9][9])
{   
    int errorgrid[9][9]= {
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

    //PUTTING THE FIRST 12 ENTRIES
    int iterations=0;
    emptyboard[1][1]=rand()%10;
    emptyboard[4][5]=rand()%10;

    while(iterations<13)
    {
        int t=rand()%10;
        int r=rand()%10;
        int c=rand()%10;
        while(!is_safe(emptyboard,r,c,t))
        {
            t=rand()%10;
        }
        emptyboard[r][c]=t;
    iterations++;
    }

    //Giving ai to complete the remaining board
    solve_sudoku(emptyboard,0,0,errorgrid,emptyboard,false,false);

    //remove half of the digits
    for(int i=0;i<50;)
    {
        int r=rand()%10;
        int c=rand()%10;

        if(emptyboard[r][c]!=0)
        {
            emptyboard[r][c]=0;
            i++;
        }
    }
}


int main() {
    //take inputs is ai_allowed, hints_allowed , init_board
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
    int initial_grid[9][9]={
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

    int playing_grid[N][N];

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

        printf("\nGenerating New Board...");
        generateboard(initial_grid);
        copy_grid(initial_grid,playing_grid);

    int key;
    do {
        //makes the cursor jump from one end to other end
        selected_cell_row = selected_cell_row > (9 - 1) ? 0 : selected_cell_row;
        selected_cell_column = selected_cell_column > (9 - 1) ? 0 : selected_cell_column;
        selected_cell_row = selected_cell_row < 0 ? (9 - 1) : selected_cell_row;
        selected_cell_column = selected_cell_column < 0 ? (9 - 1) : selected_cell_column;

        //manual entry mode
        if(mode==2)
        {     
            check_board_show_Errors(playing_grid,errorgrid,initial_grid);
            display_board(playing_grid, selected_cell_row, selected_cell_column,errorgrid,initial_grid);
        }

        //algorithmic solving mode
        if(mode==1)
        {

            if(is_valid_board(errorgrid))
            {
                if (solve_sudoku(playing_grid,selected_cell_row,selected_cell_column,errorgrid,initial_grid,slow,true)) {
                    display_board(playing_grid,selected_cell_row,selected_cell_column,errorgrid,initial_grid);
                    printf("This is the required Sudoku solution\n");
                }
                else {
                    display_board(playing_grid,selected_cell_row,selected_cell_column,errorgrid,initial_grid);
                    printf("No solution exists.\n");
                }
            }
            else{
                display_board(playing_grid,selected_cell_row,selected_cell_column,errorgrid,initial_grid);
                printf("Not valid board.\n");
            }
            mode=2;
        }
        //

        
        fflush(stdin);
        key = getch();

        // handle numkeys   
        if (key >= 48 && key <= 57 && initial_grid[selected_cell_row][selected_cell_column]==0) 
        {  
            playing_grid[selected_cell_row][selected_cell_column] = key - 48;
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
