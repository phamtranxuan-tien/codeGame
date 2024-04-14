#include "main_Object.h"
#include "base_Object.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
using namespace std;

// Test lần 2s
main_Object::main_Object()
{
	x = 100;
	y = 100;
	image = NULL;
}

main_Object::~main_Object()
{
	return;
}

void main_Object::SetImage(SDL_Surface* img)
{
	image = img;
}

SDL_Surface* main_Object::GetImage()
{
	return image;
}

void main_Object::SetX(int xx)
{
	x = xx;
}

int main_Object::GetX()
{
	return x;
}

void main_Object::SetY(int yy)
{
	y = yy;
}

int main_Object::GetY()
{
	return y;
}


int y_val = 0, x_val = 0;
void main_Object::Move()
{
    if (x >= 0 && x <= 1280)
        x += x_val;
    else
    {
        if (x < 0)
            x = 0;
        else
            x = 1180;
    }
    if (y >= 0 && y <= 720)
        y += y_val;
    else
    {
        if
            (y < 0)
            y = 0;
        else
            y = 620;
    }
}

void main_Object::Action(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            x_val -= 1;
            break;
        case SDLK_s:
            y_val += 1;
            break;
        case SDLK_w:
            y_val -= 1;
            break;
        case SDLK_d:
            x_val += 1;
            break;
        }
    }
    else 
        if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
                x_val = 0;
                break;
            case SDLK_s:
                y_val = 0;
                break;
            case SDLK_w:
                y_val = 0;
                break;
            case SDLK_d:
                x_val = 0;
                break;
            }
        }
}