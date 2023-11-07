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
	return Point();
}

void ComputerPlayer::SetFlotilla()
{

}
