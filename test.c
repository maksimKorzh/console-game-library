#include "game.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

char map[] = {

    "##########"
    "#        #"
    "#        #"
    "#        #"
    "#        #"
    "#    @   #"
    "#        #"
    "#        #"
    "#        #"
    "##########"
    
};

void GetPlayerPosition(int *pos_x, int *pos_y)
{
    for(int row = 0; row < MAP_HEIGHT; row++)
    {
        for(int col = 0; col < MAP_WIDTH; col++)
        {
            int cell = row * MAP_WIDTH + col;

            if(map[cell] == '@')
            {
                *pos_x = col;
                *pos_y = row;
            }
        }
    }
}

void MovePlayer(int pos_x, int pos_y, int offset)
{
    int player = pos_y * MAP_WIDTH + pos_x;

    if(map[player + offset] != '#')
    {
        map[player] = ' ';
        map[player + offset] = '@';
    }
}

int main()
{
    int pos_x, pos_y, key;

    int center_x = SCREEN_WIDTH / 2 - MAP_WIDTH / 2;
    int center_y = SCREEN_HEIGHT / 2 - MAP_HEIGHT / 2;

    InitScreen();
    PrintMap(center_x, center_y, MAP_WIDTH, MAP_HEIGHT, map);

    while(key != 27)
    {
        GetPlayerPosition(&pos_x, &pos_y);
        key = getch();

        switch(key)
        {
            case 'w':
                MovePlayer(pos_x, pos_y, - MAP_WIDTH);
                break;

            case 's':
                MovePlayer(pos_x, pos_y, MAP_WIDTH);
                break;

            case 'a':
                MovePlayer(pos_x, pos_y, - 1);
                break;

            case 'd':
                MovePlayer(pos_x, pos_y, 1);
                break;
        }

        PrintMap(center_x, center_y, MAP_WIDTH, MAP_HEIGHT, map); 
    }
    
    Leave();
    return 0;
}