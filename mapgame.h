#ifndef MAP_GAME_H_
#define MAP_GAME_H_

#include "SDLFunc.h"
#include "Object.h"

#define MAX_TILES 10

using namespace std;

class TileMat : public Object
{
public:
	TileMat() { ; }
	~TileMat() { ; }
};

class MapGame
{
	Map map_game_;
	TileMat tile_mat[MAX_TILES];
public:
	MapGame() { ; }
	~MapGame() { ; }
	Map GetMap() { return map_game_; }
	void SetMap(Map mymap) { map_game_ = mymap; };
	void Load_Map(const char* name);
	void Load_Tiles(SDL_Renderer* renderer);
	void Draw_Map(SDL_Renderer* renderer);
};

#endif
