#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include<stdlib.h>
#include "keys.c"
#include "./headers/boardfunctions.h"
#include "./headers/types.h"
#include "./headers/types2.h"
#include "filereader.c"
#include "maingame.c"
#include "tutorialpages.c"
#define MENU_SIZE 6

GlGameSettings settings;

void displayMenu(int selectedOption) {
    clearScreen();

    char menu_options[MENU_SIZE][50] = {"New Game","Loaded game", "Saved Games", "How to Play","Settings","Quit"};
    printf("SUDOKU\n\n");
    // Display the menu options
    for (int i = 1; i <= MENU_SIZE; i++) {
        if (i == selectedOption) {
            printf("> %s <\n", menu_options[i - 1]);
        } else {
            printf("  %s \n", menu_options[i - 1]);
        }
    }
}

void toggle(int *a,int min, int max,int direction){
if(direction==1)
{
    if((*a)==max)
    {
        (*a)=min;
    }
    else{
        (*a)+=1;
    }
}
if(direction==0){
if((*a)==min)
    {
        (*a)=max;
    }
    else{
        (*a)=(*a)-1;
    }
}
}



void tutorialmenu()
{
    int pageno;
    void (*pagearray[3]) () ={page1,page2,page3};    
    printf("Welcome to the tutorial\n Let's start.\n Use enter or backspace to change pages");
    pageno=1;
    int key=0;
    while(key!=27)
    {
        pagearray[pageno-1](&pageno);
        key=getch();
        if (key == 13) 
        { 
            toggle(&pageno,1,3,1);
        }
        if (key==8)
        {
            toggle(&pageno,1,3,0);
        }
        if(key==ESCKEY)
        {    exit(0);
        }

        if(key==BACKSPACE)
        {
            break;
        }
    }


}

//function to format the display layout of the settings menu (without input logic)
void displaySettings(int selectedoption,GlGameSettings *settings){
    clearScreen();

    char menu_options[4][50][50] = {{"Ai Not Allowed","AI Allowed"}, {"Hints Not Allowed","Hints Allowed"}, {"Normal","Childmode"},{"Fast(AI)","Slow(AI)"}};
    int* info[4]={&settings->ai,&settings->hints,&settings->gamemode,&settings->slow};

    // Display the menu options
    printf("Settings:\n");
    for (int i = 1; i <= 4; i++) {
        int t;
        switch(i){
                case 1:
                t=settings->ai;
                break;
                case 2:
                t=settings->hints;
                break;
                case 3:
                t=settings->gamemode;
                break;
                case 4:
                t=settings->slow;
                }
        if (i == selectedoption) {
            printf("< %s >\n", menu_options[i - 1][t]);
        } else {
            printf("  %s \n", menu_options[i - 1][t]);
        }
    }
    printf("\n\nUse left and right arrow keys to change settings");
}

//Enter the settings menu (contains inputs and logics)
void SettingsMenu(GlGameSettings *settings){
    int selectedOption=1;
    

    int key;
    do {
        int* info[4]={&settings->ai,&settings->hints,&settings->gamemode,&settings->slow};
        selectedOption=selectedOption>4?1:selectedOption;
        selectedOption=selectedOption<1?4:selectedOption;
        displaySettings(selectedOption,settings);
        key = getch();

        // Process arrow key input
        if (key == 0 || key == 224) 
        {
            key = getch(); // Extended key code
            if (key == UPARROW ) { // Up arrow
                selectedOption--;
            } else if (key == DOWNARROW ) { // Down arrow
                selectedOption++;
            }
            else if (key == LEFTARROW || key==RIGHTARROW) { // Right arrow or left arrow
                toggle(info[selectedOption-1],0,1,1);
            }
            if(key==ESCKEY)
            {
                exit(0);
            }
        }
    }
    while (key != 13); // Repeat until Enter key is pressed
}



int main();
int main() {

    //initialize loadedgame and new game. based on the option selected, one of this will be passes into the game with additional bool
    // param tlling wheteher new game or old game

    int has_loaded_the_game=0;
    Game LoadedGame;
    Game NewGame;
    settings.ai=1,settings.gamemode=1,settings.hints=1,settings.slow=1;

    empty_Game_Init(&LoadedGame,settings);
    empty_Game_Init(&NewGame,settings);


    int selectedOption = 1;
    char key;

    while(1)
    {

    do {
        selectedOption=selectedOption>6?1:selectedOption;
        selectedOption=selectedOption<1?6:selectedOption;
        displayMenu(selectedOption);
        if(selectedOption==1){
        printf("\nNow playing New Game#%d",NewGame.id);
        }
        if(selectedOption==2){
            if( has_loaded_the_game)
            {
                printf("\nNow playing Loaded Game#%d",LoadedGame.id);
            }
            else{
                printf("\nNo games loaded");
            }    
        }
        // Wait for arrow key input
        key = getch();

            if (key == UPARROW ) { // Up arrow
                selectedOption--;
            } else if (key == DOWNARROW ) { // Down arrow
                selectedOption++;
            }
            else if(key==ESCKEY)
            {
                exit(0);
            }

if(key==ENTERKEY)
{
switch(selectedOption){
        //will create a new game
        case 1:
            write_game(NewGame);
            mainGame(NewGame,true);

            //initialize the new game again
            empty_Game_Init(&NewGame,settings);
            NewGame.settings.ai=settings.ai;
            NewGame.settings.gamemode=settings.gamemode;
            NewGame.settings.hint=settings.hints;
            NewGame.settings.gamemode=settings.gamemode;
            NewGame.settings.slow=settings.slow;

        break;


        //will create board from a savedgame data
        //will give loaded game info to the function if has_loaded_game else do nothing
        case 2:
        if(has_loaded_the_game){
            //pass to fn
            mainGame(LoadedGame,false);
        }
        break;

        //will get us into saved games menu
        case 3:
        SavedGamesMenu(&LoadedGame, &has_loaded_the_game);
        break;

        case 4:
        tutorialmenu();
        break;


        case 5:

        SettingsMenu(&settings);
        //update the settings
        NewGame.settings.ai=settings.ai;
        NewGame.settings.gamemode=settings.gamemode;
        NewGame.settings.hint=settings.hints;
        NewGame.settings.gamemode=settings.gamemode;
        NewGame.settings.slow=settings.slow;

        break;


        case 6:
        exit(0);
        break;
    }
}

fflush(stdin);


    } while (key != ESCKEY); // Repeat until Enter key is pressed


    // SettingsMenu(&settings);

}
return 0;
}