#include "Game.h"

//Game::Game(Platform* platform)
//	:platform{ platform }
//{
//	HumanPlayer* humanPlayer = new HumanPlayer();
//	humanPlayer->PlayerPlatform() = platform->PlayerPlatform();
//	players.push_back(humanPlayer);
//
//	ComputerPlayer* computerPlayer = new ComputerPlayer();
//	players.push_back(computerPlayer);
//}

Game::Game()
{
	HumanPlayer* humanPlayer = new HumanPlayer();
	//humanPlayer->PlayerPlatform() = platform->PlayerPlatform();
	players.push_back(humanPlayer);
	
	ComputerPlayer* computerPlayer = new ComputerPlayer();
	players.push_back(computerPlayer);
}

void Game::Setup()
{

	for (int i = 0; i < players.size(); i++)
		players[i]->SetFlotilla();
}

void Game::View()
{
}

void Game::Process()
{
	currentPlayer = false;
	HitType hit;

	while (true)
	{
		View();
		Point point = players[currentPlayer]->SetShot();
		hit = players[!currentPlayer]->CheckShot(point);

		if (hit == HitType::Destroy)
			if (players[!currentPlayer]->FlotillaSize() == 0)
				break;

		if (hit == HitType::Beside)
			currentPlayer = !currentPlayer;
	}
}
