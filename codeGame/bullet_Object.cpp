#include "Function.h"

void bullet_Object::Create_bullet(int xx, int yy, string filename)
{
	x = xx;
	y = yy;
	image = LoadImage(filename);
	image = resizeImage(image, 30, 10);
	image = SplitBackground(image);
}

bullet_Object::~bullet_Object()
{
	return;
}

void bullet_Object::Move()
{
	if (x < SCREEN_WIDTH)
		x++;
}

void bullet_Object::SetShoot()
{
	Shoot = true;
}

bool bullet_Object::GetShoot()
{
	return Shoot;
}
