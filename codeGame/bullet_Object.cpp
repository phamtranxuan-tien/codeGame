#include "Function.h"

void bullet_Object::Create_bullet(int xx, int yy, string filename)
{
	x = xx;
	y = yy;
	image = LoadImage(filename);
	if (image == NULL)
	{
		cout << "Load image in method Create_bullet failed!";
		exit(1);
	}
	image = SplitBackground(resizeImage(image, 30, 10));
}

bullet_Object::~bullet_Object()
{
	return;
}

void bullet_Object::Move(int dir)
{
	//dir=1: dan ban qua trai
	//dir=0: dan ban qua phai
	if (dir == 0)
	{
		if (x < SCREEN_WIDTH)
			x = x + 15;
		else x = -1;
	}
	else
	{
		if (x >= 0)
			x = x - 15;
	}
}

void bullet_Object::SetShoot()
{
	Shoot = true;
}

bool bullet_Object::GetShoot()
{
	return Shoot;
}
 
void bullet_Object::CleanUpBullet()
{
	SDL_FreeSurface(image);
}