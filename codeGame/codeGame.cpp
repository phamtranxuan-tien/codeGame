#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "main_Object.h"
#undef main 
using namespace std;

//Khai bao cac hang so
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int SCREEN_BPP = 32;

SDL_Surface* g_screen = NULL;
SDL_Event g_even;

//Khai bao ham
bool Init();

void ApplySurface(SDL_Surface*, SDL_Surface*, int, int);
void CleanUp(base_Object);
SDL_Surface* resizeImage(SDL_Surface*, int, int);
SDL_Surface* SplitBackground(SDL_Surface*);

int main(int argc, char* argv[])
{
    bool is_quit = false;

    Init();
    base_Object g_bkground;
    g_bkground.SetImage(g_bkground.LoadImageGIF("background_01.gif"));
    g_bkground.SetImage(resizeImage(g_bkground.GetImage(), 1280, 720));
    ApplySurface(g_bkground.GetImage(), g_screen, 0, 0);
    

    main_Object g_object;
    g_object.SetImage(g_object.LoadImage("Mine_03.png"));
    if (g_object.GetImage() == NULL)
        return 0;

    g_object.SetImage(resizeImage(g_object.GetImage(), 270 /2, 175 /2));
    g_object.SetImage(SplitBackground(g_object.GetImage()));
    ApplySurface(g_object.GetImage(), g_screen, 0, 0);

    int currentFrame = 0;
    int frameDelay = 1000; // Delay between frames in milliseconds
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
        ApplySurface(g_bkground.GetImage(), g_screen, 0, 0);
        // Get current time
        Uint32 currentTime = SDL_GetTicks();

        // Update frame if enough time has passed
        if (currentTime - lastFrameTime >= frameDelay)
        {
            // Move to the next frame
            currentFrame++;
            if (currentFrame >= g_bkground.GetImage()->w)
            {
                currentFrame = 0; // Loop back to the beginning
            }

            lastFrameTime = currentTime;
        }

        // Calculate source rectangle for current frame
        SDL_Rect srcRect = { currentFrame * g_bkground.GetImage()->w, 0, g_bkground.GetImage()->w, g_bkground.GetImage()->h };

        // Draw current frame of background GIF
        SDL_BlitSurface(g_bkground.GetImage(), &srcRect, g_screen, NULL);

        ApplySurface(g_object.GetImage(), g_screen, g_object.GetX(), g_object.GetY());
        g_object.Move();
        if (SDL_Flip(g_screen) == -1)
            return 0;
    }
    CleanUp(g_bkground);
    SDL_Quit();
    return 1;
}

// Kiểm tra lỗi khi khởi tạo SDL
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

// Load ảnh và kiểm tra lỗi


// Vẽ ảnh lên màn hình
void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, NULL, des, &offset);
}

// Free surface và thoát SDL
void CleanUp(base_Object g_bkground)
{
    SDL_FreeSurface(g_screen);
    SDL_FreeSurface(g_bkground.GetImage());
}

//Resize kích thước ảnh
SDL_Surface* resizeImage(SDL_Surface* image, int newWidth, int newHeight) {
    // Tạo một surface mới với kích thước mới
    SDL_Surface* newSurface = SDL_CreateRGBSurface(0, newWidth, newHeight, 32, 0, 0, 0, 0);
    if (newSurface == nullptr) {
        cerr << "Error creating new surface: " << SDL_GetError() << endl;
        return nullptr;
    }

    // Tính toán tỷ lệ scale
    float scaleX = (float)newWidth / image->w;
    float scaleY = (float)newHeight / image->h;

    // Lặp qua từng pixel của surface mới và sao chép giá trị pixel từ surface cũ
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Tính toán tọa độ tương ứng trên surface cũ
            int oldX = (int)(x / scaleX);
            int oldY = (int)(y / scaleY);

            // Lấy màu pixel từ surface cũ
            Uint32 pixel = ((Uint32*)image->pixels)[oldY * image->w + oldX];

            // Đặt màu pixel vào surface mới
            ((Uint32*)newSurface->pixels)[y * newWidth + x] = pixel;
        }
    }

    return newSurface;
}

//Tách nền xanh cho nhân vật
SDL_Surface* SplitBackground(SDL_Surface* image)
{
    if (image != NULL)
    {
        Uint32 color_key = SDL_MapRGB(image->format, 179, 179, 179);
        SDL_SetColorKey(image, SDL_SRCCOLORKEY, color_key);
    }
    return image;
}
