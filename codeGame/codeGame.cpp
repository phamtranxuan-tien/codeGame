#include "Function.h"

#undef main 

int main(int argc, char* argv[])
{
    bool is_quit = false;

    Init();
    main_Object plane;
    base_Object g_bkground;
    bullet_Object bullet;
    enemy_Object enemy;
    vector <bullet_Object> a;
    
   // g_bkground.SetImage(g_bkground.LoadImage("background_01.gif"));
    //g_bkground.SetImage(g_bkground.resizeImage(g_bkground.GetImage(), SCREEN_WIDTH, SCREEN_HEIGHT));
    //ApplySurface(g_bkground.GetImage(), screen, 0, 0);
    
    if (plane.GetImage() == NULL)
        return 0;

//    plane.SetImage(plane.resizeImage(plane.GetImage(), 270 , 175));
    plane.SetImage(plane.SplitBackground(plane.GetImage()));

    // Load các frame ảnh vào một mảng
    SDL_Surface* frames[NUM_FRAMES];
    for (int i = 0; i < NUM_FRAMES; ++i) {
        std::string filename = "frame_" + std::to_string(i) + ".png";
        frames[i] = IMG_Load(filename.c_str());
        if (frames[i] == nullptr) {
            std::cerr << "Failed to load frame " << filename << "!" << std::endl;
            return 1;
        }
    }


    int currentFrame = 0;
    Uint32 lastFrameTime = 0;


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
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
            {
                bullet.Create_bullet(plane.GetX() +170, plane.GetY()+120, "fire_01.png");
                bullet.SetShoot();
                a = plane.GetBullet();
                a.push_back(bullet);
                plane.SetBullet(a);

            }
            plane.Action(event);
        }

        // Kiểm tra xem đã đủ thời gian để chuyển sang khung hình mới chưa
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastFrameTime >= FRAME_DELAY) {
            // Chuyển sang khung hình tiếp theo
            currentFrame = (currentFrame + 1) % NUM_FRAMES;
            lastFrameTime = currentTime;
        }

        ApplySurface(frames[currentFrame], screen, 0, 0);






        a.clear();
        ApplySurface(g_bkground.GetImage(), screen, 0, 0);
        ApplySurface(plane.GetImage(), screen, plane.GetX(), plane.GetY());
        ApplySurface(enemy.GetImage(), screen, enemy.GetX(), enemy.GetY());
        plane.Move();
        plane.Shoot();
        enemy.Move();
//        SDL_Delay(50);
        if (SDL_Flip(screen) == -1)
            return 0;

        // Cập nhật màn hình
        SDL_Flip(screen);
    }

    // Giải phóng bộ nhớ
    for (int i = 0; i < NUM_FRAMES; ++i) {
        SDL_FreeSurface(frames[i]);
    }
    CleanUp(g_bkground);
    SDL_Quit();
    return 1;
}

