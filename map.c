#include "rogue.h"

void createTiles(level *newLevel)
{
	unsigned int i, j;

	newLevel->map= calloc(HEIGHT_MAP, sizeof(tiles*));
	
	for(i = 0; i < HEIGHT_MAP; i++){
		newLevel->map[i] = calloc(WIDTH_MAP, sizeof(tiles));
		for(j = 0; j < WIDTH_MAP; j++){
			newLevel->map[i][j].icon = WALL;
			newLevel->map[i][j].color = COLOR_PAIR(COLOR_YELLOW);
			newLevel->map[i][j].walkable = 0;
			newLevel->map[i][j].visible = 0;
		}
	}
}

void configMap(level *newLevel)
{
	int i, y, x, height, width, numRooms;
	room *rooms; /* Poder-se-hia utilizar un vector normal em vez disso, ex.: room rooms[numRooms].
					Com isso evitar-se-hia a necessidade de alocação dinâmica de armazenamento ou memoria. */
	numRooms = (rand()%11) + 5;
	rooms = malloc(sizeof(room) * numRooms);
	
	for(i=0; i<numRooms; i++){
		y = (rand()%(HEIGHT_MAP-10)) + 1; /* Não se considera todo o tamanho do mapa para evitar overflow */
		x = (rand()%(WIDTH_MAP-20)) + 1;
		height = (rand()%7) + 3;
		width = (rand()%15) + 5;
		rooms[i] = createRoom(y, x, height, width);
		includeRoom(rooms[i], newLevel);
	
		if(i != 0)
		createCorridor(rooms[i-1].center, rooms[i].center, newLevel);
	}
	newLevel->initialPos.y = rooms[0].center.y;
	newLevel->initialPos.x = rooms[0].center.x;
	createCenter(newLevel);
	free(rooms);
}

room createRoom(int y, int x, int height, int width)
{
	room newRoom;
	
	newRoom.pos.y = y;
	newRoom.pos.x = x;
	newRoom.height = height;
	newRoom.width = width;
	newRoom.center.y = y + (height/2);
	newRoom.center.x = x + (width/2);
	
	return newRoom;
}

void includeRoom(room room, level *newLevel)
{
	int y, x;
	for(y = room.pos.y; y < room.pos.y + room.height; y++)
		for(x = room.pos.x; x < room.pos.x + room.width; x++){
			newLevel->map[y][x].icon = SPACE;
			newLevel->map[y][x].color = COLOR_PAIR(COLOR_WHITE);
			newLevel->map[y][x].walkable = 1;
			newLevel->map[y][x].visible = 0;
		}
}

void createCorridor(pos firstCenter, pos secondCenter, level *newLevel)
{
	pos temp;
	temp.y = firstCenter.y;
	temp.x = firstCenter.x;
	
	while(temp.y != secondCenter.y){
		temp.y += (secondCenter.y - firstCenter.y) / abs(secondCenter.y - firstCenter.y);
		newLevel->map[temp.y][temp.x].icon = SPACE;
		newLevel->map[temp.y][temp.x].color = COLOR_PAIR(COLOR_WHITE);
		newLevel->map[temp.y][temp.x].walkable = 1;
		newLevel->map[temp.y][temp.x].visible = 0;
	}
	while(temp.x != secondCenter.x){
		temp.x += (secondCenter.x - firstCenter.x) / abs(secondCenter.x - firstCenter.x);
		newLevel->map[temp.y][temp.x].icon = SPACE;
		newLevel->map[temp.y][temp.x].color = COLOR_PAIR(COLOR_WHITE);
		newLevel->map[temp.y][temp.x].walkable = 1;
		newLevel->map[temp.y][temp.x].visible = 0;
	}
}

void createCenter(level *newLevel)
{
	int posYExit, posXExit;
	
	do{
		posYExit = (rand() % (HEIGHT_MAP-2)) + 1;
		posXExit = (rand() % (WIDTH_MAP-2)) + 1;
	}while(newLevel->map[posYExit][posXExit].icon != SPACE); /* Há que se impedir que se gere monstro na room 0, que é a do player */
	
	newLevel->map[posYExit][posXExit].icon = EXIT;
	newLevel->map[posYExit][posXExit].color = COLOR_PAIR(COLOR_EXIT);
	newLevel->map[posYExit][posXExit].visible = 0;
}