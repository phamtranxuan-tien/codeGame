#pragma once
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <vector>
#include "base_Object.h"
#include "main_Object.h"
#include "bullet_Object.h"
#include "enemy_Object.h"

using namespace std;

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//Khai bao cac hang so
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;
const int NUM_FRAMES = 80;
// const int FRAME_DELAY = 100; // milliseconds

const int FPS = 60; // Tần số khung hình mong muốn (60 khung hình mỗi giây)
const int FRAME_DELAY = 150 / FPS; // Thời gian trễ giữa mỗi khung hình


//Khai bao bien toan cuc
extern SDL_Surface* screen;
extern SDL_Event event;

//Khai bao cac ham
bool Init();
void CleanUp(base_Object);
void ApplySurface(SDL_Surface*, SDL_Surface*, int, int);
SDL_Surface* SplitBackground(SDL_Surface*);

#endif