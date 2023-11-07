#pragma once
#include <string>
#include "Field.h"
#include "Platform.h"

class IPlayerPlatform;

class Player
{
protected:
	std::string name;
	Field battleField;
	std::vector<Ship*> flotilla;
public:
	Player(std::string name);
	Player();

	std::string& Name();
	Field& BattleField();
	std::vector<Ship*>& Flotilla();
	int FlotillaSize();

	HitType CheckShot(Point point);
	
	virtual Point SetShot() = 0;
	virtual void SetFlotilla() = 0;
};

class HumanPlayer : public Player
{
	IPlayerPlatform* playerPlatform;
public:
	IPlayerPlatform*& PlayerPlatform() { return playerPlatform; }

	Point SetShot() override;
	void SetFlotilla() override;
};

class ComputerPlayer : public Player
{
public:
	Point SetShot() override;
	void SetFlotilla() override;
};

