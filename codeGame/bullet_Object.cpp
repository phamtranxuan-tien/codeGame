#include "Function.h"

void bullet_Object::Create_bullet(int xx, int yy, string filename)
{
	x = xx;
	y = yy;
	image = LoadImage(filename);
	image = SplitBackground(resizeImage(image, 30, 10));
}

bullet_Object::~bullet_Object()
{
	return;
}

void bullet_Object::Move()
{
	if (x < SCREEN_WIDTH)
		x = x + 15;
	else x = -1;
}

void bullet_Object::SetShoot()
{
	Shoot = true;
}

bool bullet_Object::GetShoot()
{
	return Shoot;
}
