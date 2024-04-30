#pragma once
#include "base_Object.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
using namespace std;
class bullet_Object:public base_Object //Lop dan duoc ke thua tu lop base_Object
{
private:
	bool Shoot = false; //Thuoc tinh dung de kiem tra xem vien dan da duoc ban hay chua
public:
	void Create_bullet(int,int,string); //Ham khoi tao toa do, hinh anh cua cac doi tuong thuoc class
	~bullet_Object(); //Ham huy mac dinh
	void Move(int); //Di chuyen vien dan 
	void SetShoot(); //Cap nhat lai gia tri cua thuoc tinh Shoot
	bool GetShoot(); //Lay gia tri cua thuoc tinh Shoot
};

