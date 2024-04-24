﻿#include "Function.h"
#include <chrono>
#include <thread>
#undef main 

int main(int argc, char* argv[])
{
    bool is_quit = false;

    Init();
    main_Object plane;
    base_Object g;
    bullet_Object bullet;
    enemy_Object enemy;
    vector <bullet_Object> a;
    vector <enemy_Object> e;
    enemy_Object enemy_temp;
    SDL_Surface* menu = NULL;
    Mix_Chunk* sound1, * sound2;

    //Khoi tao am thanh
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL audio: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        return 1;
    }

    g.SetImage(g.LoadImage("Menu.png"));
    menu = g.GetImage();
    menu = resizeImage(menu, SCREEN_WIDTH, SCREEN_HEIGHT);
    // Load các frame ảnh vào một mảng
    SDL_Surface* frames[NUM_FRAMES] = { NULL };
    SDL_Surface* temp = NULL;
    for (int i = 0; i < NUM_FRAMES; ++i) {
        std::string filename = "frame_" + std::to_string(i) + ".png";
        g.SetImage(g.LoadImage(filename));
        frames[i] = g.GetImage();
        if (frames[i] == nullptr) {
            std::cerr << "Failed to load frame " << filename << "!" << std::endl;
            return 1;
        }
        frames[i] = resizeImage(frames[i], SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    srand(time(NULL));
    for (int i = 0; i < Sum_of_Enemy; i++)
    {
        enemy_temp.SetX((rand() % SCREEN_WIDTH) / 2 + SCREEN_WIDTH);
        enemy_temp.SetY(rand() % (SCREEN_HEIGHT - 175));
        e.push_back(enemy_temp);
    }
 
    if (plane.GetImage() == NULL)
        return 0;

    plane.SetImage(plane.SplitBackground(plane.GetImage()));
    
    int currentFrame = 0;
    Uint32 lastFrameTime = 0;
    Uint32 currentTime;

    plane.CreateMau();

    while (!is_quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                is_quit = true; // Thoat neu nhan duoc su kien thoat
                break;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                is_quit = true; // Thoat neu nhan phim ESC
                break;
            }
            else if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) || Play == true)
            {
                Play = true;
                

                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
                {
                    if (plane.GetBullet().size() < Sum_of_Bullet)
                    {
                        bullet.Create_bullet(plane.GetX() + 175, plane.GetY() + 111, "fire_enemy_02.png");
                        bullet.SetShoot();
                        a = plane.GetBullet();
                        a.push_back(bullet);
                        plane.SetBullet(a);
                        sound1 = Mix_LoadWAV("shot.wav");
                        if (sound1 != NULL)
                            Mix_PlayChannel(-1, sound1, 0);
                    }
                }
                plane.Action(event);

            }
        }
        if (Play == false)
        {
            ApplySurface(menu, screen, 0, 0);
            sound2 = Mix_LoadWAV("menu.wav");
            if (sound2 != NULL)
                Mix_PlayChannel(-1, sound2, 0);
            /*sound1 = Mix_LoadWAV("shot.wav");
            if (sound1 != NULL)
                Mix_PlayChannel(-1, sound1, 0);*/
        }
        else
        {
         //   Mix_HaltChannel(-1);

            sound2 = Mix_LoadWAV("sound_background.wav");
            if (sound2 != NULL)
                Mix_PlayChannel(-1, sound2, 0);
            Uint32 currentTime = SDL_GetTicks();

            // Kiểm tra thời gian giữa các frame
            if (currentTime - lastFrameTime >= FRAME_DELAY) {
                // Xóa màn hình
                SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));

                // Vẽ hình ảnh của plane và enemy lên màn hình
                ApplySurface(frames[currentFrame], screen, 0, 0);
                ApplySurface(plane.GetImage(), screen, plane.GetX(), plane.GetY());
                for (int i = 0; i < e.size(); i++)
                    ApplySurface(e[i].GetImage(), screen, e[i].GetX(), e[i].GetY());
                vector <bullet_Object> b = plane.GetBullet();

                for (int i = 0; i < e.size(); i++)
                    if (e[i].GetX() != -1 && e[i].GetY() != -1)
                        ApplySurface(e[i].GetImage(), screen, e[i].GetX(), e[i].GetY());



            for (int i = 0; i < e.size(); i++)
                if (e[i].GetX() != -1 && e[i].GetY() != -1)
                {
                    e[i].Destroy(b);
                    if (e[i].GetX() == -1 && e[i].GetY() == -1)
                        e.erase(e.begin() + i);
                }
              
            plane.DrawMau();
            plane.SetBullet(b);
            plane.Move();
            plane.Shoot();
            plane.Crush(e);

                for (int i = 0; i < e.size(); i++)
                    if (e[i].GetX() != -1 && e[i].GetY() != -1)
                    {
                        if (e[i].GetX() <= SCREEN_WIDTH)
                            e[i].Shoot();
                        e[i].Move();
                    }

                // Cập nhật màn hình
                SDL_Flip(screen);

                // Cập nhật frame
                currentFrame = (currentFrame + 1) % NUM_FRAMES;

                // Cập nhật thời gian cuối cùng
                lastFrameTime = currentTime;
            }

            a.clear();
        }
        

        // Cập nhật màn hình
        if (SDL_Flip(screen) == -1)
            return 0;
    }

    // Giải phóng bộ nhớ
    for (int i = 0; i < NUM_FRAMES; ++i)
    {
        SDL_FreeSurface(frames[i]);
    }
    CleanUp(g);
    SDL_Quit();
    return 1;
}