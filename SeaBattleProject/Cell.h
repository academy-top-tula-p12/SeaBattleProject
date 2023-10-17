#pragma once
struct Point
{
	int row;
	int column;
	Point(int row, int column)
		: row{ row }, column{ column } {}
	Point() : Point(0, 0) {}
};

enum class CellType
{
	Water,
	Deck
};


class Cell
{
	Point point;
	CellType type;
	bool isShot;
public:
	Cell(Point point);
	Cell(int row, int column);
	Cell();

	CellType& Type();
	bool& IsShot();
};

