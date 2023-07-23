#include "rogue.h"

pers *player;

pers *createPlayer()
{
	pers *newPlayer = calloc(1, sizeof(pers));
	
	if(newPlayer == NULL)
		mvprintw(20, 20, "Problemas na alocacao de armazenamento");
	else{
		newPlayer->icon = PLAYER;
		newPlayer->color = COLOR_PAIR(COLOR_GREEN);
		newPlayer->hp = 10;
		newPlayer->attack = 6;
		newPlayer->strength = 2;
		newPlayer->defense = 0;
		return newPlayer;
	}
}

void putPlayer(level *actualLevel)
{	
	player->pos.y = actualLevel->initialPos.y;
	player->pos.x = actualLevel->initialPos.x;
	player->icon = PLAYER;
	mvaddch(player->pos.y, player->pos.x, player->icon);
	actualLevel->map[actualLevel->initialPos.y][actualLevel->initialPos.x].walkable = 0;
	createFOV(player, actualLevel);
}

void handleInput(level *actualLevel)
{
	pos newPos;
	newPos.y = player->pos.y;
	newPos.x = player->pos.x;
	
	switch(getch()){
		case 'w':
		case 'W':
			newPos.y--;
			break;
		case 's':
		case 'S':
			newPos.y++;
			break;
		case 'a':
		case 'A':
			newPos.x--;
			break;
		case 'd':
		case 'D':
			newPos.x++;
			break;
		case 27:
			gameover = 1;
			return;
		case 'f':
		case 'F':
			interage();
			return;
		default:
			return;
	}
	movePlayer(player, newPos, actualLevel);
}

void movePlayer(pers *player, pos newPos, level *actualLevel)
{
	if(actualLevel->map[newPos.y][newPos.x].walkable){
		actualLevel->map[player->pos.y][player->pos.x].walkable = 1;
		player->pos.y = newPos.y;
		player->pos.x = newPos.x;
		actualLevel->map[newPos.y][newPos.x].walkable = 0;
	}else{
		playerAttck(newPos);
	}
}

void interage()
{
		if(actualLevel->map[player->pos.y][player->pos.x].icon == EXIT)
			actualLevel->finalized = 1;
		else
			grabItem();
}