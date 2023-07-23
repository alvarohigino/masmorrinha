#include "rogue.h"

void createMonster(level *newLevel)
{
	int i;
	
	newLevel->monster = malloc(sizeof(mons *) * newLevel->numMonsters);
	for(i = 0; i < newLevel->numMonsters; i++) {
		newLevel->monster[i] = malloc(sizeof(mons));
		specifiesMonster(newLevel, i);
		do{
			newLevel->monster[i]->pos.y = rand() % HEIGHT_MAP;
			newLevel->monster[i]->pos.x = rand() % WIDTH_MAP;
        }while(newLevel->map[newLevel->monster[i]->pos.y][newLevel->monster[i]->pos.x].icon != SPACE);
		
		mvaddch(newLevel->monster[i]->pos.y, newLevel->monster[i]->pos.x, newLevel->monster[i]->icon);
		newLevel->map[newLevel->monster[i]->pos.y][newLevel->monster[i]->pos.x].walkable = 0;
    }
}

void monsterTurn()
{
	pos newPos;
	int i;

	for(i=0; i<actualLevel->numMonsters; i++){
			newPos.y = actualLevel->monster[i]->pos.y;
			newPos.x = actualLevel->monster[i]->pos.x;
			if(actualLevel->monster[i]->pos.y > player->pos.y)
				newPos.y--;
			else if(actualLevel->monster[i]->pos.y < player->pos.y)
				newPos.y++;
			else if(actualLevel->monster[i]->pos.x > player->pos.x)
				newPos.x--;
			else if(actualLevel->monster[i]->pos.x < player->pos.x)
				newPos.x++;
			moveMonster(newPos, i);
	}
}

void moveMonster(pos newPos, int i)
{
	if(actualLevel->map[newPos.y][newPos.x].walkable) {
		actualLevel->map[actualLevel->monster[i]->pos.y][actualLevel->monster[i]->pos.x].walkable = 1;
		actualLevel->monster[i]->pos.y = newPos.y;
		actualLevel->monster[i]->pos.x = newPos.x;
		actualLevel->map[newPos.y][newPos.x].walkable = 0;
	}else
		monsterAttck(newPos, i);
}

void specifiesMonster(level *newLevel, int i)
{
	int especie = rand() % 4;
	
	switch(especie){
		case 0:
			newLevel->monster[i]->icon = 'R';
			newLevel->monster[i]->color = COLOR_PAIR(COLOR_MAGENTA);
			newLevel->monster[i]->hp = 4;
			newLevel->monster[i]->attack = 3;
			break;
		case 1:
			newLevel->monster[i]->icon = 'A';
			newLevel->monster[i]->color = COLOR_PAIR(COLOR_MAGENTA);
			newLevel->monster[i]->hp = 6;
			newLevel->monster[i]->attack = 4;
			break;
		case 2:
			newLevel->monster[i]->icon = 'S';
			newLevel->monster[i]->color = COLOR_PAIR(COLOR_MAGENTA);
			newLevel->monster[i]->hp = 8;
			newLevel->monster[i]->attack = 5;
			break;
		case 3:
			newLevel->monster[i]->icon = 'M';
			newLevel->monster[i]->color = COLOR_PAIR(COLOR_MAGENTA);
			newLevel->monster[i]->hp = 10;
			newLevel->monster[i]->attack = 8;
			break;
	}
}