#pragma once
#include "Function.h"

class enemy_Object :public base_Object
{
private:
public:
	enemy_Object();
	void Move();
	void Destroy(vector <bullet_Object>&);
	void RandomPos();
};

