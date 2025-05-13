#include <stdio.h>
#include <stdlib.h>

void start(char board[][20], const int n)
{
    for (int i = 0; i < 4; i++) 
    {
        int j = i % 2;
        while (j <= n)
         {
            board[i][j] = '1';
            j += 2;
        }      
    }
    for (int i = n-1; i > n - 5; i--)
     {
        int j = (1+i) % 2;
        while (j < n)
         {
            board[i][j] = '2';
            j += 2;
        }      
    }
}
void print(char board[][20], const int n)
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == '1' || board[i][j] == '2')
            {
                printf("%c ", board[i][j]);
            }
            else
            {
                printf("_");
            }    
        }
        printf("\n");
    }
}


int main(void) 
{
    char board[20][20];
    start(board, 10);
    print(board, 10);
    return 0;
}