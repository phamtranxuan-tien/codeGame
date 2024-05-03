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
//		if (a[i].GetX() >= this->GetX() + 30 && a[i].GetY() + 5 <= this->GetY() + 132 && a[i].GetY() + 5 >= this->GetY() + 40)
		if ((a[i].GetX() < this->GetX() + 110 + (150 - 110) &&
			a[i].GetX() + 0.5 > this->GetX() + 110 &&
			a[i].GetY() < this->GetY() + 40 + (113 - 40) &&
			a[i].GetY() + 4 > this->GetY() + 40) || 
			(a[i].GetX() < this->GetX() + 70 + (175 - 75) &&
				a[i].GetX() + 0.5 > this->GetX() + 70 &&
				a[i].GetY() < this->GetY() + 60 + (95 - 60) &&
				a[i].GetY() + 4 > this->GetY() + 60) ||
			(a[i].GetX() < this->GetX() + 90 + (165 - 93) &&
				a[i].GetX() + 0.5 > this->GetX() + 90 &&
				a[i].GetY() < this->GetY() + 50 + (105 - 50) &&
				a[i].GetY() + 4 > this->GetY() + 50))
		{
			x = -300;
			y = -300;
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
		{
			SDL_FreeSurface(bullets[i].GetImage());
			bullets.erase(bullets.begin() + i);
		}
}

void enemy_Object::Boom(SDL_Surface* frames_boomb[], int x_temp, int y_temp)
{

	int currentFrameEnemy = 0;
	Uint32 lastFrameTimeEnemy = 0;
	Uint32 currentTimeEnemy = SDL_GetTicks();
	if (currentTimeEnemy - lastFrameTimeEnemy >= 100)
	{
		ApplySurface(frames_boomb[currentFrameEnemy], screen, x_temp, y_temp);
		SDL_Flip(screen);
		currentFrameEnemy = (currentFrameEnemy + 1) % 8;
		lastFrameTimeEnemy = currentTimeEnemy;
	}
}