#pragma once
#include "Animal.h"

class Wolf : public Animal
{
    public:
        Wolf(Position position, int birthTurn);
        Wolf(Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory);
        bool interactsWith(std::string species) const override;
        std::shared_ptr<Organism> clone(const Position& pos, int birthTurn) const override;
};