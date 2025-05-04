#pragma once
#include "Plant.h"

class Dandelion : public Plant
{
    public:
        Dandelion();
        Dandelion(Position position, int birthTurn);
        Dandelion(Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory);
        std::shared_ptr<Organism> clone(const Position& pos, int birthTurn) const override;
};