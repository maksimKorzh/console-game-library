#include "game.h"

int main()
{
    int pos_x = 20, pos_y = 8;
    int dest_index = pos_y * SCREEN_WIDTH + pos_x;

    InitScreen();

    screen[dest_index] = 'a';
    sprintf(screen + dest_index + 2, "Hello, game.h!");
    RefreshScreen();
    
    getch();
    Leave();
    return 0;
}