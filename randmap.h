#pragma once
#include "iostream"
#include "ctime"
#include "iostream"
#include "fstream"

static int board[MAX_MAP_Y][MAX_MAP_X];

static void house_1(int x, int y)
{
    if (board[x][y] == 0)
    {
        board[x][y] = 1;
    }
    if (board[x+1][y] == 0)
    {
        board[x+1][y] = 1;
    }
    if (board[x+2][y] == 0)
    {
        board[x+2][y] = 1;
    }
    if (board[x+3][y] == 0)
    {
        board[x+3][y] = 1;
    }
    if (board[x][y+1] == 0)
    {
        board[x][y+1] = 1;
    }
    if (board[x][y+2] == 0)
    {
        board[x][y+2] = 1;
    }
    if (board[x][y+3] == 0)
    {
        board[x][y+3] = 1;
    }
    if (board[x+3][y] == 0)
    {
        board[x+3][y] = 1;
    }
    if (board[x][y+1] == 0)
    {
        board[x][y+1] = 1;
    }
    if (board[x][y+2] == 0)
    {
        board[x][y+2] = 1;
    }
    if (board[x][y+3] == 0)
    {
        board[x][y+3] = 1;
    }
    if (board[x + 1][y + 3] == 0)
    {
        board[x + 1][y + 3] = 1;
    }
    if (board[x + 2][y + 3] == 0)
    {
        board[x + 2][y + 3] = 1;
    }
    if (board[x + 3][y + 3] == 0)
    {
        board[x + 3][y + 3] = 1;
    }
    if (board[x + 3][y + 1] == 0)
    {
        board[x + 3][y + 1] = 1;
    }
    //makes house hollow:
    board[x+1][y+1] = 8;
    board[x+1][y+2] = 8;
    board[x+2][y+1] = 8;
    board[x+2][y+2] = 8;
    board[x+3][y+2] = 8;
}

static void house_2(int x, int y)
{
    if (board[x][y] == 0)
    {
        board[x][y] = 1;
    }

    if (board[x+1][y] == 0)
    {
        board[x + 1][y] = 1;
    }

    if (board[x+2][y] == 0)
    {
        board[x + 2][y] = 1;
    }

    if (board[x+3][y] == 0)
    {
        board[x + 3][y] = 1;
    }

    if (board[x][y+1] == 0)
    {
        board[x][y + 1] = 1;
    }

    if (board[x][y+3] == 0)
    {
        board[x][y + 3] = 1;
    }

    if (board[x][y+4] == 0)
    {
        board[x][y + 4] = 1;
    }

    if (board[x][y+5] == 0)
    {
        board[x][y + 5] = 1;
    }

    if (board[x][y+6] == 0)
    {
        board[x][y + 6] = 1;
    }

    if (board[x+1][y+6] == 0)
    {
        board[x + 1][y + 6] = 1;
    }

    if (board[x+2][y+3] == 0)
    {
        board[x + 2][y + 3] = 1;
    }

    if (board[x+3][y+3] == 0)
    {
        board[x + 3][y + 3] = 1;
    }

    if (board[x+3][y+1] == 0)
    {
        board[x + 3][y + 1] = 1;
    }

    if (board[x+3][y+2] == 0)
    {
        board[x + 3][y + 2] = 1;
    }

    if (board[x+3][y+3] == 0)
    {
        board[x + 3][y + 3] = 1;
    }

    if (board[x+3][y+4] == 0)
    {
        board[x + 3][y + 4] = 1;
    }

    if (board[x+3][y+5] == 0)
    {
        board[x + 3][y + 5] = 1;
    }

    if (board[x+3][y+6] == 0)
    {
        board[x + 3][y + 6] = 1;
    }
    //makes house hollow:
    board[x][y+2] = 8;
    board[x+1][y+1] = 8;
    board[x+1][y+2] = 8;
    board[x+1][y+3] = 8;
    board[x+1][y+4] = 8;
    board[x+1][y+5] = 8;
    board[x+2][y+1] = 8;
    board[x+2][y+2] = 8;
    board[x+2][y+4] = 8;
    board[x+2][y+5] = 8;
    board[x+2][y+6] = 8;
}

static void house_1b(int x, int y)
{
    if (board[x][y] == 0)
    {
        board[x][y] = 1;
    }
    if (board[x + 1][y] == 0)
    {
        board[x + 1][y] = 1;
    }
    if (board[x + 2][y] == 0)
    {
        board[x + 2][y] = 1;
    }
    if (board[x + 3][y] == 0)
    {
        board[x + 3][y] = 1;
    }
    if (board[x+3][y + 2] == 0)
    {
        board[x+3][y + 2] = 1;
    }
    if (board[x][y + 2] == 0)
    {
        board[x][y + 2] = 1;
    }
    if (board[x][y + 3] == 0)
    {
        board[x][y + 3] = 1;
    }
    if (board[x + 3][y] == 0)
    {
        board[x + 3][y] = 1;
    }
    if (board[x][y + 1] == 0)
    {
        board[x][y + 1] = 1;
    }
    if (board[x][y + 2] == 0)
    {
        board[x][y + 2] = 1;
    }
    if (board[x][y + 3] == 0)
    {
        board[x][y + 3] = 1;
    }
    if (board[x + 1][y + 3] == 0)
    {
        board[x + 1][y + 3] = 1;
    }
    if (board[x + 2][y + 3] == 0)
    {
        board[x + 2][y + 3] = 1;
    }
    if (board[x + 3][y + 3] == 0)
    {
        board[x + 3][y + 3] = 1;
    }
    if (board[x + 3][y + 1] == 0)
    {
        board[x + 3][y + 1] = 1;
    }
    //makes house hollow:
    board[x + 1][y + 1] = 8;
    board[x + 1][y + 2] = 8;
    board[x + 2][y + 1] = 8;
    board[x + 2][y + 2] = 8;
    board[x][y + 1] = 8;
}

