#include "Function.h"

main_Object::main_Object()
{
	x = 100;
	y = 100;
    image = LoadImage("Mine_03.png");
}

main_Object::~main_Object()
{
	return;
}

int y_val = 0, x_val = 0;
void main_Object::Move()
{
    if (x + x_val >= 0 && x + x_val <= SCREEN_WIDTH - 270)
        x += x_val;
    if (y + y_val >= 0 && y + y_val <= SCREEN_HEIGHT - 175)
        y += y_val;
}

void main_Object::Action(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            x_val -= 15;
            break;
        case SDLK_s:
            y_val += 15;
            break;
        case SDLK_w:
            y_val -= 15;
            break;
        case SDLK_d:
            x_val += 15;
            break;
        }
    }
    else 
        if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
                x_val = 0;
                break;
            case SDLK_s:
                y_val = 0;
                break;
            case SDLK_w:
                y_val = 0;
                break;
            case SDLK_d:
                x_val = 0;
                break;
            }
        }
}

vector<bullet_Object> main_Object::GetBullet()
{
    return bullets;
}

void main_Object::SetBullet(vector <bullet_Object> v)
{
    bullets = v;
}

void main_Object::Shoot()
{
    for (int i = 0; i < bullets.size(); ++i)
    {
        ApplySurface(bullets[i].GetImage(), screen, bullets[i].GetX(), bullets[i].GetY());
        bullets[i].Move();
        if (bullets[i].GetX() >= SCREEN_WIDTH)
            bullets.erase(bullets.begin() + i);
    }
}

void main_Object::Crush(vector <enemy_Object> e)
{
    for (int i = 0; i < e.size(); ++i)
        if (this->GetX() + 245 >= e[i].GetX() && this->GetY() + 96 >= e[i].GetY() && this->GetY() + 96 <= e[i].GetY() + 150)
        {
            this->SetX(-300);
            this->SetY(-300);
        }
}
