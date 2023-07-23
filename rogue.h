#ifndef ROGUE_H
#define ROGUE_H

#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define HEIGHT_MAP 25
#define WIDTH_MAP 80
#define WALL '#'
#define SPACE '.'
#define EXIT '>'
#define PLAYER '@'
#define MED_KIT '+'
#define SPADE '/'
#define ARMOR '%'
#define ATT_MAX 9
#define DEF_MAX 3

#define COLOR_EXIT 9

typedef struct{
	int y, x;
}pos;

typedef struct{
	char icon;
	int color;
	int walkable;
	int visible;
}tiles;

typedef struct{
	pos pos;
	char icon;
	int color;
	int hp;
	int attack;
	int strength;
	int velocity;
	int defense;
}pers;

typedef struct{
	int height, width;
	pos pos;
	pos center;
}room;

typedef struct{
	pos pos;
	char icon;
	int color;
	int hp;
	int attack;
	int velocity;
	int vivit;
	int visible;
}mons;

typedef struct{
	pos pos;
	char icon;
	int color;
	int rarity;
	int lethality;
	int hp;
	int protection;
	int equipped;
	int visible;
}item;

typedef struct{
	tiles **map;
	int numRooms;
	mons **monster;
	int numMonsters;
	item **item;
	int numItems;
	pos initialPos;
	int finalized;
}level;

/* Variaveis externas */
extern pers *player;
extern int gameover;
level *actualLevel;

/* Declarações das funcções de level.c */
level *createLevel();
void calculateNumMons(level *newLevel);
void calculateNumItems(level *newLevel);

/* Declaraçõesdas funções de map.c */
void createTiles(level *newLevel);
void configMap(level *newLevel);
room createRoom(int y, int x, int height, int width);
void includeRoom(room room, level *newLevel);
void createCorridor(pos firstCenter, pos secondCenter, level *newLevel);
void createCenter(level *newLevel);

/* Declaração das funcções de player.c */
pers *createPlayer();
void putPlayer(level *actualLevel);
void handleInput(level *actualLevel);
void movePlayer(pers *player, pos newPos, level *actualLevel);
void interage();

/* Declaração das funcções de motor.c */
void configScr();
void gameLoop();
void exitGame();

/* Declarações das funcções de monster.c */
void createMonster(level *newLevel);
void monsterTurn();
void moveMonster(pos newPos, int i);
void specifiesMonster(level *newLevel, int i);

/* Declarações das funcções de item.c */
void createItems(level *newLevel);
void specifiesItems(level *newLevel, int i);
void grabItem();
void discardItem(int i);
void limitEquippedItems();

/* Declarações das funcções de combate.c */
void playerAttck(pos newPos);
void killMonster(int i);
void varAttaJog(int *varAtt);
void varAttMons(int *varAtt, int i);
void reallocMonsters(int i);
void monsterAttck(pos newPos, int i);
void historic(int option, int action);

/* Declarações das funcções de impressao.c */
void initialScreen();
void printMap();
void printPlayer(pers *player);
void printMonster();
void printItem();
void imprimirTudo(int levelCounter);

/* Declarações de funccões de fov.c */
void createFOV(pers *player, level *actualLevel);
void destructFOV(pers *player, level *actualLevel);
int isInMap(int y, int x);
void seeRest();
void seeMonster(int i);
void seeItem(int i);

/* Declarações das funcções de free.c */
void freeMMonster(level *level);
void freeMMap(level *level);
void freeMLevel(level *level);

#endif