static void house_2b(int x, int y)
{
    if (board[x][y] == 0)
    {
        board[x][y] = 1;
    }

    if (board[x][y+2] == 0)
    {
        board[x][y+2] = 1;
    }

    if (board[x + 2][y] == 0)
    {
        board[x + 2][y] = 1;
    }

    if (board[x + 3][y] == 0)
    {
        board[x + 3][y] = 1;
    }

    if (board[x][y + 1] == 0)
    {
        board[x][y + 1] = 1;
    }

    if (board[x][y + 3] == 0)
    {
        board[x][y + 3] = 1;
    }

    if (board[x][y + 4] == 0)
    {
        board[x][y + 4] = 1;
    }

    if (board[x+2][y + 6] == 0)
    {
        board[x+2][y + 6] = 1;
    }

    if (board[x][y + 6] == 0)
    {
        board[x][y + 6] = 1;
    }

    if (board[x + 1][y + 6] == 0)
    {
        board[x + 1][y + 6] = 1;
    }

    if (board[x + 1][y + 3] == 0)
    {
        board[x + 1][y + 3] = 1;
    }

    if (board[x + 3][y + 3] == 0)
    {
        board[x + 3][y + 3] = 1;
    }

    if (board[x + 3][y + 1] == 0)
    {
        board[x + 3][y + 1] = 1;
    }

    if (board[x + 3][y + 2] == 0)
    {
        board[x + 3][y + 2] = 1;
    }

    if (board[x + 3][y + 3] == 0)
    {
        board[x + 3][y + 3] = 1;
    }

    if (board[x + 3][y + 4] == 0)
    {
        board[x + 3][y + 4] = 1;
    }

    if (board[x + 3][y + 5] == 0)
    {
        board[x + 3][y + 5] = 1;
    }

    if (board[x + 3][y + 6] == 0)
    {
        board[x + 3][y + 6] = 1;
    }
    //makes house hollow:
    board[x+1][y] = 8;
    board[x + 1][y + 1] = 8;
    board[x + 1][y + 2] = 8;
    board[x + 1][y + 3] = 8;
    board[x + 1][y + 4] = 8;
    board[x + 1][y + 5] = 8;
    board[x + 2][y + 1] = 8;
    board[x + 2][y + 2] = 8;
    board[x + 2][y + 3] = 8;
    board[x + 2][y + 4] = 8;
    board[x + 2][y + 5] = 8;
    board[x][y + 5] = 8;
}

static int createRandomMap()
{
    srand(time(NULL));
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            int r = rand() % 100 + 1;
            /*Makes borders*/
            if (i==0||j==0||j==MAX_MAP_X-1||i==MAX_MAP_Y-1)
            {
                board[i][j] = 7;
            }
            else if (board[i][j] == 0)
            {
                board[i][j] = 0;
            }
            if (r == 1)
            {
                house_1(i,j);
            }
            if (r == 2)
            {
                house_2(i, j);
            }
            if (r == 3)
            {
                house_1b(i, j);
            }
            if (r == 4)
            {
                house_2b(i, j);
            }
            /*check if against another house, if true, makes a hallway/doorway (North and South)*/
            if (board[i][j] == 1 && board[i][j-2] == 1 && board[i - 1][j - 1] == 1)
            {
                board[i-1][j-1] = 8;
                board[i][j-1] = 8;
            }
            if (board[i-2][j] == 1 && board[i - 2][j - 2] == 1 && board[i - 1][j - 1] == 1)
            {
                board[i-2][j-1] = 8;
                board[i - 1][j -1] = 8;
            }
            /*check if against another house, if true, makes a hallway/doorway (East and West)*/
            if (board[i][j] == 1 && board[i - 2][j] == 1 && board[i - 1][j - 1] == 1)
            {
                board[i-1][j] = 8;
                board[i - 1][j-1] = 8;
            }
            if (board[i][j - 2] == 1 && board[i - 2][j - 2] == 1 && board[i - 1][j - 1] == 1)
            {
                board[i - 1][j-2] = 8;
                board[i - 1][j - 1] = 8;
            }
            //if (board[i][j+1] == 7 || board[i][j-1] == 7||board[i-1][j] == 7||board[i-1][j] == 7)
            //{
            //	board[i][j] == 0;
            //}
        }
    }

    std::ofstream myfile;
    myfile.open("Map.txt");
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            myfile << board[i][j] << " ";
        }
        myfile << "\n";
    }
    myfile.close();

    return 0;
}

