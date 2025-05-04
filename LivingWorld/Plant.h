#pragma once
#include "Organism.h"

class Plant : public Organism
{
	public:
		Plant();
		Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn);
		Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory);

		bool interactsWith(std::string species) const override;
		void collision(std::shared_ptr<Organism> other) override;
		void move(Position position) override;
		void saveTo(std::ostream& out, const std::unordered_map<LifeRecord*, int>& recordToID) const override;
		void loadFrom(std::istream& in, const std::vector<std::shared_ptr<LifeRecord>> idToRecord) override;
};