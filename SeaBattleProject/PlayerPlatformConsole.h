#pragma once
#include "Platform.h"
#include "Console.h"

class FieldConsole : public WindowConsole
{
	int sizeCell;
	int sizeField;

	Point areaBegin;

public:
	FieldConsole(Console* console, int row, int column, int size);

	void Show() override;
};

class PlayerPlatformConsole : public IPlayerPlatform
{
	Console* console;

	std::vector<Ship> flotilla;
public:
	std::vector<Ship> SetFlotilla() override;

};

