#include "Function.h"

SDL_Surface* screen = NULL;
SDL_Event event = {};
//play = 0: chua choi, 1: dang choi //-1 :man hinh choi lai
int Play = 0;

int  y_val = 0, x_val = 0;

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

    //Khoi tao am thanh
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL audio: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        return 1;
    }
    return true;
}

// Free surface va thoat SDL
void CleanUp(base_Object bkground)
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(bkground.GetImage());
}

//Resize anh
SDL_Surface* resizeImage(SDL_Surface* image, int newWidth, int newHeight)
{
    // Tao mot surface moi voi kich thuoc moi
    SDL_Surface* newSurface = SDL_CreateRGBSurface(0, newWidth, newHeight, 32, 0, 0, 0, 0);
    if (newSurface == nullptr) {
        cerr << "Error creating new surface: " << SDL_GetError() << endl;
        return nullptr;
    }

    // Tinh toan ty le scale
    float scaleX = (float)newWidth / image->w;
    float scaleY = (float)newHeight / image->h;

    // Lap qua tung pixel cua surface moi va sao cheo gia tri pixel tu surface cu
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Tinh toan toa đo tuong ung trên surface cu
            int oldX = (int)(x / scaleX);
            int oldY = (int)(y / scaleY);

            // Lay mau pixel tu surface cu
            Uint32 pixel = ((Uint32*)image->pixels)[oldY * image->w + oldX];

            // Đat mau pixel vao surface moi
            ((Uint32*)newSurface->pixels)[y * newWidth + x] = pixel;
        }
    }

    return newSurface;
}

