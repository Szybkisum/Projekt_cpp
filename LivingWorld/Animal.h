#pragma once
#include "Organism.h"

class Animal : public Organism
{
    private:
        Position lastPosition;
    public:
        Animal();
        Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn);
        Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory);

        void collision(std::shared_ptr<Organism> other) override;
        void move(Position position) override;
        void saveTo(std::ostream& out, const std::unordered_map<LifeRecord*, int>& recordToID) const override;
        void loadFrom(std::istream& out, const std::vector<std::shared_ptr<LifeRecord>>& idToRecord) override;
};