#include "Function.h"
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
    SDL_Surface* menu = NULL, *victory = NULL;
    Mix_Chunk* sound_shot=NULL, * sound_menu = NULL, * sound_boom = NULL, * sound_victory = NULL;

    int tt = 0;

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

    g.SetImage(g.LoadImage("victory.jpg"));
    g.SetImage(resizeImage(g.GetImage(), SCREEN_WIDTH, SCREEN_HEIGHT));
    g.SetImage(g.SplitBackground(g.GetImage()));
    victory = g.GetImage();
    

    //Load cac frame anh vao mang
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

    // Load cac frame_enter anh vao mot mang
    SDL_Surface* frames_enter[NUM_FRAMES_ENTER] = { NULL };
    SDL_Surface* temp_enter = NULL;
    for (int i = 0; i < NUM_FRAMES_ENTER; ++i) {
        std::string filename;
        if (i < 1)
            filename = "Start_01_01.png";
        else
            filename = "Start_01_02.png";
        g.SetImage(g.LoadImage(filename));
        g.SetImage(resizeImage(g.GetImage(), 1010 / 2, 120 / 2));
        g.SetImage(g.SplitBackground(g.GetImage()));
        frames_enter[i] = g.GetImage();
        if (frames_enter[i] == nullptr) {
            std::cerr << "Failed to load frame " << filename << "!" << std::endl;
            return 1;
        }
    }

    // Load cac frame_boomb anh vao mot mang
    SDL_Surface* frames_boomb[9] = { NULL };
    temp_enter = NULL;
    for (int i = 1; i <= 8; ++i) {
        string filename = "boomb_0";
        filename += to_string(i);
        filename += ".png";
        g.SetImage(g.LoadImage(filename));
        g.SetImage(resizeImage(g.GetImage(), 200 , 200));
        g.SetImage(g.SplitBackground(g.GetImage()));
        frames_boomb[i - 1] = g.GetImage();
        if (frames_boomb[i - 1] == nullptr) {
            std::cerr << "Failed to load frame " << filename << "!" << std::endl;
            return 0;
        }
    }

    //Khoi tao ngau nhien vi tri cua ke dich
    srand(time(NULL));
    for (int i = 0; i < Sum_of_Enemy; i++)
    {
        enemy_temp.SetX((rand() % SCREEN_WIDTH) / 2 + SCREEN_WIDTH);
        enemy_temp.SetY(rand() % (SCREEN_HEIGHT - 175));
        e.push_back(enemy_temp);
    }
 
    //Tach nen may bay
    if (plane.GetImage() == NULL)
        return 0;
    plane.SetImage(plane.SplitBackground(plane.GetImage()));
    
    //Khoi tao mau
    plane.CreateMau();

    int currentFrame = 0;
    Uint32 lastFrameTime = 0;
    int currentFrame1 = 0;
    Uint32 lastFrameTime1 = 0;
    int x_temp = plane.GetX(), y_temp = plane.GetY();

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
                Play = 1;
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
                    Mix_HaltChannel(-1); //Tat sound_menu neu nhan phim enter
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
                {
                    if (plane.GetBullet().size() < Sum_of_Bullet)
                    {
                        //Them dan vua duoc ban vao vector dan cua plane
                        bullet.Create_bullet(plane.GetX() + 170, plane.GetY() + 120, "fire_01.png");
                        bullet.SetShoot();
                        a = plane.GetBullet();
                        a.push_back(bullet);
                        plane.SetBullet(a);
                        
                        //Phat am thanh tieng sung
                        sound_shot = Mix_LoadWAV("shot.wav");
                        if (sound_shot != NULL)
                            Mix_PlayChannel(-1, sound_shot, 0);
                    }
                }
                plane.Action(event);

            }
        }
        if (Play == 0)
        {
            //Phat am thanh nen
            sound_menu = Mix_LoadWAV("menu.wav");
            if (sound_menu != NULL)
                Mix_PlayChannel(-1, sound_menu, 0);
            ApplySurface(menu, screen, 0, 0);
            
            Uint32 currentTime = SDL_GetTicks();

            // Kiem tra thoi gian giua cac frame
            if (currentTime - lastFrameTime >= FRAME_DELAY_ENTER) {

                // Ve anh plane va emeny len man hinh
                ApplySurface(frames_enter[currentFrame], screen, SCREEN_WIDTH / 2 - 1010 / 4, 633);
                // Cap nhat man hinh
                SDL_Flip(screen);

                // Cap nhat frame
                currentFrame = (currentFrame + 1) % NUM_FRAMES_ENTER;

                // Cap nhat thoi gian cuoi cung
                lastFrameTime = currentTime;
            }
        }
        else if (Play == 1)
        {
            tt = 1;
            if (currentFrame1 == 7)
            {
                ApplySurface(menu, screen, 0, 0);
                Play = -1;
                currentFrame1 = 0;
            }
            if (plane.GetX() != -300)
                x_temp = plane.GetX(), y_temp = plane.GetY();
            Uint32 currentTime1 = SDL_GetTicks();
            if (currentTime1 - lastFrameTime1 >= 100 && plane.GetMau()[0].GetHP() == 0) {
                sound_boom = Mix_LoadWAV("boom_01.wav");
                if (sound_boom != NULL)
                    Mix_PlayChannel(-1, sound_boom, 0);
                plane.SetX(-300);
                plane.SetY(-300);
                ApplySurface(frames_boomb[currentFrame1], screen, x_temp, y_temp);
                SDL_Flip(screen);
                currentFrame1 = (currentFrame1 + 1) % 8;
                lastFrameTime1 = currentTime1;
            }
                
            
           
            Uint32 currentTime = SDL_GetTicks();
            // Kiem tra thoi gian giua cac frame
            if (currentTime - lastFrameTime >= FRAME_DELAY) {
                // Xoa man hinh
                SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));

                // Ve anh plane va emeny len man hinh
                ApplySurface(frames[currentFrame], screen, 0, 0);
                ApplySurface(plane.GetImage(), screen, plane.GetX(), plane.GetY());

                for (int i = 0; i < e.size(); i++)
                    if (e[i].GetX() != -1 && e[i].GetY() != -1)
                        ApplySurface(e[i].GetImage(), screen, e[i].GetX(), e[i].GetY());
                
                //Pha huy dich neu bi ban trung
                vector <bullet_Object> b = plane.GetBullet();
                for (int i = 0; i < e.size(); i++)
                    if (e[i].GetX() != -1 && e[i].GetY() != -1)
                    {
                        e[i].Destroy(b);
                        if (e[i].GetX() == -1 && e[i].GetY() == -1)
                            e.erase(e.begin() + i);
                    }

                //Hien thi va cap nhat cac thuoc tinh cua doi tuong may bay
                plane.DrawMau();
                plane.SetBullet(b);
                plane.Move();
                plane.Shoot();
                plane.Crush(e);
                for (int i = 0; i < e.size(); ++i)
                    if (e[i].GetX() == -300 && e[i].GetY() == -300)

                for (int i = 0; i < e.size(); ++i)
                    if (e[i].GetX() == -300 && e[i].GetY() == -300)
                        e.erase(e.begin() + i);
                if (e.size() == 0)
                {
                    y_val = 0;
                    x_val = 0;
                 }
                //Cap nhat toa do cua dich va dan cua dich
                for (int i = 0; i < e.size(); i++)
                    if (e[i].GetX() != -1 && e[i].GetY() != -1)
                    {
                        if (e[i].GetX() <= SCREEN_WIDTH)
                            e[i].Shoot();
                        e[i].Move();
                    }
                
                if (e.size() == 0 && plane.GetMau()[0].GetHP() == 1)
                {
        
                    ApplySurface(victory, screen, 0, 0);
                    sound_victory = Mix_LoadWAV("victory.wav");
                    if (sound_victory != NULL)
                        Mix_PlayChannel(-1, sound_victory, 0);
                    SDL_Flip(screen);
                    Play = -1;
                    SDL_Delay(2000);         
                }
                //Cap nhat man hinh
                SDL_Flip(screen);
                //cap nhat frame
                currentFrame = (currentFrame + 1) % NUM_FRAMES;

                // Cap nhat thoi gian cuoi cung
                lastFrameTime = currentTime;
            }
            a.clear();
        }
        else
        {
            if (tt == 1)
            {
                //Load am thanh
                Mix_FreeChunk(sound_menu);
                sound_menu = Mix_LoadWAV("menu.wav");
                if (sound_menu != NULL)
                    Mix_PlayChannel(-1, sound_menu, 0);

                //Cap nhat lai toa do may bay
                plane.SetX(100);
                plane.SetY(100);

                // Load ảnh "Replay" hoac victory
                SDL_Surface* replayButton = g.LoadImage("Replay.png");
                if (!replayButton) {
                    std::cerr << "Failed to load replay button image!" << std::endl;
                }
                replayButton = resizeImage(replayButton, 1010 / 2, 120 / 2);
                replayButton = g.SplitBackground(replayButton);

                // Ve menu len man hinh
                
                if (e.size() != 0)
                    ApplySurface(menu, screen, 0, 0);
                ApplySurface(replayButton, screen, 300, 620);
                 
                // Giai phong bo nho anh "Replay"
                SDL_FreeSurface(replayButton);

                //Cap nhat lai vector dan
                e.clear();
                a = plane.GetBullet();
                a.clear();
                plane.SetBullet(a);

                for (int i = 0; i < Sum_of_Enemy; i++)
                {
                    enemy_temp.SetX((rand() % SCREEN_WIDTH) / 2 + SCREEN_WIDTH);
                    enemy_temp.SetY(rand() % (SCREEN_HEIGHT - 175));
                    e.push_back(enemy_temp);
                }

                

                //Cap nhat lai mau
                /*vector <Heart_Object> temp = plane.GetMau();
                temp.clear();
                plane.SetMau(temp);*/
                plane.CreateMau();
                tt = 0;
            }  
        }
        //Cap nhat man hinh
        if (SDL_Flip(screen) == -1)
            return 0;
    }

    //Giai phong bo nho
    // Giải phóng bộ nhớ cho âm thanh
    Mix_FreeChunk(sound_shot);
    Mix_FreeChunk(sound_menu);
    Mix_FreeChunk(sound_boom);

    for (int i = 0; i < NUM_FRAMES; ++i)
        SDL_FreeSurface(frames[i]);
    /*for (int i = 0; i < NUM_FRAMES_ENTER; ++i)
        SDL_FreeSurface(frames_enter[i]);*/
    CleanUp(g);
    SDL_FreeSurface(plane.GetImage());
    SDL_Quit();
    return 1;
}