#include "Function.h"

main_Object::main_Object()
{
	x = 100;
	y = 100;
    image = LoadImage("Mine_03.png");
    //image = LoadImage("Enemy_05.png");
    //image = LoadImage("fire_enemy_02.png");
    //image = resizeImage(image, 30, 10);
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
        if (this->GetX() + 35 < b[i].GetX() + 0.5 &&
            this->GetX() + 35 + (145 - 35) > b[i].GetX()&&
            this->GetY() + 62 < b[i].GetY() + 4 &&
            this->GetY() + 62 + (80 - 62) > b[i].GetY())
        {
            this->Damge();
            b[i].SetX(-100);
            b[i].SetY(-100);
        }

        // Than may bay cai tien
        else if (this->GetX() + 90 < b[i].GetX() + 0.5 &&
            this->GetX() + 90 + (175 - 90) > b[i].GetX() &&
            this->GetY() + 80 < b[i].GetY() + 4 &&
            this->GetY() + 80 + (111 - 80) > b[i].GetY())
        {
            this->Damge();
            b.erase(b.begin() + i);
        }

        // Duoi may bay cai tien
        else if (this->GetX() + 25 < b[i].GetX() + 0.5 &&
            this->GetX() + 25 + 30 > b[i].GetX()&&
            this->GetY() + 40 < b[i].GetY() + 4 &&
            this->GetY() + 40 + (62 - 40) > b[i].GetY())
        {
            this->Damge();
            b.erase(b.begin() + i);
        }

        // Mui may bay cai tien
        else if (this->GetX() + 170 < b[i].GetX() + 0.5 &&
            this->GetX() + 170 + (235 - 170) > b[i].GetX() &&
            this->GetY() + 90 < b[i].GetY() + 4 &&
            this->GetY() + 90 + (105 - 90) > b[i].GetY())
        {
            this->Damge();
            b.erase(b.begin() + i);
        }

        // Sung may bay cai tien
        else if (this->GetX() + 75 < b[i].GetX() + 0.5 &&
            this->GetX() + 75 + (133 - 75) > b[i].GetX() &&
            this->GetY() + 111 < b[i].GetY() + 4 &&
            this->GetY() + 111 + (127 - 111) > b[i].GetY())
        {
            this->Damge();
            b.erase(b.begin() + i);
        } 
    }
}

