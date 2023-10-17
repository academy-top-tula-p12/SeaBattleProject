#include "Ship.h"

Ship::Ship(Point point, int size, DirectionShip direction)
	: point{ point },
	size{ size },
	direction{ direction },
	damage{} {}

Ship::Ship(int row, int column, int size, DirectionShip direction)
	: Ship(Point(row, column), size, direction) {}

Point Ship::GetPoint()
{
	return point;
}

int& Ship::Row()
{
	return point.row;
}

int& Ship::Column()
{
	return point.column;
}

int Ship::Size()
{
	return size;
}

DirectionShip& Ship::Direction()
{
	return direction;
}

int& Ship::Damage()
{
	return damage;
}

bool Ship::IsDead()
{
	return size == damage;
}

bool Ship::IsPoint(Point point)
{
	bool isPoint{ false };
	int row = this->point.row;
	int column = this->point.column;

	for (int s = 0; s < size; s++)
	{
		if (point.row == row && point.column == column)
			isPoint = true;
		(direction == DirectionShip::Horizontal) ? column++ : row++;
	}

	return isPoint;
}
