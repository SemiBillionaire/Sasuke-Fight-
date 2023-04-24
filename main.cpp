#include "Sasuke.h"
#include "TimeManage.h"
#include "Monster.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event mainevent;

vector<Monster*> Monster_list(int number, int type, double x1, double x2)
{
    vector<Monster*> list_monster;
    Monster* mon = new Monster[20];
    string path;
    if (type == 1) path = "Monster/1/m1_run_left.png";
    for (int i = 0; i < number; i++)
    {
        Monster* new_monster = (mon + i);
        new_monster->set_type(type);
        if (new_monster != NULL)
        {
            new_monster->LoadImg(path, renderer);
            new_monster->set_clips();
            new_monster->set_x_pos((x1 + i * ((x2 - x1) / number))*TILE_SIZE);
            new_monster->set_Mid(new_monster->get_x_pos());
            new_monster->set_y_pos(2*TILE_SIZE);
            new_monster->set_range(new_monster->get_x_pos());
            new_monster->set_Mon_HP(type);
            list_monster.push_back(new_monster);
        }
    }
    return list_monster;
}

void set_Monster(vector<Monster*>& list_monster, Map mymap, Sasuke& player)
{
    for (int i = 0; i < list_monster.size(); i++)
    {
        Monster* mymon = list_monster[i];
            if (mymon != nullptr && mymon->Meet_Sasuke_(mymap))
            {
                mymon->SetMapXY(mymap.start_x_, mymap.start_y_);
                mymon->MonsterMove(mymap);
                if (player.x_pos < mymon->get_begin() || player.x_pos > mymon->get_end())
                {
                    mymon->MoveAround();
                }
                else
                {
                    mymon->Action(player);
                    mymon->Attack(player);
                    mymon->Is_Attacked(player);
                }
                mymon->Present(renderer);
            }
            else if (mymon != nullptr && !(mymon->Meet_Sasuke_(mymap)))
            {
                if (player.x_pos + SCREEN_WIDTH >= mymon->get_x_pos())
                {
                    mymon->SetMapXY(mymap.start_x_, mymap.start_y_);
                    mymon->MonsterMove(mymap);
                    mymon->MoveAround();
                    mymon->Present(renderer);
                }
            }
            if (mymon != nullptr && mymon->Is_Dead())
            {
                list_monster[i] = nullptr;
            }
        }
}

int main(int argc, char* argv[])
{
    Time maintime;
    initSDL(window, renderer);
    SDL_Texture* background = loadBackGround("NarutoBackground2.jpeg", renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    MapGame mapgame;
    mapgame.Load_Map("map/map.dat");
    mapgame.Load_Tiles(renderer);

    vector<Monster*> monster1_turn_1 = Monster_list(4, 1, 105, 117);
    vector<Monster*> monster1_turn_2 = Monster_list(3, 1, 165, 171);
    vector<Monster*> monster1_turn_3 = Monster_list(2, 1, 243, 245);

    Sasuke player;
    player.y_pos = 0*TILE_SIZE;
    //player.x_pos =106 * TILE_SIZE;
    player.LoadImg("Sasuke/sasuke_stand_right_official.png", renderer);
    player.Set_Frame();

    bool quit = false;
    while (!quit)
    {
        maintime.begin();
        while (SDL_PollEvent(&mainevent) != 0)
        {
            if (mainevent.type == SDL_QUIT)
            {
                quit = true;
            }
            if (player.death) quit = true;
            player.InputAction(mainevent, renderer);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);

        Map mymap = mapgame.GetMap();
        player.SetMoveMap(mymap.start_x_, mymap.start_y_);
        player.Move(mymap);
        player.Attacked();
        player.Set_Frame();
        player.Collect_Point(mymap);
        player.Present(renderer);

        player.Is_Attacked_Left = false;
        player.Is_Attackef_Right = false;

        mapgame.SetMap(mymap);
        mapgame.Draw_Map(renderer);
        
        set_Monster(monster1_turn_1, mymap, player);
        set_Monster(monster1_turn_2, mymap, player);
        set_Monster(monster1_turn_3, mymap, player);

        SDL_RenderPresent(renderer);

        int real_time = maintime.get_time();
        if (real_time < time_present_one_frame)
        {
            SDL_Delay(time_present_one_frame - real_time);
        }
    }

    quitSDL(window, renderer);
    return 0;
}







