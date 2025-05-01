#include <iostream>
#include "Position.h"
#include "Plant.h"
#include "Animal.h"
#include "World.h"

using namespace std;

int main()
{
	World world(10, 10);

	Position p1{ 1, 1 };
	Position p2{ 3, 5 };

	world.addOrganism<Plant>(0, 5, 5, 2, p1, world.getTurn());
	world.addOrganism<Animal>(0, 5, 5, 2, p2, world.getTurn());

	// Tura 0
	cout << world.toString() << endl;
	world.printOrganisms();

	int turns = 5;
	for (int i = 0; i < turns; i++) {
		world.makeTurn();
		cout << world.toString() << endl;
		world.printOrganisms();
	}

	return 0;
}
