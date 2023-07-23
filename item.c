#include "rogue.h"

enum rarity{
	COMMON = 6,
	RARE = 9
};

void createItems(level *newLevel)
{
	int i;
	
	newLevel->item = malloc(sizeof(item *) * newLevel->numItems);
	for(i = 0; i < newLevel->numItems; i++){
		newLevel->item[i] = malloc(sizeof(item));
		specifiesItems(newLevel, i);
		do{
			newLevel->item[i]->pos.y = rand() % HEIGHT_MAP;
			newLevel->item[i]->pos.x = rand() % WIDTH_MAP;
		}while(newLevel->map[newLevel->item[i]->pos.y][newLevel->item[i]->pos.x].icon != SPACE);
		
		mvaddch(newLevel->item[i]->pos.y, newLevel->item[i]->pos.x, newLevel->item[i]->icon);
	}
}

void specifiesItems(level *newLevel, int i)
{
	newLevel->item[i]->rarity = ((rand() % 10) + 1);
	
	if(newLevel->item[i]->rarity < RARE){
		newLevel->item[i]->icon = MED_KIT;
		newLevel->item[i]->color = COLOR_PAIR(COLOR_RED);
		newLevel->item[i]->lethality = 0;
		newLevel->item[i]->hp = 6;
		newLevel->item[i]->protection = 0;
		newLevel->item[i]->equipped = 0;
	}else if(newLevel->item[i]->rarity == RARE){
		newLevel->item[i]->icon = SPADE;
		newLevel->item[i]->color = COLOR_PAIR(COLOR_CYAN);
		newLevel->item[i]->lethality = 3;
		newLevel->item[i]->hp = 0;
		newLevel->item[i]->protection = 0;
		newLevel->item[i]->equipped = 0;
	}else{
		newLevel->item[i]->icon = ARMOR;
		newLevel->item[i]->color = COLOR_PAIR(COLOR_BLUE);
		newLevel->item[i]->lethality = 0;
		newLevel->item[i]->hp = 0;
		newLevel->item[i]->protection = DEF_MAX;
		newLevel->item[i]->equipped = 0;
	}
}

void grabItem()
{
	int i;
	
	for(i = 0; i < actualLevel->numItems; i++)
		if(player->pos.y == actualLevel->item[i]->pos.y && player->pos.x == actualLevel->item[i]->pos.x){
			player->hp += actualLevel->item[i]->hp;
			player->attack += actualLevel->item[i]->lethality;
			player->defense += actualLevel->item[i]->protection;
			discardItem(i);
		}
		limitEquippedItems();
}

void discardItem(int i)
{
	int j;
	
	for(j = i; j <actualLevel->numItems-1; j++)
		actualLevel->item[j] = actualLevel->item[j+1];
		actualLevel->item = realloc(actualLevel->item, sizeof(item *)*(actualLevel->numItems-1));
		actualLevel->numItems--;
}

void limitEquippedItems()
{
	if(player->attack > ATT_MAX)
		player->attack = ATT_MAX;
	if(player->defense > DEF_MAX)
		player->defense = DEF_MAX;
}