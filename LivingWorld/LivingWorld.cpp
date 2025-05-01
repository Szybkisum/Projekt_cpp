#include <iostream>
#include "Position.h"
#include "Organism.h"
#include "World.h"

using namespace std;

int main()
{
	World world(10, 10);

	Position p1{ 1, 1 };
	Position p2{ 3, 5 };

	Organism* org1 = world.addOrganism<Organism>(5, 3, 20, 8, p1, world.getTurn());
	Organism* org2 =world.addOrganism<Organism>(5, 3, 20, 8, p2, world.getTurn());

	cout << org1->toString() << endl;
	cout << org2->toString() << endl;

	// Tura 0
	cout << world.toString() << endl;
	cout << org1->toString() << endl;
	cout << org2->toString() << endl;

	// Tura 1
	world.makeTurn();
	cout << world.toString() << endl;
	cout << org1->toString() << endl;
	cout << org2->toString() << endl;

	// Tura 2
	world.makeTurn();
	cout << world.toString() << endl;
	cout << org1->toString() << endl;
	cout << org2->toString() << endl;

	// world.writeWorld("world.bin");

	// // Tura 3
	// world.makeTurn();
	// cout << world.toString() << endl;

	// // powrot do Tury 2
	// world.readWorld("world.bin");
	// cout << world.toString() << endl;

	return 0;
}
