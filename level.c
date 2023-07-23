/* Falta criar uma maneira de calcular o número de sessões/rooms */

#include "rogue.h"

int levelCounter = 0;

level *createLevel()
{
	level *newLevel = malloc(sizeof(level));
	/* Config. do novo level */
	levelCounter += 1;
	createTiles(newLevel);
	configMap(newLevel);
	calculateNumMons(newLevel);
	createMonster(newLevel);
	calculateNumItems(newLevel);
	createItems(newLevel);
	newLevel->finalized = 0;
	
	return newLevel;
}

void calculateNumMons(level *newLevel)
{
	newLevel->numMonsters = ((rand() % 4) + 2);
	newLevel->numMonsters = (int)(newLevel->numMonsters + (newLevel->numMonsters * levelCounter/10));
}

void calculateNumItems(level *newLevel)
{
	newLevel->numItems = ((rand() % 4) + 1);
	newLevel->numItems = (int)(newLevel->numItems + (newLevel->numItems * levelCounter/10));
}