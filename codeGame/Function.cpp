#include "Function.h"

SDL_Surface* screen = NULL;
SDL_Event event = {};

//Ve anh len man hinh
void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, NULL, des, &offset);
}

// Kiem tra loi khi khoi tao SDL
bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (screen == NULL)
    {
        return false;
    }
    return true;
}

// Free surface va thoat SDL
void CleanUp(base_Object bkground)
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(bkground.GetImage());
}

