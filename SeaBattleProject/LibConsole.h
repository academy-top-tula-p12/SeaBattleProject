#pragma once
#include "Console.h"
#include "Platform.h"

class FieldConsoleBuilder;

/// <summary>
/// //////////////////////
/// </summary>

class FieldConsole : public WindowConsole
{
	int sizeCell;

public:
	const int SizeField{ 10 };
	const Point AreaBegin{ 1, 2 };

	FieldConsole(Console* console);

	int& SizeCell();

	static FieldConsoleBuilder GetBuilder(Console* console);
	void Show() override;
};

class FieldConsoleBuilder
{
	FieldConsole* field;
public:
	FieldConsoleBuilder(FieldConsole* field);

	FieldConsoleBuilder* SetPoint(Point point);
	FieldConsoleBuilder* SetCellSize(int size);
	FieldConsoleBuilder* SetColorBack(Colors color);

	FieldConsole* GetField();
};




/// <summary>
/// ////////////////////////
/// </summary>

/*
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
*/

class ShipConsole : public WindowConsole
{
	Ship* ship;
	int sizeCell;
	Point areaBegin;
public:
	ShipConsole(Console* console, int size);

	ShipConsole* SetSizeCell(int size);
	ShipConsole* SetAreaBegin(Point point);

	DirectionShip& Direction();

	Ship*& InnerShip();

	int Size();

	void Show() override;
	void Hide() override;
};
