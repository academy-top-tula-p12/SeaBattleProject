#include "Game.h"
#include "Console.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    /*Game game;
    game.Setup();
    game.View();

    game.Process();*/
    
    Console console;

    WindowConsole win2(&console);
    win2.Row() = 7;
    win2.Column() = 15;
    win2.AreaBack() = Colors::Magenta;
    win2.AreaFore() = Colors::Green;
    win2.Show();


    WindowConsole win(&console);
    win.Row() = 5;
    win.Column() = 10;
    win.AreaBack() = Colors::Green;
    win.Title() = "Hello World";

    win.Show();

    _getch();

    win.Hide();


    _getch();
    
}
