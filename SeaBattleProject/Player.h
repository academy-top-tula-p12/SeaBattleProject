#pragma once
#include <string>
#include "Field.h"
#include "Platform.h"

class Player
{
protected:
	std::string name;
	Field battleField;
	std::vector<Ship> flotilla;
public:
	Player(std::string name);
	Player();

	std::string& Name();
	Field& BattleField();
	std::vector<Ship>& Flotilla();
	int FlotillaSize();

	HitType CheckShot(Point point);
	
	virtual Point SetShot() = 0;
	virtual void SetFlotilla() = 0;
};

class HumanPlayer : public Player
{
	//IPalyerPlatform* playerPlatform;
public:
	//IPalyerPlatform*& PlayerPlatform() { return playerPlatform; }

	Point SetShot() override
	{
		return Point();
		//return playerPlatform->SetShot();
	}

	void SetFlotilla() override
	{
		//flotilla = playerPlatform->SetFlotilla();
		battleField.SetShips(flotilla);
	}
};

class ComputerPlayer : public Player
{
public:
	Point SetShot() override
	{
		return Point();
	}

	void SetFlotilla() override
	{

	}
};

