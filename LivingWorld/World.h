#pragma once

#include <ctime>
#include <algorithm>
#include "Organism.h"

class World
{
private:
	int worldX;
	int worldY;
	int turn = 0;
	std::vector<std::unique_ptr<Organism>> organisms;
	char separator = '.';

	std::string getSpeciesFromPosition(int x, int y) const;
	bool isPositionOnWorld(int x, int y) const;
	bool isPositionFree(Position position) const;

public:
	World();
	World(int worldX, int worldY);

	int getWorldX() const;
	void setWorldX(int worldX);
	int getWorldY() const;
	void setWorldY(int worldY);
	int getTurn() const;
	

	void addOrganismPtr(std::unique_ptr<Organism> org);

	template <typename T, typename... Args>
    T* addOrganism(Args&&... args) {
        static_assert(std::is_base_of<Organism, T>::value,
                      "T must derive from Organism");
        auto org = std::make_unique<T>(std::forward<Args>(args)...);
        T* rawPtr = ptr.get();
		addOrganismPtr(std::move(org));
        return rawPtr;
    }
	void removeOrganism(Organism* org);
	std::vector<Position> getVectorOfFreePositionsAround(Position position) const;

	void makeTurn();
	void writeWorld(std::string fileName) const;
	void readWorld(std::string fileName);
	std::string toString() const;
};

