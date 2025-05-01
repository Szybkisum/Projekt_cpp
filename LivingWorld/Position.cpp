#include "Position.h"
#include <cmath>


Position::Position(int x, int y) : x(x), y(y) {};

int Position::getX() const
{
	return x;
}

void Position::setX(int x)
{
	if (x >= 0)
		this->x = x;
	else
		this->x = 0;
}

int Position::getY() const
{
	return y;
}

void Position::setY(int y)
{
	if (y >= 0)
		this->y = y;
	else
		this->y = 0;
}

std::string Position::toString() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

double Position::distance(Position position) const
{
	double dx = (double)x - (double)position.x;
	double dy = (double)y - (double)position.y;
	return sqrt( (dx * dx) + (dy * dy) );
}

void Position::move(int dx, int dy)
{
	this->x = (x + dx);
	this->y =(y + dy);
}
