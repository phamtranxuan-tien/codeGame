#include "Function.h"

enemy_Object::enemy_Object()
{
	image = SplitBackground(LoadImage("Enemy_05.png"));
}

void enemy_Object::Move()
{
	if (x > 0)
		x = x - 10;
}


void enemy_Object::Destroy(vector <bullet_Object>& a)
{
	for (int i = 0; i < a.size(); i++)
		if (a[i].GetX() >= this->GetX() + 30 && a[i].GetY() + 5 <= this->GetY() + 132 && a[i].GetY() + 5 >= this->GetY() + 40)
		{
			x = -1;
			y = -1;
			a.erase(a.begin() + i);
			return;
		}
}
