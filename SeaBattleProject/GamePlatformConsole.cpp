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

void GamePlatformConsole::ViewShot(Point point, bool currentPlayer)
{
	FieldConsole* field = (currentPlayer) ? fieldComputer : fieldHuman;

	//char fill = ()
}
