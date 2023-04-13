#include "Sasuke.h"

int frame_number(Input in)
{
	if (in.jump == 1) return 6;
	else if (in.fall == 1) return 6;
	else if (in.stand == 1) return 8;
	else if (in.run == 1) return 10;
}

Sasuke::Sasuke()
{
	CurrentIMG = 0;
	x_pos = 0;
	y_pos = 0;
	x_value = 0;
	y_value = 0;
	width_character = 0;
	height_character = 0;
	Direction = -1;
	type_input.stand = 1;
	type_input.run = 0;
	type_input.jump = 0;
	type_input.hold = 0;
	type_input.normal_attack = 0;
	Stand_on_ground = false;
	x_map = 0;
	y_map = 0;
	y_ground = 0;
	type_input.fall = 0;
	death = false;
}
Sasuke::~Sasuke()
{

}

bool Sasuke::LoadImg(string path, SDL_Renderer* renderer)
{
	bool loadedimg = Object::LoadImg(path, renderer);
	if (loadedimg == true)
	{
		width_character = rect_.w/frame_number(type_input);
		height_character = rect_.h;
	}
	return loadedimg;
}

void Sasuke::Set_Frame()
{
	int frame_number_ = frame_number(type_input);
	for (int i = 0; i < frame_number_; i+=1)
	{
		gif[i].x = i * width_character;
		gif[i].y = 0;
		gif[i].w = width_character;
		gif[i].h = height_character;
	}
}

void Sasuke::Present(SDL_Renderer* des)
{
	if (Direction == Left)
	{
		if (type_input.jump == 1 ) LoadImg("Sasuke/sasuke_jump_up_left.png", des);
		else if (type_input.fall == 1 ) LoadImg("Sasuke/sasuke_jump_down_left.png", des);
		else if (type_input.stand == 1) {
			LoadImg("Sasuke/sasuke_stand_left_official.png", des); SDL_Delay(50);
		}
		else if ( type_input.run == 1 ) LoadImg("Sasuke/sasuke_run_left_official.png", des);
	}
	else
	{
		if (type_input.jump == 1 ) LoadImg("Sasuke/sasuke_jump_up_right.png", des);
		else if (type_input.fall == 1 ) LoadImg("Sasuke/sasuke_jump_down_right.png", des);
		else if (type_input.stand == 1) {
			LoadImg("Sasuke/sasuke_stand_right_official.png", des); SDL_Delay(50);
		}
		else if (type_input.run == 1) LoadImg("Sasuke/sasuke_run_right_official.png", des);
	}
	CurrentIMG++;
	if ( CurrentIMG >= frame_number(type_input) ) CurrentIMG = 0;
	rect_.x = x_pos - x_map;
	rect_.y = y_pos - y_map;
	SDL_Rect* current_clip = &gif[CurrentIMG];
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_character, height_character };
	SDL_RenderCopy(des, myobject, current_clip, &renderQuad);
}

void Sasuke::InputAction(SDL_Event events, SDL_Renderer* renderer)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_w:
		{
			if (Stand_on_ground == true) { type_input.jump = 1; y_ground = y_pos; Stand_on_ground = false; }
		}
		break;
		case SDLK_d:
		{
			if (!Stand_on_ground && Direction == Left && x_value != 0) break;
			else
			{
				Direction = Right;
				type_input.run = 1;
				type_input.stand = 0;
			}
		}
		break;
		case SDLK_a:
		{
			if (!Stand_on_ground && Direction == Right && x_value != 0) break;
			else
			{
				Direction = Left;
				type_input.run = 1;
				type_input.stand = 0;
			}
		}
		break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_w:
		{
			type_input.fall = 1;
			type_input.jump = 0;
		}
		break;
		default:
		{
			type_input.run = 0;
			type_input.stand = 1;
		}
		break;
		}
	}
}

