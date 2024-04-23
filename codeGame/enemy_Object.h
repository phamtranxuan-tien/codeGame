#pragma once
#include "Function.h"

class enemy_Object :public base_Object
{
private:
	vector <bullet_Object> bullets;
public:
	enemy_Object();
	void Move();
	void Destroy(vector <bullet_Object>&);
	void RandomPos();
	vector<bullet_Object> GetBullet();
	void SetBullet(vector <bullet_Object>);
	void Shoot();
	void Shooting();
};

