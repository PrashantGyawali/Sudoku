#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct SavedGamesdata{
    int lastmodified;
    int id;
    struct Settings{
    int ai;
    int hint;
    int gamemode;
    int slow;
    }settings;

    int initialgrid[9][9];
    int grid[9][9];
    int errorgrid[9][9];
}SavedGames;

int* emptyboardinit(){
    int a[9][9]={
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
    return a;
}

bool completevalid(int a[9][9])
{
    //check 
    for(int i=0;i<9;i++)
        {
            int row_sum=0;
            int row_product=1;
            int col_sum=0;
            int col_product=1;

            for(int j=0;j<9;j++)
            {
            row_sum+=a[i][j];
            row_product*=a[i][j];
            col_sum+=a[j][i];
            col_product*=a[j][i];
            }

            if(row_sum!=45 ||col_sum!=45||row_product!=362880 ||col_product!=362880)
            {
            printf("row or column");
            return false;
            }
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
                printf("square");
                return false;
            }
        } 
    }

    return true;
}

SavedGames* read_games(int* numgames) {
    FILE* fs = fopen("pastgames.txt", "rb");
    if (fs == NULL) {
    return NULL;
    }
    // Get the total number of records (size of file / size of a book structure)
    fseek(fs, 0, SEEK_END);
    long fileSize = ftell(fs);
    *numgames = fileSize / sizeof(SavedGames);

    // Allocate memory for the array of games
    SavedGames* games = (SavedGames*)malloc((*numgames) * sizeof(SavedGames));
    if (games == NULL) {
        perror("Memory allocation error");
        fclose(fs);
        return NULL;
    }

    // Read the data from the file into the array of structures
    rewind(fs); // Move file pointer back to the beginning
    fread(games, sizeof(SavedGames), *numgames, fs);

    fclose(fs);
    return games;
}


void readdata(FILE*srcfile,struct SavedGames* games)
{

}


void main()
{
    int selectedgame=0;

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

        SavedGames* games = read_games(&numgames);
        FILE *fs;
        fs=fopen("pastgames.txt","a+");
        fseek(fs,0,SEEK_END);
        SavedGames bk={
            200,1,{0,0,0,0},{
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
        },emptyboardinit(),emptyboardinit()};
        fwrite(&bk,sizeof(bk),1,fs);
        fclose(fs);
        
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
        // printf("%d",completevalid(test_grid)); //for testing
        if (games != NULL) {
            printf("+ID----Last Modified----Ai--+\n");
            for (int i = 0; i < numgames; i++)
            {
                    if(i==selectedgame)
                    {
                    printf("\033[47;30m %d \t %d \t\t %d \033[0m\n",games[i].id ,games[i].lastmodified,games[i].settings.ai);
                    }
                    else{
                    printf(" %d \t %d \t\t %d \n",games[i].id ,games[i].lastmodified,games[i].settings.ai);
                    }
            }
    }
    else{
        printf("No Saved games");
    }


    free(games); // Free the dynamically allocated memory for the array of books
}

