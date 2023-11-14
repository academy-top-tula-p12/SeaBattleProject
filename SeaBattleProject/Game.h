#pragma once

#include "Player.h"
#include "Platform.h"

class Game
{
	
	bool currentPlayer{ false };

	Platform* platform;
public:
	std::vector<Player*> players;

	Game(Platform* platform = nullptr);
	Game();
	
	void Setup();
	void View();
	void Process();
};

