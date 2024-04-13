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
const int NUM_FRAMES = 8;
const int FRAME_DELAY = 50; // milliseconds

//Khai bao bien toan cuc
extern SDL_Surface* screen;
extern SDL_Event event;

//Khai bao cac ham
bool Init();
void CleanUp(base_Object);
void ApplySurface(SDL_Surface*, SDL_Surface*, int, int);
SDL_Surface* SplitBackground(SDL_Surface*);

#endif