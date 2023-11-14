#pragma once
#include "Player.h"

class Player;
class IGamePlatform;
class IPlayerPlatform;

class Platform
{
	IGamePlatform* gamePlatform;
	IPlayerPlatform* playerPlatform;
public:
	Platform(IGamePlatform* gamePlatform,
		IPlayerPlatform* playerPlatform)
		: gamePlatform{ gamePlatform },
		playerPlatform{ playerPlatform } {}

	IGamePlatform* GamePlatform() { return gamePlatform; }
	IPlayerPlatform* PlayerPlatform() { return playerPlatform; }
};

class IGamePlatform
{
public:
	virtual void SetupGame() = 0;
	virtual void ViewGame() = 0;
	virtual void ViewShot(Point point, bool currentPlayer) = 0;

	virtual std::vector<Player*>& Players() = 0;
	//virtual void SetDestroy() = 0
};

class IPlayerPlatform
{
public:
	virtual std::vector<Ship*> SetFlotilla() = 0;
	virtual Point SetShot() = 0;
};




