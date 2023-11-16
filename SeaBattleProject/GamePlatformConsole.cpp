#include "GamePlatformConsole.h"


void GamePlatformConsole::SetFlotillaConsole()
{
	for (auto ship : players[0]->Flotilla())
	{
		ShipConsole* shipConsole = new ShipConsole(console, ship->Size());
		shipConsole->InnerShip() = ship;
		shipConsole->Direction() = ship->Direction();
		shipConsole->SetAreaBegin(Point(rowMain, columnMain));
		shipConsole->AreaBack() = Colors::Green;
		shipConsole->AreaFore() = Colors::Green;
		shipConsole->SetSizeCell(sizeCell);

		humanFlotilla.push_back(shipConsole);
	}
	
}

GamePlatformConsole::GamePlatformConsole(Console* console)
	: console{ console }
{
	auto builder = FieldConsole::GetBuilder(console);
	fieldHuman = builder.SetPoint(Point(rowMain, columnMain))
		->SetCellSize(sizeCell)
		->GetField();

	builder.Reset();
	int computerFieldColumn = columnMain + (fieldHuman->SizeField + 4) * sizeCell * 2;
	fieldComputer = builder.SetPoint(Point(rowMain, computerFieldColumn))
		->SetCellSize(sizeCell)
		->GetField();

	
	
}

std::vector<Player*>& GamePlatformConsole::Players()
{
	return players;
}

void GamePlatformConsole::SetupGame()
{
	WindowConsole dialog(console, rowMain, columnMain, 7, 20 * sizeCell);
	dialog.Title() = "Player name";
	dialog.Show();

	console->Background(Colors::Gray);
	console->Rectangle(rowMain + 3, columnMain + 3, 1, 17 * sizeCell);
	console->CursorGoto(rowMain + 3, columnMain + 3);

	std::string name;
	std::getline(std::cin, name);

	players[0]->Name() = name;

	fieldHuman->Title() = players[0]->Name();
	fieldComputer->Title() = players[1]->Name();

	dialog.Hide();
}

void GamePlatformConsole::ViewGame()
{
	SetFlotillaConsole();

	console->Clear();
	fieldHuman->Show();

	for (auto shipConsole : humanFlotilla)
		shipConsole->Show();

	fieldComputer->Show();
}

void GamePlatformConsole::ViewShot(Point point, bool currentPlayer, HitType hit)
{
	FieldConsole* fieldConsole = (currentPlayer) ? fieldHuman : fieldComputer;
	Field* field = &players[!currentPlayer]->BattleField();

	CellType type = field->GetCell(point).Type();
	char symbolFill = (type == CellType::Water) ? WATERCHAR : DESKCHAR;
	
	int row{ fieldConsole->Row() + fieldConsole->AreaBegin.row + 1 + point.row * sizeCell };
	int column{ fieldConsole->Column() + fieldConsole->AreaBegin.column + 1 + point.column * 2 * sizeCell };

	int width = sizeCell * 2;
	int heigth = sizeCell;

	console->Foreground(Colors::Red);
	if(hit == HitType::Wound)
		console->Foreground(Colors::Magenta);
	
	console->Rectangle(row, column, heigth, width, symbolFill);

	if (hit == HitType::Destroy)
	{
		Ship* shipDestroy{};
		for (auto ship : players[!currentPlayer]->Flotilla())
			if (ship->IsPoint(point))
				shipDestroy = ship;

		int rw = shipDestroy->Row();
		int cw = shipDestroy->Column();

		int hw = (shipDestroy->Direction() == DirectionShip::Horizontal) ? 1 : shipDestroy->Size();
		int ww = (shipDestroy->Direction() == DirectionShip::Vertical) ? 1 : shipDestroy->Size();

		if (rw > 0)
		{
			rw--;
			hw++;
		}

		if (cw > 0)
		{
			cw--;
			ww++;
		}
			
		if (rw + hw < 10) hw++;
		if (cw + ww < 10) ww++;

		rw = fieldConsole->Row() + fieldConsole->AreaBegin.row + 1 + rw * sizeCell;
		cw = fieldConsole->Column() + fieldConsole->AreaBegin.column + 1 + cw * 2 * sizeCell;
		hw = hw * sizeCell;
		ww = ww * 2 * sizeCell;

		console->Background(Colors::Blue);
		console->Foreground(Colors::Red);
		console->Rectangle(rw, cw, hw, ww, WATERCHAR);

		int r = fieldConsole->Row() + fieldConsole->AreaBegin.row + 1 + shipDestroy->Row() * sizeCell;
		int c = fieldConsole->Column() + fieldConsole->AreaBegin.column + 1 + shipDestroy->Column() * 2 * sizeCell;

		int w{};
		int h{};

		if (shipDestroy->Direction() == DirectionShip::Horizontal)
		{
			h = sizeCell;
			w = shipDestroy->Size() * 2 * sizeCell;
		}
		else
		{
			h = shipDestroy->Size() * sizeCell;
			w = 2 * sizeCell;
		}

		//console->Foreground(Colors::Red);
		console->Rectangle(r, c, h, w, DESKCHAR);
	}
}
