#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <time.h>
#include "keys.c"
#include "./headers/types.h"

//clears the screen
void clearScreen() {
    system("cls");
}

int getDateInteger() {
    time_t current_time;
    struct tm *timeinfo;

    // Get the current time
    current_time = time(NULL);
    timeinfo = localtime(&current_time);

    // Calculate the date integer in the format YYYYMMDD
    int date_integer = (timeinfo->tm_year + 1900) * 10000 + (timeinfo->tm_mon + 1) * 100 + timeinfo->tm_mday;

    return date_integer;
}


void copy_grid2(Board* src,Board* destination)
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            *destination[i][j]=*src[i][j];
        }
    }
}
typedef struct Gamesdata{
    int lastmodified;
    int id;
    struct Settings{
    int ai;
    int hint;
    int gamemode;
    int slow;
    }settings;

    Board initialgrid;
    Board grid;
    Board errorgrid;
}Game;


void emptyboardinit(Board a){
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            a[i][j]=0;
        }
    }
}

void empty_Game_Init(Game *gm){
        srand(time(NULL));
        gm->lastmodified=getDateInteger();
        gm->id=rand()%100000;
        gm->settings.ai=1;
        gm->settings.gamemode=0;
        gm->settings.hint=1;
        gm->settings.slow=0;
        emptyboardinit(gm->initialgrid);
        emptyboardinit(gm->errorgrid);
        emptyboardinit(gm->grid);
}

Game* read_games(int* numgames) {
    FILE* fs = fopen("pastgames.txt", "rb");
    if (fs == NULL) {
    return NULL;
    }
    // Get the total number of records (size of file / size of a book structure)
    fseek(fs, 0, SEEK_END);
    long fileSize = ftell(fs);
    *numgames = fileSize / sizeof(Game);

    // Allocate memory for the array of games
    Game* games = (Game*)malloc((*numgames) * sizeof(Game));
    if (games == NULL) {
        perror("Memory allocation error");
        fclose(fs);
        return NULL;
    }

    // Read the data from the file into the array of structures
    rewind(fs); // Move file pointer back to the beginning
    fread(games, sizeof(Game), *numgames, fs);

    fclose(fs);
    return games;
}



void SavedGamesMenu(Game *Self, int* has_loaded_the_game)
{
    int selectedgame=0;
    // Game Game1;
    int grid[9][9]= 
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
        
        FILE *pastgames;
        pastgames=fopen("pastgames.txt","rb");
        int numgames;

        Game* games = read_games(&numgames);

//Was used to initialize empty games to test
        // FILE *fs;
        // fs=fopen("pastgames.txt","a+");
        // fseek(fs,0,SEEK_END);
        // //empty Game init
        Game bk;
        empty_Game_Init(&bk);
        // printf("\nAdded new game info %d %d",bk.id,bk.lastmodified);
        // sleep(2000);

        // fwrite(&bk,sizeof(bk),1,fs);
        // fclose(fs);
        
        int test_grid[9][9]={
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
        if (games != NULL) {
            int key=1;
            while(key!=BACKSPACE)
            {   clearScreen();
                printf("+ID----Last Modified----Ai------Hints---SlowAI+\n");
                for (int i = 0; i < numgames; i++)
                {
                        if(i==selectedgame)
                        {
                        printf("\033[47;30m %-7d \t %9d \t %d \t %d \t %d \033[0m \n",games[i].id, games[i].lastmodified, games[i].settings.ai, games[i].settings.hint, games[i].settings.slow);
                        }
                        else{
                        printf(" %-7d \t %9d \t %d  \t %d \t %d\n",games[i].id ,games[i].lastmodified,games[i].settings.ai,games[i].settings.hint,games[i].settings.slow);
                        }
                }
                printf("\nPress backspace to go back to main menu");
            key=getch();
            if(key==UPARROW && selectedgame>0)
            {
                selectedgame-=1;
            }
            if(key==DOWNARROW && selectedgame<numgames-1)
            {
                selectedgame+=1;
            }
            if(key==ENTERKEY)
            {
            // CopyGame(&games[selectedgame],&Game1);
            printf("\nLoading Game data...");
            sleep(500);
            bk=games[selectedgame];
            //and update this Game to start menu
            *Self=bk;
            *has_loaded_the_game=1;
            break;
            }
            if(key==ESCKEY)
            {
                free(games);
                exit(0);
            }
        }     
    }
    else{
        printf("\nNo Saved games\nPress any key to go back to main menu...");
        getch();
    }
    free(games); // Free the dynamically allocated memory for the array of books
}

