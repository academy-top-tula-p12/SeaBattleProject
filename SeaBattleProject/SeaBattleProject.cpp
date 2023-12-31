﻿#include "Game.h"
#include "Console.h"
#include "PlayerPlatformConsole.h"
#include "GamePlatformConsole.h"

void tempFunction()
{

    ////setlocale(LC_ALL, "Russian");

    ///*Game game;
    //game.Setup();
    //game.View();

    //game.Process();*/

    //Console* console = new Console();

    ////WindowConsole win(console, 3, 5, 10, 10);
    //FieldConsole field(console, 2, 5);
    ////win.Show();
    //field.Show();

    //ShipConsole ship(console, Point(2, 2), 3, DirectionShip::Vertical);
    //ship.Show();

    //KeyCode key = KeyCode::Enter;
    //bool isQuit = false;

    //while (true)
    //{
    //    if (console->KeyPressed())
    //    {
    //        key = (KeyCode)console->GetChar();

    //        ship.Hide();

    //        switch (key)
    //        {
    //        case ArrowUp:
    //            ship.Row()--;
    //            break;
    //        case ArrowDown:
    //            ship.Row()++;
    //            break;
    //        case ArrowLeft:
    //            ship.Column()--;
    //            break;
    //        case ArrowRight:
    //            ship.Column()++;
    //            break;
    //        case Enter:
    //            break;
    //        case Space:
    //            if (ship.Direction() == DirectionShip::Horizontal)
    //                ship.Direction() = DirectionShip::Vertical;
    //            else
    //                ship.Direction() = DirectionShip::Horizontal;
    //            break;
    //        case Esc:
    //            isQuit = true;
    //            break;
    //        default:
    //            break;
    //        }

    //        if (isQuit) break;
    //        ship.Show();
    //    }
    //}

    ////console->GetChar();
}


int main()
{
    Console* console = new Console();

    //PlayerPlatformConsole playerPlatform(console);
    //playerPlatform.SetFlotilla();

    //GamePlatformConsole gamePlatform(console);
    //gamePlatform.SetupGame(new HumanPlayer());

    Game* game = new Game(
        new Platform(
            new GamePlatformConsole(console),
            new PlayerPlatformConsole(console)
        )
    );

    game->Setup();
    //game->View();
    /*Point point = game->players[0]->SetShot();
    std::cout << "row: " << point.row
        << "column: " << point.column << "\n";*/

    game->Process();

    console->GetChar();
}
