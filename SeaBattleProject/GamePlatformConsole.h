#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Platform.h"
#include "Console.h"
#include "LibConsole.h"

class GamePlatformConsole : public IGamePlatform
{
	Console* console;

	int rowMain{ 2 };
	int columnMain{ 5 };
	int sizeCell{ 2 };

	std::vector<ShipConsole*> humanFlotilla;

	std::vector<Player*> players;

	FieldConsole* fieldHuman;
	FieldConsole* fieldComputer;

	void SetFlotillaConsole();
public:
	GamePlatformConsole(Console* console);

	std::vector<Player*>& Players() override;

	void SetupGame() override;
	void ViewGame() override;
	void ViewShot(Point point, bool currentPlayer, HitType hit) override;
};

