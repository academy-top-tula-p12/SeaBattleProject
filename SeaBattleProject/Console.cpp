#include "Console.h"

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




