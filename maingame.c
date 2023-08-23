#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include<stdlib.h>
#include "./headers/boardfunctions.h"
#include "keys.c"
#include "filereader.c"
#include "./headers/types.h"
#include "hardcore.c"

#define N 9


int mainGame(Game current_loaded_game, bool new_game_or_not) {
    //take inputs is ai_allowed, hints_allowed , init_board
    int mode=2;
    int slow=current_loaded_game.settings.slow;
    int selected_cell_row = 4, selected_cell_column = 4;
    clearScreen();
    printf("\tSudoku game\n\nHow to play?:\n");
    printf("'a' => ai solver in game\n");
    printf("'b' => manual mode\n");
    printf("'Arrow keys' => Navigation\n");
    printf("'0' => Clear the number\n");
    printf("'Backspace' => Go back to menu\n");
    printf("'Esc' => quit\n");
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

    if(new_game_or_not==true)
    {
        clearScreen();
        printf("\nGenerating New Board...\n Please restart if it takes too long");
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

        cross_sleep(500);
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
            if(current_loaded_game.settings.hint==1 )
            {
                check_board_show_Errors(playing_grid,error_grid,initial_grid);
            }
            display_board(playing_grid, selected_cell_row, selected_cell_column,error_grid,initial_grid);

        //procedure for hardmode
            if(current_loaded_game.settings.gamemode==1)
            {
                for(int i=0;i<9;i++)
                {
                    for(int j=0;j<9;j++)
                    {
                        if(error_grid[i][j]==1)
                        {
                            cross_sleep(500);
                            printf("\nYou have made an invalid move. Activating destruction protocol");
                            cross_sleep(500);
                            write_game(current_loaded_game,'d');
                            deletegmae();
                        }
                    }
                }
            }
        }

        //algorithmic solving mode
        if(mode==1)
        {
            if(is_valid_board(error_grid))
            {
                if (solve_sudoku(playing_grid,selected_cell_row,selected_cell_column,error_grid,initial_grid,slow,slow)) {
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
            copy_grid(error_grid,current_loaded_game.errorgrid);
            copy_grid(playing_grid,current_loaded_game.grid);
            copy_grid(initial_grid,current_loaded_game.initialgrid);
            write_game(current_loaded_game,'u');
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
        if(key==97 && current_loaded_game.settings.ai==1 && current_loaded_game.settings.gamemode!=1) 
        {
            mode=1;
        }
        if(key==98)
        {
            mode=2;
        }

        if(key==ESCKEY)
        {
            exit(0);
        }

    } while (key != BACKSPACE);
    fflush(stdin);
    return 0;
}



