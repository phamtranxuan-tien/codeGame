#include "Function.h"

main_Object::main_Object()
{
	x = 100;
	y = 100;
    image = LoadImage("Mine_03.png");
    if (image == NULL)
    {
        cout << "Load image in method main_Object failed!";
        exit(1);
    }
}

main_Object::~main_Object()
{
	return;
}

void main_Object::Move()
{
    if (x + x_val >= 0 && x + x_val <= SCREEN_WIDTH - 270)
        x += x_val;
    if (y + y_val >= -30 && y + y_val <= SCREEN_HEIGHT - 175)
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
    for (int i = bullets.size() - 1; i >= 0; i--)
    {
        ApplySurface(bullets[i].GetImage(), screen, bullets[i].GetX(), bullets[i].GetY());
        bullets[i].Move(0);
        if (bullets[i].GetX() >= SCREEN_WIDTH)
        {
            bullets[i].CleanUpBullet();
            bullets.erase(bullets.begin() + i);
        }
            
    }
}

void main_Object::Damage()
{
    this->DestroyMau();
    if (Mau[0].GetHP() == 0)
    {
        y_val = 0;
        x_val = 0;
        return;
    }
}

void main_Object::DamageEnemy(vector <enemy_Object> e)
{
    for (int i = 0; i < e.size(); i++)
    {
        if (e[i].GetX() <= -54 && e[i].GetX() > -300)
        {
            for (int j = 0; j < 3; j++)
                this->Damage();
            x = -300;
            y = -300;
            return;
        }
    }
}

void main_Object::Crush(vector <bullet_Object>& b)
{
    for (int i = b.size() - 1; i >= 0; i--)
    {
        // Dau may bay cai tien
        if (this->GetX() + 35 < b[i].GetX() + 0.5 &&
            this->GetX() + 35 + (145 - 35) > b[i].GetX()&&
            this->GetY() + 62 < b[i].GetY() + 4 &&
            this->GetY() + 62 + (80 - 62) > b[i].GetY())
        {
            this->Damage();
            b[i].SetX(-100);
            b[i].SetY(-100);
        }

        // Than may bay cai tien
        else if (this->GetX() + 90 < b[i].GetX() + 0.5 &&
            this->GetX() + 90 + (175 - 90) > b[i].GetX() &&
            this->GetY() + 80 < b[i].GetY() + 4 &&
            this->GetY() + 80 + (111 - 80) > b[i].GetY())
        {
            this->Damage();
            b[i].SetX(-100);
            b[i].SetY(-100);
        }

        // Duoi may bay cai tien
        else if (this->GetX() + 25 < b[i].GetX() + 0.5 &&
            this->GetX() + 25 + 30 > b[i].GetX()&&
            this->GetY() + 40 < b[i].GetY() + 4 &&
            this->GetY() + 40 + (62 - 40) > b[i].GetY())
        {
            this->Damage();
            b[i].SetX(-100);
            b[i].SetY(-100);
        }

        // Mui may bay cai tien
        else if (this->GetX() + 170 < b[i].GetX() + 0.5 &&
            this->GetX() + 170 + (235 - 170) > b[i].GetX() &&
            this->GetY() + 90 < b[i].GetY() + 4 &&
            this->GetY() + 90 + (105 - 90) > b[i].GetY())
        {
            this->Damage();
            b[i].SetX(-100);
            b[i].SetY(-100);
        }

        // Sung may bay cai tien
        else if (this->GetX() + 75 < b[i].GetX() + 0.5 &&
            this->GetX() + 75 + (133 - 75) > b[i].GetX() &&
            this->GetY() + 111 < b[i].GetY() + 4 &&
            this->GetY() + 111 + (127 - 111) > b[i].GetY())
        {
            this->Damage();
            b[i].SetX(-100);
            b[i].SetY(-100);
        } 
    }
    for (int i = b.size() - 1; i >= 0; i--)
        if (b[i].GetX() == -100 && b[i].GetY() == -100)
        {
            b[i].CleanUpBullet();
            b.erase(b.begin() + i);
        }
            
    
}

void main_Object::Crush(vector <enemy_Object>& e)
{
    for (int i = e.size() - 1; i >= 0; i--)
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
            this->Damage();
            e[i].SetX(-300);
            e[i].SetY(-300);
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
            this->Damage();
            e[i].SetX(-300);
            e[i].SetY(-300);
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
            this->Damage();
            e[i].SetX(-300);
            e[i].SetY(-300);
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
            this->Damage();
            e[i].SetX(-300);
            e[i].SetY(-300);
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
            this->Damage();
            e[i].SetX(-300);
            e[i].SetY(-300);
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
            this->Damage();
            e[i].SetX(-300); 
            e[i].SetY(-300);
        }
        vector <bullet_Object> temp = e[i].GetBullet();
        this->Crush(temp);
        e[i].SetBullet(temp);
        this->DamageEnemy(e);
        
    }
}

vector <Heart_Object> main_Object::GetMau()
{
    return Mau;
}

void main_Object::SetMau(vector <Heart_Object> mau)
{
    Mau = mau;
}

void main_Object::CreateMau()
{
    int XMau = 1000;
    int YMau = 10;
    if (!Mau.empty())
    {
        for (int i = 0; i < Sum_of_Heart; i++)
            SDL_FreeSurface(Mau[i].GetImage());
        Mau.clear();
    }
    
    for (int i = 0; i < Sum_of_Heart; i++)
    {   
        Heart_Object temp;
        temp.CreateHeart(XMau, YMau, "Alive.png");
        Mau.push_back(temp);
        XMau += 60;
    } 
}

void main_Object::DestroyMau()
{
    
    for (int i = Sum_of_Heart - 1; i >= 0; i--)
        if (Mau[i].GetHP() == 1)
        {
            SDL_Surface* img = LoadImage("Dead.png");
            if (img == NULL)
            {
                cout << "Load image in method DestroyMau failed!";
                exit(1);
            }
            img = SplitBackground(resizeImage(img, 50, 50));
            Mau[i].SetImage(img);
            Mau[i].SetHP(0);  
            break;
        }
}   

void main_Object::DrawMau()
{
    for (int i = 0; i < Sum_of_Heart; i++)
        ApplySurface(Mau[i].GetImage(), screen, Mau[i].GetX(), Mau[i].GetY());
}

void main_Object::CleanUpBullets()
{
    for (int i = 0;i < bullets.size();i++)
        bullets[i].CleanUpBullet();
    bullets.clear();
}