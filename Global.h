#pragma once

//Using SDL and standard IO
#include <stdio.h>
#include <stdlib.h>  
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <time.h>
#include <math.h>

#include <unordered_set>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Window Name
#define WINDOW_NAME "Boids"