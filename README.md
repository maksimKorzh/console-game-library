# Console Game Library
A very basic cross-platform console game library dedicated
for the beginners who want to write their own games

#When to use
Every time you want to write a game like tetris or snake
that requires moving the character(s) along the map without
buffered input(no enter key is pressed) as well as a non-scrolling
screen, e.g. print map at given coordinates.

#API

  - InitScreen()        set up console/terminal environment
  - RefreshScreen()     update screen buffer
  - getch()             raw getchar() without echoing
  - Leave()             do some housekeeping (needs some extra work to restore windows console)

  use this "char screen[SCREEN_SIZE];" array to print something to screen,
  e.g. to print single character at given position use:
  
  int row = 10; int col = 20;
  
  screen[row * MAP_WIDTH + col] = 'a';
  RefreshScreen();
  
  This would print character 'a' at (row, col)
  
  You can also use sprintf() function, e.g. to print 'Hello' at (10, 20):
  sprintf(screen + (row * MAP_WIDTH + col), "Hello")
  
  This would print character 'a' at (row, col)
  
  See the video below for more information on impolementation and usage
  of this library.

#Example
int main()
{
    InitScreen();
    
    int key;
    
    while(1)
    {
        key = getch();
        
        switch(key)
        {
            case...
            case...
            case...
            case...
        }
        
        RefreshScreen();
    }
    
    Leave();

    return 0;
}

#YouTube video
is comming soon

