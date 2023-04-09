#include "Sasuke.h"

using namespace std;

SDL_Event mainevent;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_Texture* background = loadBackGround("NarutoBackground2.jpeg", renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    MapGame mapgame;
    mapgame.Load_Map("map/map01.dat");
    mapgame.Load_Tiles(renderer);

    Sasuke player;
    player.y_pos = 6*TILE_SIZE;
    player.LoadImg("Sasuke/sasuke_stand_right_official.png", renderer);
    player.Set_Frame();

    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&mainevent) != 0)
        {
            if (mainevent.type == SDL_QUIT)
            {
                quit = true;
            }
            player.InputAction(mainevent, renderer);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);

        Map mymap = mapgame.GetMap();
        player.SetMoveMap(mymap.start_x_, mymap.start_y_);
        player.Move(mymap);
        player.Set_Frame();
        player.Present(renderer);

        mapgame.SetMap(mymap);
        mapgame.Draw_Map(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_RenderPresent(renderer);
    //waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}







