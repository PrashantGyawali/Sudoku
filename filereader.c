#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <time.h>
#include "keys.c"
#include "./headers/types.h"
#include "./headers/types2.h"


//clears the screen

#ifndef __FILEREADER__
#define __FILEREADER__

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

void emptyboardinit(Board a){
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            a[i][j]=0;
        }
    }
}

void empty_Game_Init(Game *gm,GlGameSettings settings){
        srand(time(NULL));
        gm->lastmodified=getDateInteger();
        gm->id=rand()%100000;
        gm->settings.ai=settings.ai;
        gm->settings.gamemode=settings.gamemode;
        gm->settings.gamemode=0;
        gm->settings.hint=settings.hints;
        gm->settings.slow=settings.slow;
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


void write_game(Game gamedata) {
    FILE* fs = fopen("pastgames.txt", "rb+");
    
    if (fs == NULL) {
        // Handle file creation and write new data
        fs = fopen("pastgames.txt", "wb");
        fwrite(&gamedata, sizeof(Game), 1, fs);
        fclose(fs);
        return;
    }
    
    // Get the total number of records (size of file / size of Game structure)
    fseek(fs, 0, SEEK_END);
    long fileSize = ftell(fs);
    int numgames = fileSize / sizeof(Game);

    // Allocate memory for the array of games
    Game* games = (Game*)malloc(numgames * sizeof(Game));

    // Read the data from the file into the array of structures
    rewind(fs);
    fread(games, sizeof(Game), numgames, fs);
    fclose(fs);

    // Update the file
    fs = fopen("pastgames.txt", "wb");
    fwrite(&gamedata, sizeof(Game), 1, fs);    
    for (int i = 0; i < numgames; i++) {
        if (games[i].id != gamedata.id) {
            fwrite(&games[i], sizeof(Game), 1, fs);
        }
    }
    fclose(fs);

    free(games); // Free the allocated memory
}


void SavedGamesMenu(Game *Self, int* has_loaded_the_game)
{
    clearScreen();
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

        Game bk;
        // empty_Game_Init(&bk);
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
            cross_sleep(500);
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

#endif