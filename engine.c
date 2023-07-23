#include "rogue.h"
#include <windows.h>

level *actualLevel;
extern size_t levelCounter;

void configScr()
{
	system("mode con cols=80 lines=30");
	initscr();
	noecho();
	curs_set(0);
	start_color();
	
	init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_CYAN, COLOR_CYAN,COLOR_BLACK);
	init_pair(COLOR_BLUE, COLOR_BLUE,COLOR_BLACK);
	init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
	init_pair(COLOR_EXIT,COLOR_WHITE, COLOR_BLUE);
}

void gameLoop()
{
	initialScreen();
	while(!gameover && levelCounter < 5){
		actualLevel = createLevel();
		putPlayer(actualLevel);
		while(!(actualLevel->finalized || gameover)){
			imprimirTudo(levelCounter);
			handleInput(actualLevel);
			monsterTurn();
		}
		freeMLevel(actualLevel);
	}
}

void exitGame()
{
	free(player);
	endwin();
}