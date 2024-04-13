#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "main_Object.h"
#undef main 
using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int NUM_FRAMES = 8;
const int FRAME_DELAY = 100; // milliseconds

const int SCREEN_BPP = 32;

SDL_Surface* g_screen = NULL;
SDL_Event g_even;

bool Init();
void ApplySurface(SDL_Surface*, SDL_Surface*, int, int);
void CleanUp(base_Object);
SDL_Surface* resizeImage(SDL_Surface*, int, int);
SDL_Surface* SplitBackground(SDL_Surface*);

int main(int argc, char* argv[])
{
    bool is_quit = false;

    if (!Init())
        return 1;

    main_Object g_object;
    g_object.SetImage(g_object.LoadImage("Mine_03.png"));
    if (g_object.GetImage() == NULL)
        return 0;

    g_object.SetImage(resizeImage(g_object.GetImage(), 270, 175));
    g_object.SetImage(SplitBackground(g_object.GetImage()));
    ApplySurface(g_object.GetImage(), g_screen, 0, 0);

    // Load các frame ảnh vào một mảng
    SDL_Surface* frames[NUM_FRAMES];
    for (int i = 0; i < NUM_FRAMES; ++i) {
        std::string filename = "frame_" + std::to_string(i) + ".png";
        frames[i] = IMG_Load(filename.c_str());
        if (frames[i] == nullptr) {
            std::cerr << "Failed to load frame " << filename << "!" << std::endl;
            return 1;
        }
    }


    int currentFrame = 0;
    Uint32 lastFrameTime = 0;

    while (!is_quit)
    {
        while (SDL_PollEvent(&g_even))
        {
            if (g_even.type == SDL_QUIT)
            {
                is_quit = true; // Thoát nếu nhận được sự kiện thoát khỏi cửa sổ
                break;
            }
            else if (g_even.type == SDL_KEYDOWN && g_even.key.keysym.sym == SDLK_ESCAPE)
            {
                is_quit = true; // Thoát nếu nhấn phím ESC
                break;
            }
            g_object.Action(g_even);
        }

        // Kiểm tra xem đã đủ thời gian để chuyển sang khung hình mới chưa
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastFrameTime >= FRAME_DELAY) {
            // Chuyển sang khung hình tiếp theo
            currentFrame = (currentFrame + 1) % NUM_FRAMES;
            lastFrameTime = currentTime;
        }

        ApplySurface(frames[currentFrame], g_screen, 0, 0);
        ApplySurface(g_object.GetImage(), g_screen, g_object.GetX(), g_object.GetY());
        g_object.Move();

        // Cập nhật màn hình
        SDL_Flip(g_screen);
    }

    // Giải phóng bộ nhớ
    for (int i = 0; i < NUM_FRAMES; ++i) {
        SDL_FreeSurface(frames[i]);
    }

    CleanUp(g_object);
    SDL_Quit();
    return 1;
}

bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }
    g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (g_screen == NULL)
    {
        return false;
    }
    return true;
}

void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, NULL, des, &offset);
}

void CleanUp(base_Object g_object)
{
    SDL_FreeSurface(g_screen);
    SDL_FreeSurface(g_object.GetImage());
}

SDL_Surface* resizeImage(SDL_Surface* image, int newWidth, int newHeight) {
    SDL_Surface* newSurface = SDL_CreateRGBSurface(0, newWidth, newHeight, 32, 0, 0, 0, 0);
    if (newSurface == nullptr) {
        cerr << "Error creating new surface: " << SDL_GetError() << endl;
        return nullptr;
    }

    float scaleX = (float)newWidth / image->w;
    float scaleY = (float)newHeight / image->h;

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int oldX = (int)(x / scaleX);
            int oldY = (int)(y / scaleY);

            Uint32 pixel = ((Uint32*)image->pixels)[oldY * image->w + oldX];

            ((Uint32*)newSurface->pixels)[y * newWidth + x] = pixel;
        }
    }

    return newSurface;
}

SDL_Surface* SplitBackground(SDL_Surface* image)
{
    if (image != NULL)
    {
        Uint32 color_key = SDL_MapRGB(image->format, 179, 179, 179);
        SDL_SetColorKey(image, SDL_SRCCOLORKEY, color_key);
    }
    return image;
}
