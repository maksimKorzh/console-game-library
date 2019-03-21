/*********************************************************************************\
;                                     game.h                                      ;
;---------------------------------------------------------------------------------;
;                    A very basic console game library dedicated                  ;
;                to the beginners that want to write their own games              ;
;---------------------------------------------------------------------------------;
;                                by Maksim Korzh                                  ;
;---------------------------------------------------------------------------------;
\*********************************************************************************/

/*********************************************************************************\
;---------------------------------------------------------------------------------;
;        Copyright © 2018 Maksim Korzh <freesoft.for.people@gmail.com>            ;
;---------------------------------------------------------------------------------;
;     This work is free. You can redistribute it and/or modify it under the       ;
;      terms of the Do What The Fuck You Want To Public License, Version 2,       ;
;       as published by Sam Hocevar. See the COPYING file for more details.       ;
;---------------------------------------------------------------------------------;
'       THIS PROGRAM IS FREE SOFTWARE. IT COMES WITHOUT ANY WARRANTY, TO          ;
;        THE EXTENT PERMITTED BY APPLICABLE LAW. YOU CAN REDISTRIBUTE IT          ;
;       AND/OR MODIFY IT UNDER THE TERMS OF THE DO WHAT THE FUCK YOU WANT         ;
;          TO PUBLIC LICENCE, VERSION 2, AS PUBLISHED BY SAM HOCEVAR.             ;
;                SEE http://www.wtfpl.net/ FOR MORE DETAILS.                      ;
;---------------------------------------------------------------------------------;
\*********************************************************************************/

/*********************************************************************************\
;---------------------------------------------------------------------------------;
;                   DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                   ;
;                           Version 2, December 2004                              ;
;                                                                                 ;
;        Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>                         ;
;                                                                                 ;
;        Everyone is permitted to copy and distribute verbatim or modified        ;
;        copies of this license document, and changing it is allowed as long      ;
;        as the name is changed.                                                  ;
;                                                                                 ;
;                   DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                   ;
;          TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION        ;
;                                                                                 ;
;         0. You just DO WHAT THE FUCK YOU WANT TO.                               ;
;---------------------------------------------------------------------------------;
\*********************************************************************************/

#include <stdio.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define SCREEN_SIZE SCREEN_WIDTH * SCREEN_HEIGHT

char screen[SCREEN_SIZE];

#ifdef WIN32

#include <windows.h>
HANDLE console;
CONSOLE_CURSOR_INFO cursor;
COORD coord;
DWORD char_written = 0;
#endif


#ifdef unix

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;
#endif

void InitScreen()
{
    #ifdef WIN32
    console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);    
    cursor.dwSize = 100;
    cursor.bVisible = FALSE;    
    coord.X = 0;
    coord.Y = 0;
    SetConsoleActiveScreenBuffer(console);
    SetConsoleCursorInfo(console, &cursor);        
    #endif

    #ifdef unix
    printf("\x1b[?25l");    // hide cursor escape sequence
    printf("\x1b[2J");       // clear screen
    tcgetattr(STDIN_FILENO, &orig_termios);
    
    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    #endif
}

void RefreshScreen(int delay)
{
    for(int scr_cell = 0; scr_cell < SCREEN_SIZE; scr_cell++)
        if(!screen[scr_cell]) screen[scr_cell] = ' ';

    #ifdef WIN32
	WriteConsoleOutputCharacter(console, screen, SCREEN_WIDTH * SCREEN_HEIGHT, coord, &char_written);
	Sleep(delay);
    #endif

    #ifdef unix
    printf("\x1b[0;0H%s\n", screen);
    #endif
}

int GetKey(int key)
{
    #ifdef WIN32

    if(key != 27) key -= 32;

    if(GetAsyncKeyState((unsigned short)key) & 0x8000) return 1;
    else return 0;

    #endif


    #ifdef unix
    int cmp_key = getchar();

    if(key == cmp_key) return 1;
    else return 0;
    
    #endif
}

void Leave()
{
    #ifdef WIN32
    cursor.bVisible = TRUE;
    SetConsoleCursorInfo(console, &cursor);
    #endif

    #ifdef unix
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    printf("\x1b[?25h");    // show cursor escape sequence
    #endif
}
