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

class main_Object:public base_Object //class main_Object duoc ke thua tu class base_Object
{
private:
	vector <Heart_Object> Mau; //Thuoc tinh dai dien cho mau cua main object
	vector <bullet_Object> bullets; //Thuoc tinh dai dien cho dan
public:
	main_Object(); //Ham khoi tao mac dinh;
	~main_Object(); //Phuong thuc pha huy
	void Move(); //Ham di chuyen
	void Action(SDL_Event); //Kiem tra huong di chuyen va cap nhat khoang cach doi tuong di bao xa
	vector<bullet_Object> GetBullet(); //Lay vector dan
	void SetBullet(vector <bullet_Object>); //Cap nhat vector dan
	void Shoot(); //Ham ban dan 
	void Crush(vector <enemy_Object>&); //Kiem tra va cham voi dich va cap nhat lai ke dich
	void Crush(vector <bullet_Object>&); //Kiem tra va cham voi dan
	void Damage(); //Gay thiet hai khi trung dan hoac va cham may may dich
	void DamageEnemy(vector <enemy_Object>); //Gay thiet hai khi dich di qua pham vi can bao ve

	vector <Heart_Object> GetMau(); //Lay vector Mau
	void SetMau(vector <Heart_Object>); //Cap nhat vector Mau
	void CreateMau(); //Tao vector Mau
	void DestroyMau(); //Thay doi thuoc tinh HP cua doi tuong Mau trong vector Mau khi doi tuong chinh bi thiet hai
	void DrawMau(); //Ve vector Mau len man hinh
};

