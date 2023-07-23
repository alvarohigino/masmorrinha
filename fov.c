#include "rogue.h"

int raio = 7;

void createFOV(pers *player, level *actualLevel)
{
	int y, x;
	
	for(y = player->pos.y - raio; y <= player->pos.y + raio; y++)
		for(x = player->pos.x - raio; x <= player->pos.x + raio; x++)
			if(pow(y - player->pos.y, 2) + pow(x - player->pos.x, 2) <= pow(raio, 2))
				if(isInMap(y, x)){
					actualLevel->map[y][x].visible = 1;
					seeRest();
				}
}

void destructFOV(pers *player, level *actualLevel)
{
	int y, x;
	
	for(y = player->pos.y - raio; y <= player->pos.y + raio; y++)
		for(x = player->pos.x - raio; x <= player->pos.x + raio; x++)
			if(isInMap(y, x))
				actualLevel->map[y][x].visible = 0;
}

int isInMap(int y, int x){
	if ((y >= 0 && y < HEIGHT_MAP) && (x >= 0 && x < WIDTH_MAP))
		return 1;
	return 0;
}

void seeRest()
{
	int i;
	
	seeMonster(i);
	seeItem(i);
}

void seeMonster(int i)
{
	for(i = 0; i < actualLevel->numMonsters; i++)
		if(actualLevel->map[actualLevel->monster[i]->pos.y][actualLevel->monster[i]->pos.x].visible)
			actualLevel->monster[i]->visible = 1;
		else
			actualLevel->monster[i]->visible = 0;
}

void seeItem(int i)
{
	for(i = 0; i < actualLevel->numItems; i++)
		if(actualLevel->map[actualLevel->item[i]->pos.y][actualLevel->item[i]->pos.x].visible)
			actualLevel->item[i]->visible = 1;
		else
			actualLevel->item[i]->visible = 0;
}