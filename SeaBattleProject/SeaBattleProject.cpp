#include "Game.h"
#include "Console.h"
#include "PlayerPlatformConsole.h"

int main()
{
    //setlocale(LC_ALL, "Russian");

    /*Game game;
    game.Setup();
    game.View();

    game.Process();*/

    Console* console = new Console();
    
    //WindowConsole win(console, 3, 5, 10, 10);
    FieldConsole field(console, 2, 5, 10);
    //win.Show();
    field.Show();

    _getch();
}