void main_Object::Crush(vector <enemy_Object>& e)
{
    for (int i = 0; i < e.size(); ++i)
    {
        // Dau may bay cai tien
        if ((this->GetX() + 35 < e[i].GetX() + 110 + (150 - 110) &&
            this->GetX() + 35 + (145 - 35) > e[i].GetX() + 110 &&
            this->GetY() + 62 < e[i].GetY() + 40 + (113 - 40) &&
            this->GetY() + 62 + (80 - 62) > e[i].GetY() + 40) ||
            (this->GetX() + 35 < e[i].GetX() + 75 + (175 - 75) &&
                this->GetX() + 35 + (145 - 35) > e[i].GetX() + 75 &&
                this->GetY() + 62 < e[i].GetY() + 60 + (95 - 60) &&
                this->GetY() + 62 + (80 - 62) > e[i].GetY() + 60) ||
            (this->GetX() + 35 < e[i].GetX() + 93 + (165 - 93) &&
                this->GetX() + 35 + (145 - 35) > e[i].GetX() + 93 &&
                this->GetY() + 62 < e[i].GetY() + 50 + (105 - 50) &&
                this->GetY() + 62 + (80 - 62) > e[i].GetY() + 50))
        {
            this->Damge();
            e[i].SetX(-200);
            e[i].SetY(-200);
        }

        // Than may bay cai tien
        else if ((this->GetX() + 90 < e[i].GetX() + 110 + (150 - 110) &&
            this->GetX() + 90 + (175 - 90) > e[i].GetX() + 110 &&
            this->GetY() + 80 < e[i].GetY() + 40 + (113 - 40) &&
            this->GetY() + 80 + (111 - 80) > e[i].GetY() + 40) ||
            (this->GetX() + 90 < e[i].GetX() + 75 + (175 - 75) &&
                this->GetX() + 90 + (175 - 90) > e[i].GetX() + 75 &&
                this->GetY() + 80 < e[i].GetY() + 60 + (95 - 60) &&
                this->GetY() + 80 + (111 - 80) > e[i].GetY() + 60) ||
            (this->GetX() + 90 < e[i].GetX() + 93 + (165 - 93) &&
                this->GetX() + 90 + (175 - 90) > e[i].GetX() + 93 &&
                this->GetY() + 80 < e[i].GetY() + 50 + (105 - 50) &&
                this->GetY() + 80 + (111 - 80) > e[i].GetY() + 50))
        {
            this->Damge();
            e[i].SetX(-200);
            e[i].SetY(-200);
        }

        // Duoi may bay cai tien
        else if ((this->GetX() + 25 < e[i].GetX() + 110 + (150 - 110) &&
            this->GetX() + 25 + 30 > e[i].GetX() + 110 &&
            this->GetY() + 40 < e[i].GetY() + 40 + (113 - 40) &&
            this->GetY() + 40 + (62 - 40) > e[i].GetY() + 40) ||
            (this->GetX() + 25 < e[i].GetX() + 75 + (175 - 75) &&
                this->GetX() + 25 + 30 > e[i].GetX() + 75 &&
                this->GetY() + 40 < e[i].GetY() + 60 + (95 - 60) &&
                this->GetY() + 40 + (62 - 40) > e[i].GetY() + 60) ||
            (this->GetX() + 25 < e[i].GetX() + 93 + (165 - 93) &&
                this->GetX() + 25 + 30 > e[i].GetX() + 93 &&
                this->GetY() + 40 < e[i].GetY() + 50 + (105 - 50) &&
                this->GetY() + 40 + (62 - 40) > e[i].GetY() + 50))
        {
            this->Damge();
            e[i].SetX(-200);
            e[i].SetY(-200);
        }

        // Mui may bay cai tien
        else if ((this->GetX() + 170 < e[i].GetX() + 110 + (150 - 110) &&
            this->GetX() + 170 + (235 - 170) > e[i].GetX() + 110 &&
            this->GetY() + 90 < e[i].GetY() + 40 + (113 - 40) &&
            this->GetY() + 90 + (105 - 90) > e[i].GetY() + 40) ||
            (this->GetX() + 170 < e[i].GetX() + 75 + (175 - 75) &&
                this->GetX() + 170 + (235 - 170) > e[i].GetX() + 75 &&
                this->GetY() + 90 < e[i].GetY() + 60 + (95 - 60) &&
                this->GetY() + 90 + (105 - 90) > e[i].GetY() + 60) ||
            (this->GetX() + 170 < e[i].GetX() + 93 + (165 - 93) &&
                this->GetX() + 170 + (235 - 170) > e[i].GetX() + 93 &&
                this->GetY() + 90 < e[i].GetY() + 50 + (105 - 50) &&
                this->GetY() + 90 + (105 - 90) > e[i].GetY() + 50))
        {
            this->Damge();
            e[i].SetX(-200);
            e[i].SetY(-200);
        }

        // Sung may bay cai tien
        else if ((this->GetX() + 75 < e[i].GetX() + 110 + (150 - 110) &&
            this->GetX() + 75 + (133 - 75) > e[i].GetX() + 110 &&
            this->GetY() + 111 < e[i].GetY() + 40 + (113 - 40) &&
            this->GetY() + 111 + (127 - 111) > e[i].GetY() + 40) ||
            (this->GetX() + 75 < e[i].GetX() + 75 + (175 - 75) &&
                this->GetX() + 75 + (133 - 75) > e[i].GetX() + 75 &&
                this->GetY() + 111 < e[i].GetY() + 60 + (95 - 60) &&
                this->GetY() + 111 + (127 - 111) > e[i].GetY() + 60) ||
            (this->GetX() + 75 < e[i].GetX() + 93 + (165 - 93) &&
                this->GetX() + 75 + (133 - 75) > e[i].GetX() + 93 &&
                this->GetY() + 111 < e[i].GetY() + 50 + (105 - 50) &&
                this->GetY() + 111 + (127 - 111) > e[i].GetY() + 50))
        {
            this->Damge();
            e[i].SetX(-200);
            e[i].SetY(-200);
        }

        // Dit may bay cai tien
        else if ((this->GetX() + 44 < e[i].GetX() + 110 + (150 - 110) &&
            this->GetX() + 44 + 90 - 44 > e[i].GetX() + 110 &&
            this->GetY() + 80 < e[i].GetY() + 40 + (113 - 40) &&
            this->GetY() + 80 + (110 - 80) > e[i].GetY() + 40) ||
            (this->GetX() + 44 < e[i].GetX() + 75 + (175 - 75) &&
                this->GetX() + 44 + 90 - 44 > e[i].GetX() + 75 &&
                this->GetY() + 80 < e[i].GetY() + 60 + (95 - 60) &&
                this->GetY() + 80 + (110 - 80) > e[i].GetY() + 60) ||
                (this->GetX() + 44 < e[i].GetX() + 93 + (165 - 93) &&
                this->GetX() + 44 + 90 - 44 > e[i].GetX() + 93 &&
                this->GetY() + 80 < e[i].GetY() + 50 + (105 - 50) &&
                this->GetY() + 80 + (110 - 80) > e[i].GetY() + 50))
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
