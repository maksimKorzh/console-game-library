# Console Game Library
A very basic cross-platform console game library dedicated
for the beginners who want to write their own games

# When to use
Every time you want to write a game like tetris or snake
that requires moving the character(s) along the map without
buffered input(no enter key is pressed) as well as a non-scrolling
screen, e.g. print map at given coordinates.

# API

  - InitScreen() - sets up console/terminal environment
  - RefreshScreen() - updates screen buffer
  - getch() - gets raw character without echoing and line buffering
  - Leave() - does some housekeeping (needs some extra work to restore windows console)
  - PrintMap(int pos_x, int pos_y, int map_width, int map_height, char *map)
    
        Prints game's map to screen at given coordinates (x, y)
    
        int pos_x,        // x coordinate where to print a map on the screen       
        int pos_y,        // y coordinate where to print a map on the screen   
        int map_width,    // the constant value of map width 
        int map_height,   // the constant value of map height
        char *map         // map array

  use this "char screen[SCREEN_SIZE];" array to print something to screen,
  e.g. to print single character at given position use:
  
    int row = 10; int col = 20; 
    screen[row * MAP_WIDTH + col] = 'a';
    RefreshScreen();
  
  This would print character 'a' at (row, col)
  
  You can also use sprintf() function, e.g. to print 'Hello' at (10, 20):
  
    sprintf(screen + (20 * MAP_WIDTH + 10), "Hello")
  
  This would print character 'Hello' at (10, 20)
  
  See the video below for more information on impolementation and usage
  of this library.

# Print character/string at given coordinates (x, y)
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

# Usage example
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
    }

# YouTube video: introduction & demonstration
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/7glEsKNYjmw/0.jpg)](https://youtu.be/7glEsKNYjmw)

# YouTube video: initializing & PrintMap()
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/C_EdZqImysQ/0.jpg)](https://youtu.be/C_EdZqImysQ)

# YouTube video: moving character & collision detection
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/z3OEG45GYRA/0.jpg)](https://youtu.be/z3OEG45GYRA)

# YouTube video: complete game with game.h
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/_LxAa0soHCk/0.jpg)](https://youtu.be/_LxAa0soHCk)

