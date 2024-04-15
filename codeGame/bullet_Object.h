#pragma once
#include "base_Object.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
using namespace std;
class bullet_Object:public base_Object
{
private:
	bool Shoot = false;
public:
	void Create_bullet(int,int,string);
	~bullet_Object();
	void Move();
	void MoveEnemy();
	void SetShoot();
	bool GetShoot();
};

