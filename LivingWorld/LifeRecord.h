#pragma once
#include <string>

class LifeRecord {
private:
    int birthTurn;
    int deathTurn;
public:
    LifeRecord() = default;
    explicit LifeRecord(int birthTurn);

    int getBirthTurn() const;
    int getDeathTurn() const;
    void setDeathTurn(int deathTurn);
    std::string toString() const;
    void saveTo(std::ostream& out) const;
    void loadFrom(std::istream& in);
};