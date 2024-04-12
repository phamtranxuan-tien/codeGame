#pragma once
#include <iostream>
#include "base_Object.h"
#include <SDL.h>
#include <string>
#include <SDL_image.h>
using namespace std;

class main_Object:public base_Object
{
private:

public:
	main_Object();
	~main_Object();
	void Move();
	void SetImage(SDL_Surface*);
	SDL_Surface* GetImage();
	void SetX(int);
	int GetX();
	void SetY(int);
	int GetY();
	void Action(SDL_Event);
};

