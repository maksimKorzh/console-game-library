#include "game.h"

char map[] = {

    "##########"
    "##########"
    "##########"
    "##########"
    "##########"
    "##########"
    "##########"
    "##########"
    "##########"
    "##########"
  
};

int main()
{
    InitScreen();
    while(getch())PrintMap(10, 10, 10 ,10, map);
    Leave();
    return 0;
}