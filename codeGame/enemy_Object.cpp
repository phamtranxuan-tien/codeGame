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

void enemy_Object::Destroy(vector <bullet_Object>& a)
{
	for (int i = 0; i < a.size(); i++)
		if (a[i].GetX() >= this->GetX() - 30 && a[i].GetY() + 5 <= this->GetY() + 132 && a[i].GetY() + 5 >= this->GetY() + 40)
		{
			x = -1;
			y = -1;
			a.erase(a.begin() + i);
			return;
		}
}

void enemy_Object::EnemyShoot()
{
	for (int i = 0; i < 100; ++i)
	{
		ApplySurface(bullets[i].GetImage(), screen, bullets[i].GetX(), bullets[i].GetY());
		bullets[i].MoveEnemy();
		if (bullets[i].GetX() <= 25)
			bullets.erase(bullets.begin() + i);

	}
}