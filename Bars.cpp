#include "Bars.h"

int frame_number(int type_)
{
	if (type_ == 0) return 8;
}

Bars::Bars()
{
	width_bar=0;
	height_bar=0;
	SDL_Rect gif[30];
	CurrentIMG=0;
	x_map=0;
	y_map=0;
	type = -1;
}

Bars::~Bars()
{

}

bool Bars::LoadImg(string path, SDL_Renderer* renderer)
{
	bool loadedimg = Object::LoadImg(path, renderer);
	if (loadedimg == true)
	{
		width_bar = rect_.w / frame_number(type);
		height_bar = rect_.h;
	}
	return loadedimg;
}

void Bars::Set_Frame()
{
	int frame_number_ = frame_number(type);
	for (int i = 0; i < frame_number_; i += 1)
	{
		gif[i].x = i * width_bar;
		gif[i].y = 0;
		gif[i].w = width_bar;
		gif[i].h = height_bar;
	}
}

void Bars::Present(Sasuke sake,SDL_Renderer* des)
{
	if (type == Health)
	{
		LoadImg("Bars/HealthBar.png", des);
	}
	if (sake.changeHealthBar) CurrentIMG++;
	rect_.x = x_map;
	rect_.y = y_map;
	SDL_Rect* current_clip = &gif[CurrentIMG];
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_bar, height_bar };
	SDL_RenderCopy(des, myobject, current_clip, &renderQuad);
}

