#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

const char WATER = 176;
const char DESK = 219 ;



enum class KeyCode
{
	ArrowUp = 72,
	ArrowDown = 80,
	ArrowLeft = 75,
	ArrowRight = 77,

	Enter = 13,
	Space = 32,
	Esc = 27
};

enum class Colors
{
	Gray,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White
};

enum Border : int
{
	TopLeft,
	TopCenter,
	TopRight,
	MiddleLeft,
	MiddleCenter,
	MiddleRight,
	BottomLeft,
	BottomCenter,
	BottomRight,
	Horisontal,
	Vertical
};



class Console
{
	HANDLE descriptor;
	COORD coordinate{};
	CONSOLE_SCREEN_BUFFER_INFO info{};
public:
	Console();

	HANDLE& Descriptor();

	void Clear();
	int GetChar();

	void CursorGoto(int row, int column);
	void Write(std::string message);
	void Write(char symbol);
	void WriteGoto(int row, int column, std::string message);
	void WriteGoto(int row, int column, char symbol);

	void Foreground(Colors color, bool brightness = false);
	void Background(Colors color, bool brightness = false);
	
	void Rectangle(int row, int column, int height, int width, char pattern = 32);
	void BorderSimple(int row, int column, int height, int width);
	void BorderDouble(int row, int column, int height, int width);
};

