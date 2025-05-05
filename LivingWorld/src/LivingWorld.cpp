#include <iostream>
#include "rendering.h"
#include <SDL.h>
#include "Position.h"
#include "Grass.h"
#include "Sheep.h"
#include "Dandelion.h"
#include "Wolf.h"
#include "Toadstool.h"
#include "World.h"

using namespace std;

int main(int, char*[]) {
    const int cellSize = 16;
    World world(60, 40);
    Position p1{ 1, 1 };
	Position p2{ 2, 19 };
	Position p3{ 10, 30 };
	Position p4{ 55, 39 };
	Position p5{ 30, 20 };
	world.addOrganism<Grass>(p1, world.getTurn());
	world.addOrganism<Sheep>(p2, world.getTurn());
	world.addOrganism<Dandelion>(p3, world.getTurn());
	world.addOrganism<Wolf>(p4, world.getTurn());
	world.addOrganism<Toadstool>(p5, world.getTurn());

    if (!initSDL(world.getWorldX() * cellSize,
                 world.getWorldY() * cellSize))
        return 1;
    renderWorld(world, cellSize);
    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN &&
                     e.key.keysym.sym == SDLK_RETURN) {
                world.makeTurn();
                renderWorld(world, cellSize);
            }
        }
        SDL_Delay(10);
    }
    shutdownSDL();
    return 0;
}
