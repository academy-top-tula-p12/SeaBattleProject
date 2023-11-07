#pragma once
#include "Ship.h"
#include <vector>

enum class HitType
{
	Beside,
	Reach,
	Wound,
	Destroy
};

class Field
{
	const int size{ 10 };
	std::vector<std::vector<Cell>> cells;
public:
	Field();
	void SetCellType(Point point, CellType type);
	void SetCellShot(Point point);
	Cell GetCell(int row, int column);
	Cell GetCell(Point point);

	void SetShips(std::vector<Ship*> flotilla);
	HitType CheckShot(Point point);
};

