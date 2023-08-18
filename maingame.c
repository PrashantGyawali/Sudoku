#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include<stdlib.h>
#include "./headers/boardfunctions.h"
#include "keys.c"
#include "./headers/types.h"

#define N 9


int mainGame(Game current_loaded_game, bool new_game_or_not) {
    //take inputs is ai_allowed, hints_allowed , init_board
    int mode=2;
    int slow=current_loaded_game.settings.slow;
    int ai_allowed=current_loaded_game.settings.ai;
    int hint_allowed=current_loaded_game.settings.hint;
;
    int selected_cell_row = 4, selected_cell_column = 4;
    clearScreen();
    printf("\tSudoku game\n\nHow to play?:\n");
    printf("'a' => ai solver in game\n");
    printf("'b' => manual mode\n");
    printf("'Arrow keys' => Navigation\n");
    printf("'0' => Clear the number\n");
    printf("'Esc' => quit\n");
    printf("Currently No way to go back to main menu again. Terminate the program and run again");
    printf("\nPress Enter to continue...");
    getch();
    
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

    Board playing_grid;

    //used for coloring the duplicate numbers. if duplicate the 0 changes to 1
    Board error_grid= {
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

    cross_sleep(0);  //! Dont know why hint_allowed changes to 0 when i dont put this
    
    if(new_game_or_not==true)
    {
        clearScreen();
        printf("\nGenerating New Board...");
        generateboard(initial_grid);
        copy_grid(initial_grid,playing_grid);
        clearScreen();
        printf("\n Generated New Board...");
        printf("\n>Press b to enter the game");
    }

    if(new_game_or_not==false)
    {
        copy_grid(current_loaded_game.grid,playing_grid);
        copy_grid(current_loaded_game.initialgrid,initial_grid);
        copy_grid(current_loaded_game.errorgrid,error_grid);
    }

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
            if(hint_allowed==1 ){check_board_show_Errors(playing_grid,error_grid,initial_grid);}
            display_board(playing_grid, selected_cell_row, selected_cell_column,error_grid,initial_grid);
            // printf("%d",hint_allowed);
        }

        //algorithmic solving mode
        if(mode==1)
        {
            if(is_valid_board(error_grid))
            {
                if (solve_sudoku(playing_grid,selected_cell_row,selected_cell_column,error_grid,initial_grid,slow,true)) {
                    display_board(playing_grid,selected_cell_row,selected_cell_column,error_grid,initial_grid);
                    printf("This is the required Sudoku solution\n");
                }
                else {
                    display_board(playing_grid,selected_cell_row,selected_cell_column,error_grid,initial_grid);
                    printf("No solution exists.\n");
                }
            }
            else{
                display_board(playing_grid,selected_cell_row,selected_cell_column,error_grid,initial_grid);
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

        //ai and manual
        if(key==97 && ai_allowed==1) 
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



