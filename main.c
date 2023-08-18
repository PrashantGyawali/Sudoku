#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include<stdlib.h>
#include "./headers/boardfunctions.h"
#include "keys.c"
#include "./headers/types.h"

#define N 9

bool slow=true;

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
    Board initial_grid ={
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
    Board errorgrid= {
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

        clearScreen();
        printf("\nGenerating New Board...");
        generateboard(initial_grid);
        copy_grid(initial_grid,playing_grid);
        clearScreen();
        printf("\n Generated New Board...");
        printf("\n>Press b to enter the game");


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

            if (key == UPARROW) { // Up arrow
                selected_cell_row--;
            } else if (key == DOWNARROW) { // Down arrow
                selected_cell_row++;
            } else if (key == RIGHTARROW) { // Right arrow
                selected_cell_column++;
            } else if (key == LEFTARROW) { // Left arrow
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

    } while (key != ESCKEY);

    return 0;
}



