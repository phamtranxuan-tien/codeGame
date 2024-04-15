#include "Function.h"

base_Object::base_Object()
{
    x = 0;
    y = 0;
    image = NULL;
}

void base_Object::SetImage(SDL_Surface* img)
{
    image = img;
}

SDL_Surface* base_Object::GetImage()
{
    return image;
}

void base_Object::SetX(int xx)
{
    x = xx;
}

int base_Object::GetX()
{
    return x;
}

void base_Object::SetY(int yy)
{
    y = yy;
}

int base_Object::GetY()
{
    return y;
}

// Load anh va kiem tra loi
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

//Tach nen cho nhan vat
SDL_Surface* base_Object::SplitBackground(SDL_Surface* image)
{
    if (image != NULL)
    {
        Uint32 color_key = SDL_MapRGB(image->format, 179, 179, 179);
        SDL_SetColorKey(image, SDL_SRCCOLORKEY, color_key);
    }
    return image;
}