#pragma once
#include "Player.h"

class IGamePlatform;
class IPalyerPlatform;
//
//class Platform
//{
//	IGamePlatform* gamePlatform;
//	IPalyerPlatform* playerPlatform;
//public:
//	Platform(IGamePlatform* gamePlatform,
//		IPalyerPlatform* playerPlatform)
//		: gamePlatform{ gamePlatform },
//		playerPlatform{ playerPlatform } {}
//
//	IGamePlatform* GamePlatform() { return gamePlatform; }
//	IPalyerPlatform* PlayerPlatform() { return playerPlatform; }
//};
//
class IGamePlatform
{
public:
	virtual void SetupGame(Player* humanPlayer) = 0;
	virtual void ViewGame(std::vector<Player*> players) = 0;
};

class IPalyerPlatform
{
public:
	virtual std::vector<Ship> SetFlotilla() = 0;
	virtual Point SetShot() = 0;
};

