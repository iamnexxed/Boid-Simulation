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


// Button constants
const int BUTTON_WIDTH = 125;
const int BUTTON_HEIGHT = 125;
const int TOTAL_BUTTONS = 4;


// Boid Parameters
const int NOOFBOIDS = 50;
const double MAX_STEERING_FORCE = 0.9;
const double DETECTION_RADIUS = 50;
const double BOID_SPEED = 4;
const double ESCAPE_CROWD_RADIUS = 40;