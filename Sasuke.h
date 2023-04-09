#ifndef SASUKE_H_
#define SASUKE_H_

#include "SDLFunc.h"
#include "Object.h"
#include "mapgame.h"

#define GRAVITY 0.4
#define MAX_FAIL 8
#define SPEED 8

class Sasuke : public Object
{
public:
	Sasuke();
	~Sasuke();
	enum Direction
	{
		Right = 0,
		Left = 1,
	};
	bool LoadImg(string path, SDL_Renderer* renderer);
	void Set_Frame();
	void Present(SDL_Renderer* des);
	void InputAction(SDL_Event events, SDL_Renderer* renderer);
	void Move(Map& mymap);
	void CheckVaCham(Map& mymap);
	void SetMoveMap(int x_map_, int y_map_) { x_map = x_map_; y_map = y_map_; };
	void MoveMap(Map& mymap);

	double x_value;
	double y_value;
	double x_pos;
	double y_pos;
	int width_character;
	int height_character;
	SDL_Rect gif[10];
	Input type_input;
	int CurrentIMG;
	int Direction;
	bool Stand_on_ground;
	int x_map;
	int y_map;
};

#endif