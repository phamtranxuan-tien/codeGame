#include "base_Object.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
using namespace std;
//Test lan 3
base_Object::base_Object()
{
    x = 0;
    y = 0;
    image = NULL;
}

SDL_Surface* base_Object::LoadImageGIF2(const char* file_path)
//SDL_Surface* base_Object::LoadImageGIF2(string file_path)
{
    // Load hình ảnh từ file
//    SDL_Surface* loaded_image = IMG_Load(file_path.c_str());
    SDL_Surface* loaded_image = IMG_Load(file_path);
    if (!loaded_image)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", file_path, IMG_GetError());
        return NULL;
    }

    // Optimize hình ảnh
    SDL_Surface* optimized_image = SDL_ConvertSurface(loaded_image, loaded_image->format, 0);
    SDL_FreeSurface(loaded_image); // Giải phóng bộ nhớ cho hình ảnh đã tải

    return optimized_image;
}

SDL_Surface* base_Object::LoadImageGIF1(string file_path) {
    // Open the GIF file to read data
    SDL_RWops* file = SDL_RWFromFile(file_path.c_str(), "rb");
    if (file == NULL) {
        cout << "SDL_RWFromFile Error: " << SDL_GetError() << endl;
        return nullptr;
    }

    // Load the image from the GIF file into an SDL_Surface
    SDL_Surface* loaded_image = IMG_LoadGIF_RW(file);
    if (loaded_image == nullptr) {
        cout << "IMG_LoadGIF_RW Error: " << IMG_GetError() << endl;
        SDL_RWclose(file); // Close SDL_RWops before returning
        return nullptr;
    }

    // Close the SDL_RWops and return the loaded image directly without optimization
    SDL_RWclose(file);
    return loaded_image;
}


SDL_Surface* base_Object::LoadImageGIF(string file_path) {
    // Mở tệp GIF để đọc dữ liệu
    SDL_RWops* file = SDL_RWFromFile(file_path.c_str(), "rb");
    if (file == NULL) {
        cout << "SDL_RWFromFile Error: " << SDL_GetError() << endl;
        return nullptr;
    }

    // Tải hình ảnh từ tệp GIF vào một SDL_Surface
    SDL_Surface* loaded_image = IMG_LoadGIF_RW(file);
    if (loaded_image == nullptr) {
        cout << "IMG_LoadGIF_RW Error: " << IMG_GetError() << endl;
        SDL_RWclose(file); // Đóng SDL_RWops trước khi trả về
        return nullptr;
    }

    // Optimize hình ảnh
    SDL_Surface* optimized_image = SDL_DisplayFormat(loaded_image);
    if (optimized_image == nullptr) {
        cout << "SDL_DisplayFormat Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(loaded_image);
        SDL_RWclose(file); // Đóng SDL_RWops trước khi trả về
        return nullptr;
    }

    // Giải phóng bộ nhớ của hình ảnh gốc và đóng SDL_RWops
    SDL_FreeSurface(loaded_image);
    SDL_RWclose(file);

    return optimized_image;
}


SDL_Surface* base_Object::LoadImage(string file_path)
{
    // Load anh tu duong dan
    SDL_Surface* loaded_image = IMG_Load(file_path.c_str());
    if (loaded_image == nullptr)
    {
        cout << "IMG_Load Error: " << IMG_GetError() << endl;
        return nullptr;
    }

    // Optimize anh
    SDL_Surface* optimized_image = SDL_DisplayFormat(loaded_image);
    if (optimized_image == nullptr)
    {
        cout << "SDL_DisplayFormat Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(loaded_image);
        return nullptr;
    }

    // Free anh goc va tra ve anh da optimize
    SDL_FreeSurface(loaded_image);

    return optimized_image;
}

void base_Object::SetImage(SDL_Surface* img)
{
    image = img;
}

SDL_Surface* base_Object::GetImage()
{
    return image;
}