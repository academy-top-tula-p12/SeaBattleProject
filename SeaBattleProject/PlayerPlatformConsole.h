#pragma once
#include <array>
#include <string>

#include "Platform.h"
#include "Console.h"
#include "LibConsole.h"


class PlayerPlatformConsole : public IPlayerPlatform
{
	Console* console;
	std::vector<Ship> flotilla;


	std::vector<ShipConsole> ships;
	std::array<int, 4> counts{ 4, 3, 2, 1 };
	int rowMain{ 2 };
	int columnMain{ 5 };

	int SelectShip();
	ShipConsole* SetShip(int size);
	bool IsSetShip(ShipConsole* ship);
public:
	PlayerPlatformConsole(Console* console) : console{ console } {}

	std::vector<Ship> SetFlotilla() override;
	Point SetShot() override { return Point(); };
};

