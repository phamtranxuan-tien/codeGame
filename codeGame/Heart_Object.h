#pragma once
#include "Function.h"

class Heart_Object :public base_Object
{
private:
	int HP;
public:
	Heart_Object();
	void CreateHeart(int, int, string);
	int GetHP();
	void SetHP(int);
};

