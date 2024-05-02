#ifndef _MAIN_
#define _MAIN_

/////OUTILS/////
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <math.h>
#include <cassert>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

/////SDL/////
#include "lib/include/SDL.h"
#include "lib/include/SDL_image.h"

/////FMOD/////
#include "lib/include/fmod.h"

#define MAP_WIDTH 15
#define MAP_HEIGHT 13
#define TILE_SIZE 32
#define OFFSET_X 5
#define OFFSET_Y 4
#define TIME_NORMALIZE 1000.0f  //1 => 1px/ms => 1000px/s ; 1000 => 1px/s

class STAGE;
class ENGINE;

extern ENGINE* g_pEngine;

/////APPLICATION/////
#include "tools.h"
#include "map.h"
#include "player.h"
#include "user.h"
#include "ai.h"
#include "bonus.h"
#include "bomb.h"
#include "fire.h"
#include "button.h"
#include "frame.h"
#include "transition.h"
#include "menu.h"
#include "stage.h"
#include "engine.h"

#endif
