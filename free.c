#include "rogue.h"

void freeMLevel(level *level)
{
	freeMMonster(level);
    freeMMap(level);
	free(level);
}

void freeMMap(level *level)
{
	unsigned int i;
	
	for(i = 0; i < HEIGHT_MAP; i++)
		free(level->map[i]);
	free(level->map);
}

void freeMMonster(level *level)
{
	unsigned int i;
	
	for(i = 0; i < level->numMonsters; i++)
		free(level->monster[i]);
	free(level->monster);
}

void freeMItems(level *level)
{
	int i;
	
	for(i = 0; i < level->numItems; i++)
		free(level->item[i]);
	free(level->item);
}