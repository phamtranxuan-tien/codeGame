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
        bullets[i].Move(0);
        if (bullets[i].GetX() >= SCREEN_WIDTH)
            bullets.erase(bullets.begin() + i);
    }
}

void main_Object::Damge()
{
    if (HP == 0)
    {
        x = -300;
        y = -300;
    }
    else
        HP--;
}


void main_Object::Crush(vector <bullet_Object>& b)
{
    for (int i = 0; i < b.size(); i++)
    {
        // Dau may bay cai tien
        if (this->GetX() + 35 < b[i].GetX() + 105 + 60 &&
            this->GetX() + 35 + (170 - 90) > b[i].GetX() + 105 &&
            this->GetY() + 62 < b[i].GetY() + 105 + 10 &&
            this->GetY() + 62 + (80 - 62) > b[i].GetY() + 105)
        {
            this->Damge();
            b[i].SetX(-100);
            b[i].SetY(-100);
        }

        // Duoi may bay cai tien
        else if (this->GetX() + 25 < b[i].GetX() + 105 + 60 &&
            this->GetX() + 25 + 30 > b[i].GetX() + 105 &&
            this->GetY() + 40 < b[i].GetY() + 105 + 10 &&
            this->GetY() + 40 + (62 - 40) > b[i].GetY() + 105)
        {
            this->Damge();
            b.erase(b.begin() + i);
        }

        // Dit may bay cai tien
        else if (this->GetX() + 44 < b[i].GetX() + 158 + 170 - 158 &&
            this->GetX() + 44 + 90 - 44 > b[i].GetX() + 105 &&
            this->GetY() + 80 < b[i].GetY() + 40 + (115 - 40) &&
            this->GetY() + 80 + (110 - 80) > b[i].GetY() + 40)
        {
            this->Damge();
            b[i].SetX(-100);
            b[i].SetY(-100);
        }

        // Mui may bay
        else if (this->GetX() + 245 >= b[i].GetX() + 75 && this->GetX() + 245 <= b[i].GetX() + 75 + (245 - 175) && this->GetY() + 111 >= b[i].GetY() + 56 && this->GetY() + 111 <= b[i].GetY() + 125)
        {
            this->Damge();
            b[i].SetX(-100);
            b[i].SetY(-100);
        }

        // Sung may bay
        else if (this->GetX() + 133 >= b[i].GetX() + 100 && this->GetX() + 133 <= b[i].GetX() + 100 + (133 - 80) && this->GetY() + 127 >= b[i].GetY() + 40 && this->GetY() + 127 <= b[i].GetY() + 40 + (127 - 111))
        {
            this->Damge();
            b[i].SetX(-100);
            b[i].SetY(-100);
        }
    }
}

void main_Object::Crush(vector <enemy_Object>& e)
{
    for (int i = 0; i < e.size(); ++i)
    {
        //if (this->GetX() + 170 >= e[i].GetX() + 120 && this->GetX() + 170 <= e[i].GetX() + 120 + (170 - 90) && this->GetY() + 80 >= e[i].GetY() + 115 && this->GetY() + 80 <= e[i].GetY() + 115 + (80 - 62))
        //{
        //    this->SetX(-300);
        //    this->SetY(-300);
        //}

        // Dau may bay cai tien
        if (this->GetX() + 35 < e[i].GetX() + 105 + 60 &&
            this->GetX() + 35 + (170 - 90) > e[i].GetX() + 105 &&
            this->GetY() + 62 < e[i].GetY() + 105 + 10 &&
            this->GetY() + 62 + (80 - 62) > e[i].GetY() + 105)
        {
            this->Damge();
            e[i].SetX(-200);
            e[i].SetY(-200);
        }

        // Duoi may bay cai tien
        else if (this->GetX() + 25 < e[i].GetX() + 105 + 60 &&
            this->GetX() + 25 + 30 > e[i].GetX() + 105 &&
            this->GetY() + 40 < e[i].GetY() + 105 + 10 &&
            this->GetY() + 40 + (62 - 40) > e[i].GetY() + 105)
        {
            this->Damge();
            e[i].SetX(-200);
            e[i].SetY(-200);
        }

        // Dit may bay cai tien
        else if (this->GetX() + 44 < e[i].GetX() + 158 + 170 - 158 &&
            this->GetX() + 44 + 90 - 44 > e[i].GetX() + 105 &&
            this->GetY() + 80 < e[i].GetY() + 40 + (115 - 40) &&
            this->GetY() + 80 + (110 - 80) > e[i].GetY() + 40)
        {
            this->Damge();
            e[i].SetX(-200);
            e[i].SetY(-200);
        }

        // Mui may bay
        else if (this->GetX() + 245 >= e[i].GetX() + 75 && this->GetX() + 245 <= e[i].GetX() + 75 + (245 - 175) && this->GetY() + 111 >= e[i].GetY() + 56 && this->GetY() + 111 <= e[i].GetY() + 125)
        {
            this->Damge();
            e[i].SetX(-200);
            e[i].SetY(-200);
        }

        // Sung may bay
        else if (this->GetX() + 133 >= e[i].GetX() + 100 && this->GetX() + 133 <= e[i].GetX() + 100 + (133 - 80) && this->GetY() + 127 >= e[i].GetY() + 40 && this->GetY() + 127 <= e[i].GetY() + 40 + (127 - 111))
        {
            this->Damge();
            e[i].SetX(-200); 
            e[i].SetY(-200);
        }
        vector <bullet_Object> temp = e[i].GetBullet();
        this->Crush(temp);
        e[i].SetBullet(temp);
    }
}
