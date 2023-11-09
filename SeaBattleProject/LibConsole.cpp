#include "LibConsole.h"

int WATER = 0x2592;
int DESK = 0x2588;

FieldConsole::FieldConsole(Console* console)
    : WindowConsole(console)
{
    //areaBegin.row = 1;
    //areaBegin.column = 2;

    ////areaBack = Colors::Yellow;


    //this->Row() = row;
    //this->Column() = column;
    //this->SetSize(sizeField * sizeCell + areaBegin.row + 3,
    //    sizeField * sizeCell * 2 + areaBegin.column * 2 + 2);
}

int& FieldConsole::SizeCell()
{
    return sizeCell;
}

FieldConsoleBuilder FieldConsole::GetBuilder(Console* console)
{
    return FieldConsoleBuilder(new FieldConsole(console));
}

void FieldConsole::Show()
{
    WindowConsole::Show();

    Point offsetArea(AreaBegin.row, AreaBegin.column);
    Point offsetField(offsetArea.row + 1, offsetArea.column + 1);

    int hField = SizeField * sizeCell;
    int wField = SizeField * sizeCell * 2;

    // show coordinates
    for (int i = 0; i < SizeField; i++)
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



FieldConsoleBuilder::FieldConsoleBuilder(FieldConsole* field)
    : field{ field } 
{
    console = field->console;
}

void FieldConsoleBuilder::Reset()
{
    field = new FieldConsole(console);
}

FieldConsoleBuilder* FieldConsoleBuilder::SetPoint(Point point)
{
    field->Row() = point.row;
    field->Column() = point.column;

    return this;
}

FieldConsoleBuilder* FieldConsoleBuilder::SetCellSize(int size)
{
    field->SizeCell() = size;

    field->SetSize(field->SizeField * field->SizeCell() + field->AreaBegin.row + 3,
        field->SizeField * size * 2 + field->AreaBegin.column * 2 + 2);
    return this;
}

FieldConsoleBuilder* FieldConsoleBuilder::SetColorBack(Colors color)
{
    field->AreaBack() = color;
    field->BorderBack() = color;
    return this;
}

FieldConsole* FieldConsoleBuilder::GetField()
{
    return field;
}

ShipConsole::ShipConsole(Console* console, int size)
    : WindowConsole(console)
{
    ship = new Ship(Point(0, 0), size, DirectionShip::Horizontal);

    sizeCell = 1;
    areaBegin = { 1, 1 };
    
    isBorder = false;
    areaBack = Colors::Blue;
    areaFore = Colors::Blue;

    column = ship->Column() + areaBegin.column;
    row = ship->Row() + areaBegin.row;

    width = size;
    height = 1;

    bufferSave = new CHAR_INFO[height * width * sizeCell * 2 * sizeCell];
    bufferShow = new CHAR_INFO[height * width * sizeCell * 2 * sizeCell];
}

ShipConsole* ShipConsole::SetSizeCell(int size)
{
    sizeCell = size;

    delete[] bufferSave;
    delete[] bufferShow;

    bufferSave = new CHAR_INFO[height * width * sizeCell * 2 * sizeCell];
    bufferShow = new CHAR_INFO[height * width * sizeCell * 2 * sizeCell];

    return this;
}

ShipConsole* ShipConsole::SetAreaBegin(Point point)
{
    areaBegin = point;
    areaBegin.row += 2;
    areaBegin.column += 3;

    column = ship->Column() + areaBegin.column;
    row = ship->Row() + areaBegin.row;

    return this;
}

DirectionShip& ShipConsole::Direction()
{
    return ship->Direction();
}

Ship*& ShipConsole::InnerShip()
{
    return ship;
}

int ShipConsole::Size()
{
    return ship->Size();
}

void ShipConsole::Show()
{
    if (isShow) return;

    COORD bufferSize;
    COORD bufferPosition{ 0, 0 };
    SMALL_RECT rect;

    if (ship->Direction() == DirectionShip::Horizontal)
    {
        bufferSize.X = width * sizeCell * 2;
        bufferSize.Y = height * sizeCell;

        rect.Top = areaBegin.row + InnerShip()->Row() * sizeCell;
        rect.Left = areaBegin.column + InnerShip()->Column() * 2 * sizeCell;
        rect.Bottom = (areaBegin.row + InnerShip()->Row() + height) * sizeCell;
        rect.Right = (areaBegin.column + InnerShip()->Column() + width) * sizeCell * 2;

        /*rect.Top = row * sizeCell;
        rect.Left = column * sizeCell * 2;
        rect.Bottom = (row * sizeCell + height) * sizeCell;
        rect.Right = (column + width) * sizeCell * 2;*/
    }
    else
    {
        bufferSize.X = height * sizeCell * 2;
        bufferSize.Y = width * sizeCell;

        rect.Top = areaBegin.row + InnerShip()->Row() * sizeCell;
        rect.Left = areaBegin.column + InnerShip()->Column() * 2 * sizeCell;
        rect.Bottom = (areaBegin.row + InnerShip()->Row() + width) * sizeCell;
        rect.Right = (areaBegin.column + InnerShip()->Column() + height) * sizeCell * 2;
    }

    bool dSuccess = ReadConsoleOutput(console->Descriptor(),
                        bufferSave,
                        bufferSize,
                        bufferPosition,
                        &rect);

    WORD attributeArea = ((WORD)areaFore + (false ? 8 : 0)) | (((WORD)areaBack + (false ? 8 : 0)) << 4);

    for (int i = 0; i < ship->Size() * sizeCell * 2 * sizeCell; i++)
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

    if (ship->Direction() == DirectionShip::Horizontal)
    {
        bufferSize.X = width * sizeCell * 2;
        bufferSize.Y = height * sizeCell;

        rect.Top = areaBegin.row + InnerShip()->Row() * sizeCell;
        rect.Left = areaBegin.column + InnerShip()->Column() * 2 * sizeCell;
        rect.Bottom = (areaBegin.row + InnerShip()->Row() + height) * sizeCell;
        rect.Right = (areaBegin.column + InnerShip()->Column() + width) * sizeCell * 2;
    }
    else
    {
        bufferSize.X = height * sizeCell * 2;
        bufferSize.Y = width * sizeCell;

        rect.Top = areaBegin.row + InnerShip()->Row() * sizeCell;
        rect.Left = areaBegin.column + InnerShip()->Column() * 2 * sizeCell;
        rect.Bottom = (areaBegin.row + InnerShip()->Row() + width) * sizeCell;
        rect.Right = (areaBegin.column + InnerShip()->Column() + height) * sizeCell * 2;
    }

    bool dSuccess = WriteConsoleOutput(console->Descriptor(),
                        bufferSave,
                        bufferSize,
                        bufferPosition,
                        &rect);
    isShow = false;
}


