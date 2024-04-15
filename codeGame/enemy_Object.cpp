#include "Function.h"

enemy_Object::enemy_Object()
{
	srand(time(NULL));
	x = SCREEN_WIDTH;
	y = rand() % SCREEN_HEIGHT;
	image = SplitBackground(LoadImage("Enemy_05.png"));
}

void enemy_Object::Move()
{
	if (x > 0)
		x = x - 10;
}

void enemy_Object::RandomPos()
{
	srand(time(NULL));
	x = SCREEN_WIDTH;
	y = rand() % SCREEN_HEIGHT;
}


void enemy_Object::Destroy(vector <bullet_Object>& a)
{
	for (int i = 0; i < a.size(); i++)
		if (a[i].GetX() >= this->GetX() - 100 && a[i].GetY() <= this->GetY() + 100 && a[i].GetY() >= this->GetY() - 100)
		{
			x = -1;
			y = -1;
			a.erase(a.begin() + i);
			return;
		}
}
