#include "rogue.h"

int gameover = 0;

int main()
{	
	srand(time(NULL));
	configScr();
	player = createPlayer();
	gameLoop();
	exitGame();
	
	return 0;
}