#pragma once

#include "Organism.h"

class World
{
private:
	int worldX;
	int worldY;
	int turn = 0;
	std::vector<std::shared_ptr<Organism>> organisms;
	char separator = '.';

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
	
	std::shared_ptr<Organism> getOrganismFromPosition(int x, int y) const;
	std::string getSpeciesFromPosition(int x, int y) const;

	void removeOrganism(std::shared_ptr<Organism> org);
	void addOrganismPtr(std::shared_ptr<Organism> org);

	template <typename T, typename... Args>
    T* addOrganism(Args&&... args) {
        static_assert(std::is_base_of<Organism, T>::value,
                      "T must derive from Organism");
        auto org = std::make_shared<T>(std::forward<Args>(args)...);
        T* rawPtr = org.get();
		addOrganismPtr(std::move(org));
        return rawPtr;
    }
	std::vector<Position> getVectorOfFreePositionsAround(Position position) const;
	std::vector<Position> getVectorOfPossiblePositionsForOrganism(std::shared_ptr<Organism> org) const;

	void makeTurn();
	void saveTo(std::string fileName) const;
	void loadFrom(const std::string& fileName);
	std::string toString() const;
	void printOrganisms() const;
};

