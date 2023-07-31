#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>

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
int main()
{
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

        FILE *startgrid;
        startgrid=fopen("startgrids.txt","r");

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
    printf("%d",completevalid(test_grid));
    printf("Random no less than 8 is:%d\n",rand()%8);


}

