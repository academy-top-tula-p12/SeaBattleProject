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

enum BorderStyle
{
	Single,
	Double
};

class Console;

class WindowConsole
{
	Console* console;

	int row, column;
	int width, height;

	bool isBorder;
	BorderStyle borderStyle;
	Colors borderBack, 
		borderFore, 
		areaBack, 
		areaFore;

	std::string title;

	bool isShow;

	CHAR_INFO* bufferSave;
	CHAR_INFO* bufferShow;
public:
	WindowConsole(Console* console);
	WindowConsole(Console* console, int row, int column, int height, int width);
	
	int& Row();
	int& Column();
	int& Width();
	int& Height();

	bool& IsBorder();
	BorderStyle& BorderStyle();

	Colors& BorderBack();
	Colors& BorderFore();
	Colors& AreaBack();
	Colors& AreaFore();

	std::string& Title();

	void SetColors(Colors borderBack, Colors borderFore, Colors	areaBack, Colors areaFore);

	void WriteGoto(int row, int column, std::string message);
	void WriteGoto(int row, int column, char message);

	void Show();
	void Hide();
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
	int KeyPressed();

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

