#pragma once
#include "Organism.h"

class Plant : public Organism
{
	public:
		Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn);
		Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory);

		bool interactsWith(std::string species) const override;
		void collision(std::shared_ptr<Organism> other) override;
		void move(Position position) override;
};