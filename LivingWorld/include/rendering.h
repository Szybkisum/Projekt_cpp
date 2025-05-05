#pragma once
#include <SDL.h>
#include "World.h"

bool initSDL(int width, int height);
void shutdownSDL();
void renderWorld(const World& world, int cellSize);
extern SDL_Renderer* gRenderer;