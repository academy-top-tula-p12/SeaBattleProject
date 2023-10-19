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

class Console
{
	HANDLE descriptor;
	COORD coordinate;
	CONSOLE_SCREEN_BUFFER_INFO info;
public:
	Console();

	HANDLE& Descriptor();

	void Clear();
	void CursorGoto(int row, int column);
	void Write(std::string message);
	void Write(char symbol);
	void WriteGoto(int row, int column, std::string message);
	void WriteGoto(int row, int column, char symbol);

	void Foreground(Colors color, bool brightness = false);
	void Background(Colors color, bool brightness = false);
	
	void Rectangle(int row, int column, int height, int width, char pattern = 32);
};

