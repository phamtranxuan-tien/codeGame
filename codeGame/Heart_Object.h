#pragma once
#include "Function.h"

class Heart_Object :public base_Object //Class mau ke thua tu class base_Object
{
private:
	int HP; //Thuoc tinh HP dai dien cho doi tuong plane da het mau hay chua
public:
	Heart_Object(); //Ham khoi tao mac dinh
	void CreateHeart(int, int, string); //Ham khoi tao cac thuoc tinh cua mot doi tuong
	int GetHP(); //Lay thuoc tinh HP
	void SetHP(int); //Cap nhat thuoc tinh HP
};

