#pragma once
#include "Platform.h"
#include "Console.h"
#include "LibConsole.h"


class PlayerPlatformConsole : public IPlayerPlatform
{
	Console* console;

	std::vector<Ship> flotilla;
public:
	std::vector<Ship> SetFlotilla() override;

};

