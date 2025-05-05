#include <iostream>
#include "Position.h"
#include "Grass.h"
#include "Sheep.h"
#include "Dandelion.h"
#include "Wolf.h"
#include "Toadstool.h"
#include "World.h"

using namespace std;

int main()
{
	World world(10, 10);

	Position p1{ 1, 1 };
	Position p2{ 3, 5 };
	Position p3{ 3, 9 };
	Position p4{ 7, 8 };
	Position p5{ 5, 5 };

	world.addOrganism<Grass>(p1, world.getTurn());
	world.addOrganism<Sheep>(p2, world.getTurn());
	world.addOrganism<Dandelion>(p3, world.getTurn());
	world.addOrganism<Wolf>(p4, world.getTurn());
	world.addOrganism<Toadstool>(p5, world.getTurn());

	cout << world.toString() << endl;
	world.printOrganisms();

	for (int i = 0; i < 10; i++) {
		world.makeTurn();
		cout << world.toString() << endl;
		world.printOrganisms();
	}

	std::cout << "Saving" << std::endl;
	world.saveTo("saves/world.bin");

	for (int i = 0; i < 10; i++) {
		world.makeTurn();
		cout << world.toString() << endl;
		world.printOrganisms();
	}

	std::cout << "Loading" << std::endl;
	world.loadFrom("saves/world.bin");

	for (int i = 0; i < 10; i++) {
		world.makeTurn();
		cout << world.toString() << endl;
		world.printOrganisms();
	}

	return 0;
}
