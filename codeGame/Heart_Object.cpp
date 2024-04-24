#include "Function.h"

Heart_Object::Heart_Object()
{
	HP = 1;
}

void Heart_Object::CreateHeart(int xx, int yy, string filename)
{
	x = xx;
	y = yy;
	image = LoadImage(filename);
	image = SplitBackground(resizeImage(image, 50, 50));
}

int Heart_Object::GetHP()
{
	return HP;
}
void Heart_Object::SetHP(int hp)
{
	HP = hp;
}



