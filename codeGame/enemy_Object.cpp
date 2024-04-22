#include "Function.h"

enemy_Object::enemy_Object()
{
	image = SplitBackground(LoadImage("Enemy_05.png"));
}

void enemy_Object::Move()
{
	if (x > 0)
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
	/*bullets[0].Move(1);
	ApplySurface(bullets[0].GetImage(), screen, bullets[0].GetX(), bullets[0].GetY());*/
	bullet_Object bullet;
	if (bullets.empty() || x - bullets[bullets.size() - 1].GetX()  == 200)
	{
		bullet.Create_bullet(x, y, "fire_01.png");
		bullets.push_back(bullet);
	}
	for (int i = 0; i < bullets.size(); ++i)
	{
		ApplySurface(bullets[i].GetImage(), screen, bullets[i].GetX(), bullets[i].GetY());
		bullets[i].Move(1);
	}
	for (int i = 0; i < bullets.size(); ++i)
		if (bullets[i].GetX() < 0 && bullets.size() > 1)
			bullets.erase(bullets.begin() + i);
}
