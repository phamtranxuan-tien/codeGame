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
		x=x-0.05;
}