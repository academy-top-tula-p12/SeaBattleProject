#include "Game.h"
#include <ctime>

Game::Game(Platform* platform)
	:platform{ platform }
{
	srand(std::time(nullptr));

	HumanPlayer* humanPlayer = new HumanPlayer();
	humanPlayer->PlayerPlatform() = platform->PlayerPlatform();
	players.push_back(humanPlayer);

	ComputerPlayer* computerPlayer = new ComputerPlayer();
	players.push_back(computerPlayer);

	platform->GamePlatform()->Players() = players;
}


Game::Game()
{
	HumanPlayer* humanPlayer = new HumanPlayer();
	humanPlayer->PlayerPlatform() = platform->PlayerPlatform();
	players.push_back(humanPlayer);
	
	ComputerPlayer* computerPlayer = new ComputerPlayer();
	players.push_back(computerPlayer);
}

void Game::Setup()
{
	platform->GamePlatform()->SetupGame();

	for (int i = 0; i < players.size(); i++)
		players[i]->SetFlotilla();
}

void Game::View()
{
	platform->GamePlatform()->ViewGame();
}

void Game::Process()
{
	currentPlayer = false;
	HitType hit;

	View();

	while (true)
	{
		Point point = players[currentPlayer]->SetShot();

		if (point.row == -1)
			break;

		hit = players[!currentPlayer]->CheckShot(point);

		platform->GamePlatform()->ViewShot(point, currentPlayer, hit);

		if (hit == HitType::Destroy)
		{
			if (players[!currentPlayer]->FlotillaSize() == 0)
				break;
			// 
		}
			

		if (hit == HitType::Beside)
			currentPlayer = !currentPlayer;
	}
}
