#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include<stdlib.h>
#define MENU_SIZE 5

struct GameSettings{
    int ai;
    int hints;
    int gamemode;
    int slow;
}settings;

void clearScreen() {
    // Clear the console screen
    system("cls");
}

void displayMenu(int selectedOption) {
    clearScreen();

    char menu_options[MENU_SIZE][50] = {"New Game", "Load Saved Games", "How to Play","Settings","Quit"};

    // Display the menu options
    for (int i = 1; i <= MENU_SIZE; i++) {
        if (i == selectedOption) {
            printf("> %s <\n", menu_options[i - 1]);
        } else {
            printf("  %s \n", menu_options[i - 1]);
        }
    }
}

void toggle(int *a){
if((*a)==1)
{
    (*a)=0;
}
else{
    (*a)=1;
}
}

void displaySettings(int selectedoption,struct GameSettings *settings){
    clearScreen();

    char menu_options[4][50][50] = {{"Ai Not Allowed","AI Allowed"}, {"Hints Allowed","Hints Not Allowed"}, {"Normal","Childmode"},{"Slow(AI)","Fast(AI)"}};
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
            printf("> %s <\n", menu_options[i - 1][t]);
        } else {
            printf("  %s \n", menu_options[i - 1][t]);
        }
    }
}

void SettingsMenu(struct GameSettings *settings){
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
            if (key == 72 ) { // Up arrow
                selectedOption--;
            } else if (key == 80 ) { // Down arrow
                selectedOption++;
            }
            else if (key == 77 || key==75) { // Right arrow
                toggle(info[selectedOption-1]);
            }
        }
    }
    while (key != 13); // Repeat until Enter key is pressed
main(); //TODO: Need to change this main function to mainmenu and then make similar changes
}




int main() {
    int selectedOption = 1;
    char key;
    settings.ai=0,settings.gamemode=1,settings.hints=0,settings.slow=0;

    // SettingsMenu(&settings);
    do {
        selectedOption=selectedOption>5?1:selectedOption;
        selectedOption=selectedOption<1?5:selectedOption;
        displayMenu(selectedOption);

        // Wait for arrow key input
        key = getch();


        
            if (key == 72 ) { // Up arrow
                selectedOption--;
            } else if (key == 80 ) { // Down arrow
                selectedOption++;
            }


    } while (key != 13); // Repeat until Enter key is pressed


    switch(selectedOption){
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        SettingsMenu(&settings);
        break;
    }
return 0;
}
