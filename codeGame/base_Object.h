#pragma once
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
using namespace std; 

class base_Object
{
protected:
	float x, y;
	SDL_Surface* image;
public:
	base_Object();
	SDL_Surface* LoadImage(string);
	void SetImage(SDL_Surface*);
	SDL_Surface* GetImage();
	void SetX(int);
	int GetX();
	void SetY(int);
	int GetY();
	SDL_Surface* SplitBackground(SDL_Surface*);
};

