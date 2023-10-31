#pragma once
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>

enum KeyCode : int
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
protected:
	Console* console;

	int row, column;
	int width;
	int height;

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
	void SetSize(int height, int width);

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
	void WriteWidthGoto(int row, int column, int width, std::string message);
	void WriteWidthGoto(int row, int column, int width, char message);
	

	virtual void Show();
	virtual void Hide();
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

	void WriteWidthGoto(int row, int column, int width, std::string message);
	void WriteWidthGoto(int row, int column, int width, char message);

	void Foreground(Colors color, bool brightness = false);
	void Background(Colors color, bool brightness = false);
	
	void Rectangle(int row, int column, int height, int width, char pattern = 32);
	void BorderSimple(int row, int column, int height, int width);
	void BorderDouble(int row, int column, int height, int width);
};

