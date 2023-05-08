#ifndef BARS_H_
#define BARS_H_

#include "Sasuke.h"

class Bars : public Object
{
public:

	Bars();
	~Bars();
	bool LoadImg(string path, SDL_Renderer* renderer);
	void Set_Frame();
	void Present(Sasuke sake,SDL_Renderer* des);
	enum type
	{
		Health = 0,
		Mana = 1,
	};
	void set_type(int _type) { type = _type; }

private:
	int width_bar;
	int height_bar;
	SDL_Rect gif[30];
	int CurrentIMG;
	int x_map;
	int y_map; 
	int type;
};



#endif