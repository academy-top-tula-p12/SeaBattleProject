#pragma once
#include "Console.h"
#include "Platform.h"

class FieldConsole : public WindowConsole
{
	int sizeCell;
	int sizeField;

	Point areaBegin;

public:
	FieldConsole(Console* console, int row, int column);

	void Show() override;
};

class ShipConsole : public WindowConsole
{
	Point point;
	int size;
	DirectionShip direction;

	int sizeCell;

	Point areaBegin;
public:
	ShipConsole(Console* console, Point point, int size, DirectionShip direction);

	DirectionShip& Direction();

	int Size();

	void Show() override;
	void Hide() override;
};
