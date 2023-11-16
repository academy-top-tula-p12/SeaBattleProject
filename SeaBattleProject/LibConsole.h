#pragma once
#include "Console.h"
#include "Platform.h"

#define WATER 0x2592
#define DESK 0x2588
#define WATERCHAR 177
#define DESKCHAR 219

class FieldConsoleBuilder;

/// <summary>
/// //////////////////////
/// </summary>

class FieldConsole : public WindowConsole
{
	int sizeCell;
public:
	friend FieldConsoleBuilder;

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
	Console* console;
public:
	FieldConsoleBuilder(FieldConsole* field);

	void Reset();

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
	~ShipConsole()
	{
		if (ship)
			delete ship;
	}

	ShipConsole* SetSizeCell(int size);
	ShipConsole* SetAreaBegin(Point point);

	DirectionShip& Direction();

	Ship*& InnerShip();

	int Size();

	void Show() override;
	void Hide() override;
};


class CursorConsole : public WindowConsole
{
	int sizeCell;
	Point areaBegin;
public:
	CursorConsole(Console* console);
	CursorConsole* SetSizeCell(int size);
	CursorConsole* SetAreaBegin(Point point);

	void Show() override;
	void Hide() override;
};
