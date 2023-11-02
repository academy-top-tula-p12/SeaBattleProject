#include "PlayerPlatformConsole.h"
#include "LibConsole.h"

int PlayerPlatformConsole::SelectShip()
{
    int columnShips{ columnMain + 10 * 2 * 2 + 20 };
    int hShip{ 2 };
    int wShip{ 4 };

    int currentShip{ 2 };

    for (int size = 0; size < 4; size++)
    {
        console->Background(Colors::Gray);
        console->WriteGoto(rowMain + 1 + size * hShip * 2, columnShips - 2, std::to_string(counts[size]));
        if (counts[size])
        {
            if(size == currentShip)
                console->Background(Colors::Blue);
            else
                console->Background(Colors::Green);
        }
            
        else
            console->Background(Colors::Magenta);
        console->Rectangle(rowMain + size * hShip * 2, columnShips, 2, (size + 1) * 2 * 2);
    }



    KeyCode key = KeyCode::Enter;
    bool isQuit = false;
    int i;


    while (true)
    {
        if (console->KeyPressed())
        {
            key = (KeyCode)console->GetChar();
            bool isNotOk;
            switch (key)
            {
            case ArrowUp:
            case ArrowLeft:
                isNotOk = true;
                for (i = currentShip - 1; i >= 0; i--)
                    if (counts[i])
                    {
                        isNotOk = false;
                        break;
                    }
                if (!isNotOk)
                    currentShip = i;
                break;

            case ArrowDown:
            case ArrowRight:
                isNotOk = true;
                for (i = currentShip + 1; i <= 3; i++)
                    if (counts[i])
                    {
                        isNotOk = false;
                        break;
                    }
                if (!isNotOk)
                    currentShip = i;
                break;
            case Enter:
                isQuit = true;
                break;
            case Esc:
                break;
            default:
                break;
            }
            for (int size = 0; size < 4; size++)
            {
                console->Background(Colors::Gray);
                console->WriteGoto(rowMain + 1 + size * hShip * 2, columnShips - 2, std::to_string(counts[size]));
                if (counts[size])
                {
                    if (size == currentShip)
                        console->Background(Colors::Blue);
                    else
                        console->Background(Colors::Green);
                }

                else
                    console->Background(Colors::Magenta);
                console->Rectangle(rowMain + size * hShip * 2, columnShips, 2, (size + 1) * 2 * 2);
            }
        }
        if (isQuit) break;
    }
    return currentShip;
}

ShipConsole* PlayerPlatformConsole::SetShip(int size)
{
    ShipConsole* ship = new ShipConsole(console, 
                                        Point(2, 2), 
                                        size + 1, 
                                        DirectionShip::Horizontal);
    ship->Show();
    KeyCode key = KeyCode::Enter;
    bool isQuit = false;
    int r{}, c{};


    while (true)
    {
        if (console->KeyPressed())
        {
            key = (KeyCode)console->GetChar();

            ship->Hide();

            switch (key)
            {
            case ArrowUp:
                if (r > 0)
                {
                    ship->Row()--;
                    r--;
                }
                break;
            case ArrowDown:
                if (ship->Direction() == DirectionShip::Horizontal)
                {
                    if (r < 9)
                    {
                        ship->Row()++;
                        r++;
                    }
                }
                else
                {
                    if (r + ship->Size() < 10)
                    {
                        ship->Row()++;
                        r++;
                    }
                }
                break;
            case ArrowLeft:
                if (c > 0)
                {
                    ship->Column()--;
                    c--;
                }
                    
                break;
            case ArrowRight:
                if (ship->Direction() == DirectionShip::Vertical)
                {
                    if (c < 9)
                    {
                        ship->Column()++;
                        c++;
                    }
                }
                else
                {
                    if (c + ship->Size() < 10)
                    {
                        ship->Column()++;
                        c++;
                    }
                }
                break;
            case Enter:
                isQuit = IsSetShip(ship);
                break;
            case Space:
                if (ship->Direction() == DirectionShip::Horizontal)
                {
                    if(r + ship->Size() < 11)
                        ship->Direction() = DirectionShip::Vertical;
                }
                else
                {
                    if(c + ship->Size() < 11)
                        ship->Direction() = DirectionShip::Horizontal;
                }
                    
                break;
            case Esc:
                ship = nullptr;
                isQuit = true;
                break;
            default:
                break;
            }

            if (isQuit) break;
            ship->Show();
        }
    }
    return ship;
}

bool PlayerPlatformConsole::IsSetShip(ShipConsole* ship)
{
    for (int dr = -1; dr < ship->Size() + 1; dr++)
    {

    }

    return true;
}

std::vector<Ship> PlayerPlatformConsole::SetFlotilla()
{
    
    int currentShip{};

    FieldConsole field(console, rowMain, columnMain);

    field.Show();
    currentShip = SelectShip();

    ShipConsole* ship = SetShip(currentShip);
    

    

    console->GetChar();

    //while (true)
    //{
    //    // ViewField();
    //    // Ship ship = SetShip();
    //    // flotilla.push_back(ship);
    //    if (flotilla.size() == 10)
    //        break;
    //}
    

    return std::vector<Ship>();
}
