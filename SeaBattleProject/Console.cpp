#include "Console.h"

int BorderSimpleArr[]{ 218, 194, 191, 195, 197, 180, 192, 193, 217, 196, 179 };
int BorderDoubleArr[]{ 201, 203, 187, 204, 206, 185, 200, 202, 188, 205, 186 };

Console::Console()
{
	descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
}

HANDLE& Console::Descriptor()
{
	return descriptor;
}

void Console::Clear()
{
	std::system("cls");
}

int Console::GetChar()
{
	return _getch();
}

void Console::CursorGoto(int row, int column)
{
	coordinate.X = column;
	coordinate.Y = row;
	SetConsoleCursorPosition(descriptor, coordinate);
}

void Console::Write(std::string message)
{
	std::cout << message;
}

void Console::Write(char symbol)
{
	std::cout << symbol;
}

void Console::WriteGoto(int row, int column, std::string message)
{
	CursorGoto(row, column);
	Write(message);
}

void Console::WriteGoto(int row, int column, char symbol)
{
	CursorGoto(row, column);
	Write(symbol);
}

void Console::Foreground(Colors color, bool brightness)
{
	GetConsoleScreenBufferInfo(descriptor, &info);
	byte colorBack = info.wAttributes & (0b1111 << 4);
	byte colorFore = (byte)color + (brightness ? 8 : 0);
	SetConsoleTextAttribute(descriptor, colorBack | colorFore);
}

void Console::Background(Colors color, bool brightness)
{
	GetConsoleScreenBufferInfo(descriptor, &info);
	byte colorFore = info.wAttributes & 0b1111;
	byte colorBack = ((byte)color + (brightness ? 8 : 0)) << 4;
	SetConsoleTextAttribute(descriptor, colorBack | colorFore);
}

void Console::Rectangle(int row, int column, int height, int width, char pattern)
{
	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++)
			WriteGoto(row + r, column + c, pattern);
}

void Console::BorderSimple(int row, int column, int height, int width)
{
	width--;
	height--;
	WriteGoto(row, column, BorderSimpleArr[Border::TopLeft]);
	for (int c = 1; c < width; c++)
		WriteGoto(row, column + c, BorderSimpleArr[Border::Horisontal]);
	WriteGoto(row, column + width, BorderSimpleArr[Border::TopRight]);

	for (int r = 1; r < height; r++)
	{
		WriteGoto(row + r, column, BorderSimpleArr[Border::Vertical]);
		WriteGoto(row + r, column + width, BorderSimpleArr[Border::Vertical]);
	}

	WriteGoto(row + height, column, BorderSimpleArr[Border::BottomLeft]);
	for (int c = 1; c < width; c++)
		WriteGoto(row + height, column + c, BorderSimpleArr[Border::Horisontal]);
	WriteGoto(row + height, column + width, BorderSimpleArr[Border::BottomRight]);
}

void Console::BorderDouble(int row, int column, int height, int width)
{
	width--;
	height--;
	WriteGoto(row, column, BorderDoubleArr[Border::TopLeft]);
	for (int c = 1; c < width; c++)
		WriteGoto(row, column + c, BorderDoubleArr[Border::Horisontal]);
	WriteGoto(row, column + width, BorderDoubleArr[Border::TopRight]);

	for (int r = 1; r < height; r++)
	{
		WriteGoto(row + r, column, BorderDoubleArr[Border::Vertical]);
		WriteGoto(row + r, column + width, BorderDoubleArr[Border::Vertical]);
	}

	WriteGoto(row + height, column, BorderDoubleArr[Border::BottomLeft]);
	for (int c = 1; c < width; c++)
		WriteGoto(row + height, column + c, BorderDoubleArr[Border::Horisontal]);
	WriteGoto(row + height, column + width, BorderDoubleArr[Border::BottomRight]);
}




