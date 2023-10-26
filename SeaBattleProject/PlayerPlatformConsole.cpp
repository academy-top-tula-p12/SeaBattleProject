#include <string>
#include "PlayerPlatformConsole.h"

int WATER = 0x2592;
int DESK = 0x2588;

std::vector<Ship> PlayerPlatformConsole::SetFlotilla()
{
    while (true)
    {
        // ViewField();
        // Ship ship = SetShip();
        // flotilla.push_back(ship);
        if (flotilla.size() == 10)
            break;
    }
    

    return std::vector<Ship>();
}

//FieldConsole::FieldConsole(Console* console, int row, int column, int size)
//    : WindowConsole(console, row, column, size, size), sizeField{ size }
//{
//    sizeCell = 2;
//    this->Height() = size * sizeCell + 2;
//    this->Width() = size * sizeCell * 2 + 2;
//}

FieldConsole::FieldConsole(Console* console, int row, int column, int size)
    : WindowConsole(console)
{
    sizeCell = 2;
    sizeField = 10;
    areaBegin.row = 1;
    areaBegin.column = 2;


    this->Row() = row;
    this->Column() = column;
    this->SetSize(size * sizeCell + areaBegin.row + 3, 
                  size * sizeCell * 2 + areaBegin.column * 2 + 2);
}

void FieldConsole::Show()
{
    WindowConsole::Show();

    Point offsetArea(areaBegin.row, areaBegin.column);
    Point offsetField(offsetArea.row + 1, offsetArea.column + 1);

    int hField = sizeField * sizeCell;
    int wField = sizeField * sizeCell * 2;

    // show coordinates
    for (int i = 0; i < sizeField; i++)
    {
        WriteGoto(offsetArea.row, 
                  offsetArea.column + sizeCell + i * sizeCell * 2, 
                  65 + i);
        WriteWidthGoto(offsetArea.column + (i) * sizeCell, 
                  offsetArea.column - 1,
                  2,
                  std::to_string(i + 1));
    }

    // field water
    int fieldArea = wField * hField;
    CHAR_INFO* bufferField = new CHAR_INFO[fieldArea];
    WORD attributeArea = ((WORD)areaFore + (true ? 8 : 0)) | (((WORD)areaBack + (true ? 8 : 0)) << 4);

    COORD bufferSize{ wField, hField };
    COORD bufferPosition{ 0, 0 };
    SMALL_RECT rect{ offsetField.column + column, 
                     offsetField.row + row, 
                     offsetField.column + column + wField, 
                     offsetField.row + row + hField };

    for (int i = 0; i < fieldArea; i++)
    {
        bufferField[i].Char.UnicodeChar = WATER;
        bufferField[i].Attributes = attributeArea;
    }

    bool dSuccess = WriteConsoleOutput(console->Descriptor(),
        bufferField,
        bufferSize,
        bufferPosition,
        &rect);
        
}
