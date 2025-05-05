#include "rendering.h"
#include <iostream>

SDL_Window*   gWindow   = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool initSDL(int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;
    gWindow = SDL_CreateWindow("LivingWorld",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    if (!gWindow) return false;
    gRenderer = SDL_CreateRenderer(gWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    return gRenderer != nullptr;
}

void shutdownSDL() {
    if (gRenderer) SDL_DestroyRenderer(gRenderer);
    if (gWindow)   SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

static void setColorForSpecies(const std::string& spec) {
    if      (spec == "G") SDL_SetRenderDrawColor(gRenderer,   0, 255,   0, 255); // Grass: green
    else if (spec == "S") SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); // Sheep: white
    else if (spec == "D") SDL_SetRenderDrawColor(gRenderer, 255, 255,   0, 255); // Dandelion: yellow
    else if (spec == "W") SDL_SetRenderDrawColor(gRenderer, 255,   0,   0, 255); // Wolf: red
    else if (spec == "T") SDL_SetRenderDrawColor(gRenderer, 128,   0, 128, 255); // Toadstool: purple
    else                  SDL_SetRenderDrawColor(gRenderer,   0,   0,   0, 255); // Empty: black
}

void renderWorld(const World& world, int cellSize) {
    int rows = world.getWorldY();
    int cols = world.getWorldX();
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            std::string spec = world.getSpeciesFromPosition(x, y);
            setColorForSpecies(spec);
            SDL_Rect r{ x * cellSize, y * cellSize, cellSize, cellSize };
            SDL_RenderFillRect(gRenderer, &r);
        }
    }

    SDL_RenderPresent(gRenderer);
}