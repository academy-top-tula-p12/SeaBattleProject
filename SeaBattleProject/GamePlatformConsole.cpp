#include "GamePlatformConsole.h"

GamePlatformConsole::GamePlatformConsole(Console* console)
	: console{ console } {}

void GamePlatformConsole::SetupGame(Player* humanPlayer)
{
	WindowConsole dialog(console, rowMain, columnMain, 7, 20 * sizeCell);
	dialog.Title() = "Player name";
	dialog.Show();

	console->Background(Colors::Gray);
	console->Rectangle(rowMain + 3, columnMain + 3, 1, 17 * sizeCell);
	console->CursorGoto(rowMain + 3, columnMain + 3);

	std::string name;
	std::getline(std::cin, name);

	humanPlayer->Name() = name;

	dialog.Hide();
}

void GamePlatformConsole::ViewGame(std::vector<Player*> players)
{
	console->Clear();

	auto builder = FieldConsole::GetBuilder(console);
	auto fieldHuman = builder.SetPoint(Point(rowMain, columnMain))
		->SetCellSize(2)
		->GetField();
	fieldHuman->Title() = players[0]->Name();

	fieldHuman->Show();

	/*auto fieldComputer = new FieldConsole(console);
	fieldComputer->Title() = players[1]->Name();

	fieldHuman*/
}
