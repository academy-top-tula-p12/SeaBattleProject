#pragma once
#include <iostream>
#include <string>

#include "Platform.h"
#include "Console.h"
#include "LibConsole.h"

class GamePlatformConsole : public IGamePlatform
{
	Console* console;

	int rowMain{ 2 };
	int columnMain{ 5 };
	int sizeCell{ 2 };
public:
	GamePlatformConsole(Console* console);

	void SetupGame(Player* humanPlayer) override;
	void ViewGame(std::vector<Player*> players) override;
};

