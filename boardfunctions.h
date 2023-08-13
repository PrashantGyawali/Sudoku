#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
#include <time.h>
#include "types.h"
#define N 9

//displays each cell with proper coloring
void display_cell(int value, int isSelected, int errored,int initial) {
if (isSelected) {
    if (value != 0) {
        printf("\033[97;107m %d \033[0m", value);
    } else {
        printf("\033[97;107m   \033[0m");
    }
} else {
    if (value != 0) {
        if (initial == 1) {
            printf("\033[0;34m %d \033[0m", value); // Blue color for initial value
        } else if (errored == 1) {
            printf("\033[0;31m %d \033[0m", value); // Red color for errored value
        } else {
            printf(" %d ", value);
        }
    } else {
        printf("   ");
    }
}
}

//clears the screen
void clearScreen() {
    system("cls");
}

//displays the entire board
void display_board(Board elements, int selected_cell_row, int selected_cell_column, Board errorblock,Board initial_grid) 
{
    clearScreen();
    int i, j;
    printf("\033[1m+===+===+===+===+===+===+===+===+===+\033[0m\n");
    for (i = 0; i < 9; i++) {
        for (j = 0; j <= 9-1; j++) {
            if (j % 3 == 0) {
                printf("\033[1m|\033[0m");
                printf("");
                display_cell(elements[i][j], i == selected_cell_row && j == selected_cell_column,errorblock[i][j]==1,initial_grid[i][j]!=0);
            }
            else {
                printf(":");
                display_cell(elements[i][j], i == selected_cell_row && j == selected_cell_column,errorblock[i][j]==1,initial_grid[i][j]!=0);
            }

            if(j==9-1)
            {
                printf("\033[1m|\033[0m");
            }
        }
        printf("\n");
        for (j = 0; j < 9; j++) {
            if (j == 0) {
                if (i % 3 == 2) {
                    printf("\033[1m+===+\033[0m");
                } else {
                    printf("+---+");
                }
            } 
            else {
                if (i % 3 == 2) {
                    printf("\033[1m===+\033[0m");
                } else {
                    printf("---+");
                }
            }
        }
        printf("\n");
    }
}

bool is_valid_board(int errorgrid[9][9]){
    for (int i=0;i<9; i++)
    {
        for(int j=0;j<9;j++)
        {
            if(errorgrid[i][j]!=0)
            {
                return false;
            }
        }
    }
    return true;
}

//checks the board with the initial board and finds duplicate elements and updates the error board
void check_board_show_Errors(Board a,Board errorblocks,Board initial_grid)
{   int i,j;

    //clear the previous error tracker array 
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            errorblocks[i][j]=0;
        }
    }

    //check the columns for duplicates
    int coldups[9]={0,0,0,0,0,0,0,0,0};
    for(j=0;j<9;j++) 
        {
            //first check all the initial grid elements
            for(i=0;i<9;i++)
            {
                if(initial_grid[i][j]!=0)
                {
                coldups[initial_grid[i][j]-1]++;
                }
            }
            //then move on to other elements (Prevents initial elements from being marked as duplicate)
            for(i=0;i<9;i++)
            {
                if(a[i][j]>0 && initial_grid[i][j]==0)
                {
                    coldups[a[i][j]-1]++;
                    if(coldups[a[i][j]-1]>1) //contains duplicate means updating the errorarray to colour the other dups with red color
                    {
                        errorblocks[i][j]=1;
                    };
                }
            }
        
        //clear the col dups for checking next column
        for(i=0;i<9;i++)
        {
            coldups[i]=0;
        }
        }
        
