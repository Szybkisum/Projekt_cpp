#pragma once
#include "Organism.h"

class Plant : public Organism
{
	public:
		Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn);
		Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory);

        std::shared_ptr<Organism> clone(const Position& pos, int birthTurn) const override;
		void move(int dx, int dy) override;
};