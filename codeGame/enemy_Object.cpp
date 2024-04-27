#include "Function.h"

enemy_Object::enemy_Object()
{
	image = SplitBackground(LoadImage("Enemy_05.png"));
}

void enemy_Object::Move()
{
	if (x - 5 >= -60)
		x = x - 5;
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

vector<bullet_Object> enemy_Object::GetBullet()
{
	return bullets;
}

void enemy_Object::SetBullet(vector <bullet_Object> v)
{
	bullets = v;
}

void enemy_Object::Shoot()
{
	bullet_Object bullet;
	if (bullets.empty() || x - bullets[bullets.size() - 1].GetX()  == 500)
	{
		bullet.Create_bullet(x + 90, y + 85, "fire_enemy_02.png");
		bullets.push_back(bullet);
	}
	for (int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i].GetX() > 0)
			ApplySurface(bullets[i].GetImage(), screen, bullets[i].GetX(), bullets[i].GetY());
		bullets[i].Move(1);
	}
	for (int i = 0; i < bullets.size(); ++i)
		if (bullets[i].GetX() <= 0 && bullets.size() > 1)
			bullets.erase(bullets.begin() + i);
}
