#include "Player.h"

Player::Player(std::string name)
	: name{ name } {}

Player::Player() : Player("Computer") {}

std::string& Player::Name()
{
	return name;
}

Field& Player::BattleField()
{
	return battleField;
}

std::vector<Ship*>& Player::Flotilla()
{
	return flotilla;
}

int Player::FlotillaSize()
{
	int size{};
	for (Ship* ship : flotilla)
		if (!ship->IsDead())
			size++;
	return size;
}

HitType Player::CheckShot(Point point)
{
	HitType hit{ battleField.CheckShot(point) };
	battleField.SetCellShot(point);
	
	if (hit == HitType::Beside)
		return HitType::Beside;

	for (int i = 0; i < flotilla.size(); i++)
	{
		if (flotilla[i]->IsPoint(point))
		{
			flotilla[i]->Damage()++;
			if (flotilla[i]->IsDead())
				return HitType::Destroy;
			else
				return HitType::Wound;
		}
	}
}



Point HumanPlayer::SetShot()
{
	return playerPlatform->SetShot();
}

void HumanPlayer::SetFlotilla()
{
	flotilla = playerPlatform->SetFlotilla();
	battleField.SetShips(flotilla);
}


Point ComputerPlayer::SetShot()
{
	return Point(rand() % 10, rand() % 10);
}

void ComputerPlayer::SetFlotilla()
{
	flotilla.push_back(new Ship(Point(1, 3), 4, DirectionShip::Horizontal));
	
	flotilla.push_back(new Ship(Point(3, 0), 3, DirectionShip::Vertical));
	flotilla.push_back(new Ship(Point(9, 1), 3, DirectionShip::Horizontal));
	
	flotilla.push_back(new Ship(Point(4, 2), 2, DirectionShip::Horizontal));
	flotilla.push_back(new Ship(Point(4, 8), 2, DirectionShip::Horizontal));
	flotilla.push_back(new Ship(Point(7, 5), 2, DirectionShip::Vertical));

	flotilla.push_back(new Ship(Point(0, 1), 1, DirectionShip::Horizontal));
	flotilla.push_back(new Ship(Point(2, 9), 1, DirectionShip::Horizontal));
	flotilla.push_back(new Ship(Point(6, 2), 1, DirectionShip::Horizontal));
	flotilla.push_back(new Ship(Point(7, 8), 1, DirectionShip::Horizontal));

}
