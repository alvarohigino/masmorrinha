#include "rogue.h"

void initialScreen(int levelCounter)
{
	FILE *file;
	char text[100];
	
	file = fopen("initial_scr.txt", "r");
	if(file == NULL)
		printw("Erro ao abrir arquivo");
	while(fgets(text, sizeof(text), file) != NULL)
		printw("%s", text);
	fclose(file);
	getch();
	fflush(stdin);
	clear();
}

void imprimirTudo(int levelCounter)
{
	createFOV(player, actualLevel);
	
	printMap();
	printItem();
	printPlayer(player);
	printMonster();
	
	destructFOV(player, actualLevel);
	mvprintw(25, 0, "HP: %d\tAtaque: %d\tArmadura: %d\tVelocidade: %d\tNivel: %d",
					player->hp, player->attack, player->defense, player->velocity, levelCounter);
}

void printMap()
{
	int i, j;
	
	for(i = 0; i < HEIGHT_MAP; i++){
		for(j = 0; j < WIDTH_MAP; j++){
			if(actualLevel->map[i][j].visible)
				mvaddch(i, j, actualLevel->map[i][j].icon | actualLevel->map[i][j].color);
			else
				mvaddch(i, j, ' ');
		}
	}
}

void printPlayer(pers* player)
{
	mvaddch(player->pos.y, player->pos.x, player->icon | player->color);
}

void printMonster()
{
	int i;
	
	for(i = 0; i < actualLevel->numMonsters; i++)
		if(actualLevel->monster[i]->visible)
			mvaddch(actualLevel->monster[i]->pos.y, actualLevel->monster[i]->pos.x, 
					actualLevel->monster[i]->icon | actualLevel->monster[i]->color);
		else
			mvaddch(actualLevel->monster[i]->pos.y, actualLevel->monster[i]->pos.x, ' ');
}

void printItem()
{
	int i;
	
	for(i = 0; i < actualLevel->numItems; i++)
		if(actualLevel->item[i]->visible)
			mvaddch(actualLevel->item[i]->pos.y, actualLevel->item[i]->pos.x,
					actualLevel->item[i]->icon | actualLevel->item[i]->color);
}