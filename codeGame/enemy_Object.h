#pragma once
#include "Function.h"

class enemy_Object :public base_Object //Class dich duoc ke thua tu class base_Object
{
private:
	vector <bullet_Object> bullets; //Thuoc tinh dai dien cho dan cua ke dich
public:
 	enemy_Object(); //Ham khoi tao mac dinh
	void Move(); //Di chuyen ke dich tren man hinh
	void Destroy(vector <bullet_Object>&); //Loai bo doi tuong khi bị trung dan
	vector<bullet_Object> GetBullet(); //Lay vector dan cua class dich 
	void SetBullet(vector <bullet_Object>); //Cap nhat vector dan
	void Shoot(); //Phuong thuc ban cua dich
};

