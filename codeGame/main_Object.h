#pragma once
#include "base_Object.h"
#include "bullet_Object.h"
#include "enemy_Object.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <vector>
using namespace std;

class main_Object:public base_Object
{
private:
	int HP = 3;
	vector <bullet_Object> bullets;
public:
	main_Object();
	~main_Object();
	void Move();
	void Action(SDL_Event);
	vector<bullet_Object> GetBullet();
	void SetBullet(vector <bullet_Object>);
	void Shoot();
	void Crush(vector <enemy_Object>&);
	void Crush(vector <bullet_Object>&);
	void Damge();
};