void Sasuke::Move(Map& mymap)
{
	x_value = 0;
	y_value += GRAVITY;

	if (y_value >= MAX_FAIL) y_value = MAX_FAIL;
	if (type_input.run == 1 && Direction == Right)
	{
		x_value += SPEED;
	} else if (type_input.run == 1 && Direction == Left)
	{
		x_value -= SPEED;
	}
	if (type_input.jump == 1)
	{
		y_value -= JUMPSPEED;
	} else if (type_input.fall == 1 )
	{
		y_value += JUMPSPEED;
	}
	CheckVaCham(mymap);
	MoveMap(mymap);
}

void Sasuke::CheckVaCham(Map& mymap)
{
	int x1 = (x_pos + x_value)/TILE_SIZE; 
	int y1 = y_pos/TILE_SIZE;
	int x2 = (x_pos + x_value + TILE_SIZE )/TILE_SIZE;
	int y2 = (y_pos + TILE_SIZE )/TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_X && y1 >= 0 && y2 < MAX_Y)
	{
		if (x_value > 0) //di sang phai
		{
			if (mymap.tile[y1][x2] != 0 && mymap.tile[y2][x2] != 0 )
			{
				x_pos = x2 * TILE_SIZE;
				x_pos -= TILE_SIZE;
				x_value = 0;
			}
		}
		else if (x_value < 0)
		{
			if (mymap.tile[y1][x1] != 0 && mymap.tile[y2][x1] != 0)
			{
				x_pos = (x1 + 1) * TILE_SIZE;
				x_value = 0;
			}
		}
	}

	x1 = (x_pos) / TILE_SIZE;
	y1 = (y_pos + y_value) / TILE_SIZE;
	x2 = (x_pos + width_character ) / TILE_SIZE;
	y2 = (y_pos + y_value + TILE_SIZE ) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_X && y1 >= 0 && y2 < MAX_Y)
	{
		if (y_value > 0) //roi xuong
		{
			if (mymap.tile[y2][x1] == 3 || mymap.tile[y2][x2] == 3)
			{
				y_pos = y2 * TILE_SIZE;
				y_pos -= TILE_SIZE;
				y_value = 0;
				Stand_on_ground = true;
				type_input.fall = 0;
			}
			else {Stand_on_ground = false;}
		}
		else if (y_value < 0)
		{
			if (mymap.tile[y1][x1] != 0 || mymap.tile[y1][x2] != 0  )
			{
				y_pos = (y1 + 1) * TILE_SIZE;
				y_value = 0;
			}
		}
	}

	x_pos += x_value;
	y_pos += y_value;

	if (y_ground - y_pos >= MAXJUMP && !Stand_on_ground)
	{
		type_input.jump = 0;
		type_input.fall = 1;
	}

	if (x_pos < 0) x_pos = 0;
	else if (x_pos + width_character > MAX_X * TILE_SIZE) x_pos = MAX_X * TILE_SIZE - width_character ;
	if (y_pos < 0) y_pos = 0;
	else if (y_pos + height_character > MAX_Y * TILE_SIZE) { y_pos = (MAX_Y+1) * TILE_SIZE - height_character; death = true; };
}

void Sasuke::MoveMap(Map& mymap)
{
	mymap.start_x_ = x_pos - (SCREEN_WIDTH / 2);
	if (mymap.start_x_ < 0) mymap.start_x_ = 0;
	else if (mymap.start_x_ + SCREEN_WIDTH >= (MAX_X * TILE_SIZE))
	{
		mymap.start_x_ = (MAX_X * TILE_SIZE) - SCREEN_WIDTH;
	}
	mymap.start_y_ = y_pos - (SCREEN_HEIGHT / 2);
	if (mymap.start_y_ < 0) mymap.start_y_ = 0;
	else if (mymap.start_y_ + SCREEN_HEIGHT >= (MAX_Y * TILE_SIZE))
	{
		mymap.start_y_ = (MAX_Y * TILE_SIZE) - SCREEN_HEIGHT;
	}
}