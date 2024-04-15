#include "Function.h"

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

    for (int i = 0; i < 5; i++)
    {
        enemy_Object enemy_temp;
        enemy_temp.RandomPos();
        e.push_back(enemy_temp);
    }

    if (plane.GetImage() == NULL)
        return 0;

    plane.SetImage(plane.SplitBackground(plane.GetImage()));

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
    
    int currentFrame = 0;
    Uint32 lastFrameTime = 0;
    Uint32 currentTime;

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
                bullet.Create_bullet(plane.GetX() + 170, plane.GetY() + 120, "fire_01.png");
                bullet.SetShoot();
                a = plane.GetBullet();
                a.push_back(bullet);
                plane.SetBullet(a);
            }
            plane.Action(event);
        }
        Uint32 currentTime = SDL_GetTicks();

        // Kiểm tra thời gian giữa các frame
        if (currentTime - lastFrameTime >= FRAME_DELAY) {
            // Xóa màn hình
            SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));

            // Vẽ hình ảnh của plane và enemy lên màn hình
            ApplySurface(frames[currentFrame], screen, 0, 0);
            ApplySurface(plane.GetImage(), screen, plane.GetX(), plane.GetY());

            vector <bullet_Object> b = plane.GetBullet();

            for (int i = 0; i < 5; i++)
                if (e[i].GetX() != -1 && e[i].GetY() != -1)
                    ApplySurface(e[i].GetImage(), screen, e[i].GetX(), e[i].GetY());
            
            for (int i = 0; i < 5; i++)
                if (e[i].GetX() != -1 && e[i].GetY() != -1)
                    e[i].Destroy(b);

            plane.SetBullet(b);
            plane.Move();
            plane.Shoot();

            for (int i = 0; i < 5; i++)
                if (e[i].GetX() != -1 && e[i].GetY() != -1)
                    e[i].Move();
            // Cập nhật màn hình
            SDL_Flip(screen);

            // Cập nhật frame
            currentFrame = (currentFrame + 1) % NUM_FRAMES;

            // Cập nhật thời gian cuối cùng
            lastFrameTime = currentTime;
        }
        
        a.clear();
       
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