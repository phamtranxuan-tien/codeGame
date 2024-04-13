#pragma once
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
using namespace std; 

class base_Object
{
protected:
	int x, y;
	SDL_Surface* image;
public:
	base_Object();

	SDL_Surface* LoadImageGIF2(const char*);
//	SDL_Surface* LoadImageGIF2(string);
	SDL_Surface* LoadImageGIF1(string);
	SDL_Surface* LoadImageGIF(string);
	SDL_Surface* LoadImage(string);
	void SetImage(SDL_Surface*);
	SDL_Surface* GetImage();
};

