#define BOARDSIZE 9
#include<stdlib.h>
#include<stdbool.h>

void displayCell(int value, int isSelected, int errored) {
    if (isSelected) 
    {
        value!=0?printf("\033[97;107m %d \033[0m", value):printf("\033[97;107m   \033[0m");
    } 
    else {
        value!=0?errored==1?printf("\033[0;31m %d \033[0m", value):printf(" %d ", value):printf("   ");
    }
}

void clearScreen() {
    system("cls");
}

void displayBoard(int elements[BOARDSIZE][BOARDSIZE], int selected_cell_row, int selected_cell_column, int errorblock[BOARDSIZE][BOARDSIZE]) 
{
    clearScreen();
    int i, j;
    printf("\033[1m+===+===+===+===+===+===+===+===+===+\033[0m\n");
    for (i = 0; i < BOARDSIZE; i++) {
        for (j = 0; j <= BOARDSIZE-1; j++) {
            if (j % 3 == 0) {
                printf("\033[1m|\033[0m");
                printf("");
                displayCell(elements[i][j], i == selected_cell_row && j == selected_cell_column,errorblock[i][j]==1);
            }
            else {
                printf(":");
                displayCell(elements[i][j], i == selected_cell_row && j == selected_cell_column,errorblock[i][j]==1);
            }

            if(j==BOARDSIZE-1)
            {
                printf("\033[1m|\033[0m");
            }
        }
        printf("\n");
        for (j = 0; j < BOARDSIZE; j++) {
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

bool validboard(int errorgrid[BOARDSIZE][BOARDSIZE]){
    for (int i=0;i<9;i++)
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

void checkBoardShowErrors(int a[9][9],int errorblocks[BOARDSIZE][BOARDSIZE])
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
            for(i=0;i<9;i++)
            {
                if((a[i][j]-1)>=0)
                {
                    coldups[a[i][j]-1]++;
                    if(coldups[a[i][j]-1]>1) //contains duplicate means updating the errorarray to colour the other dups with red color
                    {
                        errorblocks[i][j]=1;
                    };
                }
            }
        for(i=0;i<9;i++)
        {
            coldups[i]=0;
        }
        }
        

//check the rows
int rowdups[9]={0,0,0,0,0,0,0,0,0};
for(i=0;i<9;i++)
{
    for(j=0;j<9;j++)
    {
        if((a[i][j]-1)>=0)
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

    int k=0,sum=0,row=0,col=0;

    for(row=0;row<9;row+=3)
    {   
        for(col=0;col<9;col+=3)
        { int sum=0;
            for(i=row;i<row+3;i++)
            {
                    for(j=col;j<col+3;j++)
                    {
                        if(a[i][j]>0)
                        {
                            sqdups[a[i][j]-1]++;
                            if(sqdups[a[i][j]-1]>1) //contains duplicate means updating the errorarray to colour the other dups with red color
                            {
                                errorblocks[i][j]=1;
                            };
                        }
                    }
            }
            for(i=0;i<9;i++)
            {
                sqdups[i]=0;
            }
        } 

    }
}