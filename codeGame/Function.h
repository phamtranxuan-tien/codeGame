#pragma once
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "base_Object.h"
#include "main_Object.h"
#include "bullet_Object.h"
#include "enemy_Object.h"
#include "Heart_Object.h"

using namespace std;

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//Khai bao cac hang so
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const int SCREEN_BPP = 32;
const int NUM_FRAMES = 8;
const int NUM_FRAMES_ENTER = 2;
const int FRAME_DELAY = 50; // milliseconds
const int FRAME_DELAY_ENTER = 3; // milliseconds
const int Sum_of_Enemy = 5;
//const int Sum_of_Enemy = 2;
const int Sum_of_Bullet = 30;
const int Sum_of_Enemy_Bullet = 1;
const int Sum_of_Heart = 3;

//Khai bao bien toan cuc
extern SDL_Surface* screen;
extern SDL_Event event;
extern int Play;
extern int y_val, x_val;

//Khai bao cac ham
bool Init(); //Khoi tao cua so window 
void CleanUp(base_Object); //Thu hoi bo nho
void ApplySurface(SDL_Surface*, SDL_Surface*, int, int); //Ve anh len man hinh
SDL_Surface* resizeImage(SDL_Surface*, int, int); //Doi kich thuoc anh

#endif