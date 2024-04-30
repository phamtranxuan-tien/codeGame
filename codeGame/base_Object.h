#pragma once
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
using namespace std; 

class base_Object //Lop co ban
{
protected:
	int x, y; //Thuoc tinh ve toa do 
	SDL_Surface* image; //Thuoc tinh hinh anh
public:
	base_Object(); //Ham khoi tao mac dinh
	SDL_Surface* LoadImage(string); //Ham load anh 
	void SetImage(SDL_Surface*); //Cap nhat hinh 
	SDL_Surface* GetImage(); //Ham tra ve hinh anh 
	void SetX(int); //Cap nhat hoanh do X
	int GetX(); //Lay gia tri hoanh do X
	void SetY(int); //Cap nhat tung do Y
	int GetY(); //Lay gia tri tung do Y
	SDL_Surface* SplitBackground(SDL_Surface*); //Tat nen hinh anh
};

