#pragma once
#include "base_Object.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
using namespace std;
class bullet_Object:public base_Object //??i t??ng ??n k? th?a t? ??i t??ng c? b?n
{
private:
	bool Shoot = false; //Thu?c tính ki?m tra ??n có ?ang ???c b?n hay không
public:
	void Create_bullet(int,int,string); //Kh?i t?o ??i t??ng ??n
	~bullet_Object(); //H?y ??i t??ng ??n
	void Move(int); //Di chuy?n ??i t??ng ??n
	void SetShoot(); //C?p nh?t giá tr? c?a thu?c tính Shoot
	bool GetShoot(); //L?y giá tr? c?a thu?c tính Shoot
};

