#include<stdlib.h>
#include<stdbool.h>

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

void clearScreen() {
    system("cls");
}

void display_board(int elements[9][9], int selected_cell_row, int selected_cell_column, int errorblock[9][9],int initial_grid[9][9]) 
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

void check_board_show_Errors(int a[9][9],int errorblocks[9][9],int initial_grid[9][9])
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

    int k=0,row=0,col=0;

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

bool completevalid(int a[9][9])
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
void copy_grid(int src[9][9],int destination[9][9])
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            destination[i][j]=src[i][j];
        }
    }
}