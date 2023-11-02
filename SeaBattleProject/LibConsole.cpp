#include "LibConsole.h"

int WATER = 0x2592;
int DESK = 0x2588;

FieldConsole::FieldConsole(Console* console, int row, int column)
    : WindowConsole(console)
{
    sizeCell = 2;
    sizeField = 10;
    areaBegin.row = 1;
    areaBegin.column = 2;

    //areaBack = Colors::Yellow;


    this->Row() = row;
    this->Column() = column;
    this->SetSize(sizeField * sizeCell + areaBegin.row + 3,
        sizeField * sizeCell * 2 + areaBegin.column * 2 + 2);
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
        WriteWidthGoto(offsetArea.row,
            offsetArea.column + sizeCell + i * sizeCell * 2 - (sizeCell - 1),
            sizeCell * 2,
            (char)(65 + i));

        WriteWidthGoto(offsetArea.column + (i + 1)*sizeCell - 1,
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

ShipConsole::ShipConsole(Console* console, 
                         Point point, 
                         int size, 
                         DirectionShip direction)
    : WindowConsole(console),
    point{ point },
    size{ size },
    direction{ direction }
{
    isBorder = false;
    areaBack = Colors::Blue;
    areaFore = Colors::Blue;
    width = size;
    height = 1;

    sizeCell = 2;

    areaBegin.row = 1;
    areaBegin.column = 1;

    column = point.column;
    row = point.row;
    bufferSave = new CHAR_INFO[height * width * sizeCell * 2 * sizeCell];
    bufferShow = new CHAR_INFO[height * width * sizeCell * 2 * sizeCell];
}
DirectionShip& ShipConsole::Direction()
{
    return direction;
}

int ShipConsole::Size()
{
    return size;
}

void ShipConsole::Show()
{
    if (isShow) return;

    COORD bufferSize;
    COORD bufferPosition{ 0, 0 };
    SMALL_RECT rect;

    if (direction == DirectionShip::Horizontal)
    {
        bufferSize.X = width * sizeCell * 2;
        bufferSize.Y = height * sizeCell;

        rect.Top = row * sizeCell;
        rect.Left = column * sizeCell * 2;
        rect.Bottom = (row * sizeCell + height) * sizeCell;
        rect.Right = (column + width) * sizeCell * 2;
    }
    else
    {
        bufferSize.X = height * sizeCell * 2;
        bufferSize.Y = width * sizeCell;

        rect.Top = row * sizeCell;
        rect.Left = column * sizeCell * 2;
        rect.Bottom = (row * sizeCell + width) * sizeCell;
        rect.Right = (column + height) * sizeCell * 2;
    }

    bool dSuccess = ReadConsoleOutput(console->Descriptor(),
                        bufferSave,
                        bufferSize,
                        bufferPosition,
                        &rect);

    WORD attributeArea = ((WORD)areaFore + (false ? 8 : 0)) | (((WORD)areaBack + (false ? 8 : 0)) << 4);

    for (int i = 0; i < size * sizeCell * 2 * sizeCell; i++)
    {
        bufferShow[i].Char.UnicodeChar = DESK;
        bufferShow[i].Attributes = attributeArea;
    }

    dSuccess = WriteConsoleOutput(console->Descriptor(),
        bufferShow,
        bufferSize,
        bufferPosition,
        &rect);
    isShow = true;
}

void ShipConsole::Hide()
{
    if (!isShow) return;

    COORD bufferSize;
    COORD bufferPosition{ 0, 0 };
    SMALL_RECT rect;

    if (direction == DirectionShip::Horizontal)
    {
        bufferSize.X = width * sizeCell * 2;
        bufferSize.Y = height * sizeCell;

        rect.Top = row * sizeCell;
        rect.Left = column * sizeCell * 2;
        rect.Bottom = (row * sizeCell + height) * sizeCell;
        rect.Right = (column + width) * sizeCell * 2;
    }
    else
    {
        bufferSize.X = height * sizeCell * 2;
        bufferSize.Y = width * sizeCell;

        rect.Top = row * sizeCell;
        rect.Left = column * sizeCell * 2;
        rect.Bottom = (row * sizeCell + width) * sizeCell;
        rect.Right = (column + height) * sizeCell * 2;
    }

    bool dSuccess = WriteConsoleOutput(console->Descriptor(),
                        bufferSave,
                        bufferSize,
                        bufferPosition,
                        &rect);
    isShow = false;
}


