#include "PlayerPlatformConsole.h"
#include "LibConsole.h"

int PlayerPlatformConsole::SelectShip()
{
    int columnShips{ columnMain + 10 * 2 * sizeCell + 20 };
    int hShip{ sizeCell };
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
        console->Rectangle(rowMain + size * hShip * 2, columnShips, sizeCell, (size + 1) * 2 * sizeCell);
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
                console->Rectangle(rowMain + size * hShip * 2, columnShips, sizeCell, (size + 1) * 2 * sizeCell);
            }
        }
        if (isQuit) break;
    }
    return currentShip;
}

ShipConsole* PlayerPlatformConsole::SetShip(int size)
{
    ShipConsole* shipConsole = (new ShipConsole(console, size))
        ->SetSizeCell(sizeCell)
        ->SetAreaBegin(Point(rowMain, columnMain));

    shipConsole->Show();

    KeyCode key = KeyCode::Enter;
    bool isQuit = false;
    //int r{}, c{};


    while (true)
    {
        isQuit = false;
        if (console->KeyPressed())
        {
            key = (KeyCode)console->GetChar();

            shipConsole->Hide();

            switch (key)
            {
            case ArrowUp:
                if (shipConsole->InnerShip()->Row() > 0)
                {
                    shipConsole->Row()--;
                    shipConsole->InnerShip()->Row()--;
                }
                break;
            case ArrowDown:
                if (shipConsole->Direction() == DirectionShip::Horizontal)
                {
                    if (shipConsole->InnerShip()->Row() < 9)
                    {
                        shipConsole->Row()++;
                        shipConsole->InnerShip()->Row()++;
                    }
                }
                else
                {
                    if (shipConsole->InnerShip()->Row() + shipConsole->Size() < 10)
                    {
                        shipConsole->Row()++;
                        shipConsole->InnerShip()->Row()++;
                    }
                }
                break;
            case ArrowLeft:
                if (shipConsole->InnerShip()->Column() > 0)
                {
                    shipConsole->Column()--;
                    shipConsole->InnerShip()->Column()--;
                }
                    
                break;
            case ArrowRight:
                if (shipConsole->Direction() == DirectionShip::Vertical)
                {
                    if (shipConsole->InnerShip()->Column() < 9)
                    {
                        shipConsole->Column()++;
                        shipConsole->InnerShip()->Column()++;
                    }
                }
                else
                {
                    if (shipConsole->InnerShip()->Column() + shipConsole->Size() < 10)
                    {
                        shipConsole->Column()++;
                        shipConsole->InnerShip()->Column()++;
                    }
                }
                break;
            case Enter:
                isQuit = IsSetShip(shipConsole);
                break;
            case Space:
                if (shipConsole->Direction() == DirectionShip::Horizontal)
                {
                    if(shipConsole->InnerShip()->Row() + shipConsole->Size() < 11)
                        shipConsole->Direction() = DirectionShip::Vertical;
                }
                else
                {
                    if(shipConsole->InnerShip()->Column() + shipConsole->Size() < 11)
                        shipConsole->Direction() = DirectionShip::Horizontal;
                }
                    
                break;
            case Esc:
                shipConsole = nullptr;
                isQuit = true;
                break;
            default:
                break;
            }

            if (isQuit) break;
            shipConsole->Show();
        }
    }
    return shipConsole;
}

bool PlayerPlatformConsole::IsSetShip(ShipConsole* ship)
{   
    bool isWrong = false;

    for (auto shipConsole : shipsConsole)
    {
        int r = ship->InnerShip()->Row();
        int c = ship->InnerShip()->Column();

        for (int i = 0; i < ship->Size(); i++)
        {
            for (int rx = -1; rx < 2; rx++)
            {
                for (int cx = -1; cx < 2; cx++)
                {
                    isWrong = shipConsole->InnerShip()->IsPoint(Point(r + rx, c + cx));
                    if (isWrong) break;
                }
                if (isWrong) break;
            }
            if (isWrong) break;
            
            (ship->Direction() == DirectionShip::Horizontal) ? c++ : r++;
        }
    }

    return !isWrong;
}

void PlayerPlatformConsole::ShowShips()
{
    for (auto shipConsole : shipsConsole)
    {
        int rBegin = rowMain + 2 + shipConsole->InnerShip()->Row() * sizeCell;
        int cBegin = columnMain + 3 + shipConsole->InnerShip()->Column() * 2 * sizeCell;
        int width{}, height{};
        if (shipConsole->Direction() == DirectionShip::Horizontal)
        {
            height = sizeCell;
            width = shipConsole->Size() * 2 * sizeCell;
        }
        else
        {
            height = shipConsole->Size() * sizeCell;
            width = 2 * sizeCell;
        }

        console->Background(Colors::Green);
        console->Rectangle(rBegin, cBegin, height, width);
    }
}


std::vector<Ship*> PlayerPlatformConsole::SetFlotilla()
{
    
    int currentShip{};

    auto builder = FieldConsole::GetBuilder(console);
    auto field = builder.SetPoint(Point(rowMain, columnMain))
        ->SetCellSize(sizeCell)
        ->GetField();

    field->Show();

    ShipConsole* ship;

    while (true)
    {
        currentShip = SelectShip();

        ship = SetShip(currentShip + 1);
        shipsConsole.push_back(ship);
        counts[currentShip]--;
        ShowShips();

        bool isZero = true;
        for (int i = 0; i < counts.size(); i++)
            isZero = isZero && (counts[i] == 0);

        if (isZero) break;
    }

    /*

    

    console->GetChar();*/

    //while (true)
    //{
    //    // ViewField();
    //    // Ship ship = SetShip();
    //    // flotilla.push_back(ship);
    //    if (flotilla.size() == 10)
    //        break;
    //}
    

    return std::vector<Ship*>();
}
