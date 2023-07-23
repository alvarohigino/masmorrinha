#include "rogue.h"

void playerAttck(pos newPos)
{
	int i, finalAttck;
	
	for(i = 0; i < actualLevel->numMonsters; i++)
		if(newPos.y == actualLevel->monster[i]->pos.y && newPos.x == actualLevel->monster[i]->pos.x){
			varAttaJog(&finalAttck);
			actualLevel->monster[i]->hp -= finalAttck;
			historic(1, finalAttck);
			if(actualLevel->monster[i]->hp <= 0)
				killMonster(i);
		}
}

void monsterAttck(pos newPos, int i)
{
	int finalAttck;
	
	if(newPos.y == player->pos.y && newPos.x == player->pos.x){
		varAttMons(&finalAttck, i);
		player->hp -= finalAttck;
		historic(2, finalAttck);
		if(player->hp <= 0)
			gameover = 1;
	}
}

void varAttaJog(int *varAtt) /* Variação do ataque do jog. */
{
	*varAtt = (player->attack + rand() % (player->attack*4/10) - (player->attack*2/10));
}

void varAttMons(int *varAtt, int i) /* Variação do ataque do mons. */
{
	*varAtt = (actualLevel->monster[i]->attack + rand() %
							(actualLevel->monster[i]->attack*4/10) - (actualLevel->monster[i]->attack*2/10))-player->defense;
}

void killMonster(int i)
{
	actualLevel->map[actualLevel->monster[i]->pos.y][actualLevel->monster[i]->pos.x].walkable = 1;
	actualLevel->monster[i]->vivit = 0;
	
	/*free(actualLevel->monster[i]);*/ /* Isso num é necessario, pois eu reposiciono os monstros e depois libero realocando o ultimo */
	reallocMonsters(i);
}

void reallocMonsters(int i)
{
	int j; /* Esse J é desnecessario */
	for(j = i; j < actualLevel->numMonsters - 1; j++)
		actualLevel->monster[j] = actualLevel->monster[j + 1];
		actualLevel->monster = realloc(actualLevel->monster, sizeof(mons *)*(actualLevel->numMonsters-1));
		actualLevel->numMonsters--;
}

void historic(int option, int action)
{
		if(option == 1)
			mvprintw(27, 0, "Voce deu %d de damno", action);
		else
			mvprintw(28, 0, "Voce soffreu %d de damno", action);
}