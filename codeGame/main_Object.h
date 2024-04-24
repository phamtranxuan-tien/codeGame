#pragma once
#include "base_Object.h"
#include "bullet_Object.h"
#include "enemy_Object.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <vector>
#include "Heart_Object.h"

using namespace std;

class main_Object:public base_Object
{
private:
	vector <Heart_Object> Mau;
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
	vector <Heart_Object> GetMau();
	void SetMau(vector <Heart_Object>);
	void CreateMau();
	void DestroyMau();
	void DrawMau();
};