//check the rows
int rowdups[9]={0,0,0,0,0,0,0,0,0};
for(i=0;i<9;i++)
{
    //first check all the initial grid elements
    for(j=0;j<9;j++)
    {
        if(initial_grid[i][j]!=0)
        {
        rowdups[initial_grid[i][j]-1]++;
        }
    }

    //then move on to other elements (Prevents initial elements from being marked as duplicate)
    for(j=0;j<9;j++)
    {
        if(a[i][j]>0 && initial_grid[i][j]==0)
        {
            rowdups[a[i][j]-1]++;
            if(rowdups[a[i][j]-1]>1)     //contains duplicate means updating the errorarray to colour the other dups with red color
            {
                errorblocks[i][j]=1;
            };
        }
    }

    //clear the row dups array for checking next row 
    for(j=0;j<9;j++)
    {
        rowdups[j]=0;
    }
}

//check all the squares
    int sqdups[9]={0,0,0,0,0,0,0,0,0};

    int row=0,col=0;

    for(row=0;row<9;row+=3)
    {   
        for(col=0;col<9;col+=3)
        {  
            //check the initial grid elements
            for(i=row;i<row+3;i++)
            {
                for(j=col;j<col+3;j++)
                {
                    if(initial_grid[i][j]!=0)
                    {
                    sqdups[initial_grid[i][j]-1]++;
                    }
                }
            }

            //check the normal elements
            for(i=row;i<row+3;i++)
            {
                    for(j=col;j<col+3;j++)
                    {
                        if(a[i][j]>0 && initial_grid[i][j]==0)
                        {
                            sqdups[a[i][j]-1]++;
                            if(sqdups[a[i][j]-1]>1) //contains duplicate means updating the errorarray to colour the other dups with red color
                            {
                                errorblocks[i][j]=1;
                            };
                        }
                    }
            }

            //empty the previous array for checking next square
            for(i=0;i<9;i++)
            {
                sqdups[i]=0;
            }
        } 

    }
}

bool completevalid(Board a)
{
    int row_sum=0;
    int row_product=1;
    int col_sum=0;
    int col_product=1;
    //check 
    for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
            row_sum+=a[i][j];
            row_product*=a[i][j];
            col_sum+=a[j][i];
            col_product*=a[j][i];
            }
        }
    if(row_sum!=45 ||col_sum!=45||row_product!=362880 ||col_product!=362880)
    {
        return false;
    }

    for(int row=0;row<9;row+=3)
    {   
        for(int col=0;col<9;col+=3)
        { int sum=0,product=1;
            for(int i=row;i<row+3;i++)
            {
                    for(int j=col;j<col+3;j++)
                    {
                        sum+=a[i][j];
                        product*=a[i][j];
                    }
            }
            if(sum!=45 || product!=362880)
            {
                return false;
            }
        } 
    }

    return true;
}

//copies grid from source to destination
void copy_grid(Board src,Board destination)
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            destination[i][j]=src[i][j];
        }
    }
}

//finds the first empty cell in grid 
bool find_empty_cell(Board grid, int *row, int *col) {
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
bool is_safe(Board grid, int row, int col, int num) {

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
bool solve_sudoku(Board grid,int selected_cell_column,int selected_cell_row,Board errorgrid,Board initial_grid,bool slow,bool display) {
    int row, col;
    // Find an empty cell (0) in the grid
    if (!find_empty_cell(grid, &row, &col)) {
        return true; // No empty cells, Sudoku is solved
    }



    // Try placing digits from 1 to 9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        if (is_safe(grid, row, col, num)) {
            // If the digit is safe, place it
            grid[row][col] = num;

            if(display)
            {
                display_board(grid,selected_cell_column,selected_cell_row,errorgrid,initial_grid);
            }

            if(slow)
            {
                if(row<3)
                sleep(10);
                else{
                    sleep(200/(9-row));
                }
            }

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

//generates a new board
void generateboard(Board emptyboard)
{   
    Board errorgrid = {
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
    srand(time(NULL));
    int iterations=0;
    emptyboard[0][0]=rand()%10;
    emptyboard[3][3]=rand()%10;

    while(iterations<13)
    {
        srand(time(NULL));
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
    for(int i=0;i<54;)
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




