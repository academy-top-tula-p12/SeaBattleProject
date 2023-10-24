#include "Console.h"

int BorderSingleArr[]{ 0x250C, 0x252C, 0x2510, 0x251C, 0x253C, 0x2524, 0x2514, 0x2534, 0x2518, 0x2500, 0x2502 };
int BorderDoubleArr[]{ 0x2554, 0x2566, 0x2557, 0x2560, 0x256C, 0x2563, 0x255A, 0x2569, 0x255D, 0x2550, 0x2551 };

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

int Console::KeyPressed()
{
	return _kbhit();
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
	WriteGoto(row, column, BorderSingleArr[Border::TopLeft]);
	for (int c = 1; c < width; c++)
		WriteGoto(row, column + c, BorderSingleArr[Border::Horisontal]);
	WriteGoto(row, column + width, BorderSingleArr[Border::TopRight]);

	for (int r = 1; r < height; r++)
	{
		WriteGoto(row + r, column, BorderSingleArr[Border::Vertical]);
		WriteGoto(row + r, column + width, BorderSingleArr[Border::Vertical]);
	}

	WriteGoto(row + height, column, BorderSingleArr[Border::BottomLeft]);
	for (int c = 1; c < width; c++)
		WriteGoto(row + height, column + c, BorderSingleArr[Border::Horisontal]);
	WriteGoto(row + height, column + width, BorderSingleArr[Border::BottomRight]);
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



WindowConsole::WindowConsole(Console* console)
	: WindowConsole(console, 0, 0, 10, 31) {}

WindowConsole::WindowConsole(Console* console, int row, int column, int height, int width)
	: console{ console }, row {	row }, column{ column }, width{ width }, height{ height }
{
	isBorder = true;
	borderStyle = BorderStyle::Double;
	borderBack = Colors::Blue;
	borderFore = Colors::White;
	areaBack = Colors::Blue;
	areaFore = Colors::White;

	bufferSave = new CHAR_INFO[height * width];
	bufferShow = new CHAR_INFO[height * width];

	isShow = false;
}

int& WindowConsole::Row()
{
	return row;
}

int& WindowConsole::Column()
{
	return column;
}

int& WindowConsole::Width()
{
	return width;
}

int& WindowConsole::Height()
{
	return height;
}

bool& WindowConsole::IsBorder()
{
	return isBorder;
}

BorderStyle& WindowConsole::BorderStyle()
{
	return borderStyle;
}

Colors& WindowConsole::BorderBack()
{
	return borderBack;
}

Colors& WindowConsole::BorderFore()
{
	return borderFore;
}

Colors& WindowConsole::AreaBack()
{
	return areaBack;
}

Colors& WindowConsole::AreaFore()
{
	return areaFore;
}

std::string& WindowConsole::Title()
{
	return title;
}

void WindowConsole::SetColors(Colors borderBack, Colors borderFore, Colors areaBack, Colors areaFore)
{
	this->borderBack = borderBack;
	this->borderFore = borderFore;
	this->areaBack = areaBack;
	this->areaFore = areaFore;
}

void WindowConsole::WriteGoto(int row, int column, std::string message)
{
}

void WindowConsole::WriteGoto(int row, int column, char message)
{
}

void WindowConsole::Show()
{
	if (isShow) return;

	COORD bufferSize{ width, height };
	COORD bufferPosition{ 0, 0 };
	SMALL_RECT rect{ column, row, column + width, row + height };

	bool dSuccess = ReadConsoleOutput(console->Descriptor(),
										bufferSave,
										bufferSize,
										bufferPosition,
										&rect);

	WORD attributeBorder = ((WORD)borderFore + (true ? 8 : 0)) | (((WORD)borderBack + (true ? 8 : 0)) << 4);
	WORD attributeArea = ((WORD)areaFore + (true ? 8 : 0)) | (((WORD)areaBack + (true ? 8 : 0)) << 4);

	int* border;
	if (borderStyle == BorderStyle::Double)
		border = BorderDoubleArr;
	else
		border = BorderSingleArr;

	/*for (int i = 0; i < width * height; i++)
	{
		bufferShow[i].Char.UnicodeChar = ' ';
		bufferShow[i].Attributes = attribute;
	}*/

	// top line
	int index{};
	bufferShow[0].Char.UnicodeChar = border[Border::TopLeft];
	bufferShow[0].Attributes = attributeBorder;

	for (index = 1; index < width - 1; index++)
	{
		bufferShow[index].Char.UnicodeChar = border[Border::Horisontal];
		bufferShow[index].Attributes = attributeBorder;
	}

	bufferShow[index].Char.UnicodeChar = border[Border::TopRight];
	bufferShow[index++].Attributes = attributeBorder;

	// title
	if (title.length() > 0)
	{
		int tindex = (width - title.length() - 2) / 2;
		bufferShow[tindex++].Char.UnicodeChar = ' ';
		for (char s : title)
			bufferShow[tindex++].Char.UnicodeChar = s;
		bufferShow[tindex++].Char.UnicodeChar = ' ';
	}
	

	// middle lines
	for (int r = 1; r < height - 1; r++)
	{
		bufferShow[index].Char.UnicodeChar = border[Border::Vertical];
		bufferShow[index++].Attributes = attributeBorder;

		for (int c = 0; c < width - 2; c++)
		{
			bufferShow[index].Char.UnicodeChar = ' ';
			bufferShow[index++].Attributes = attributeArea;
		}

		bufferShow[index].Char.UnicodeChar = border[Border::Vertical];
		bufferShow[index++].Attributes = attributeBorder;
	}

	// bottom line
	bufferShow[index].Char.UnicodeChar = border[Border::BottomLeft];
	bufferShow[index++].Attributes = attributeBorder;

	for (int c = 1; c < width - 1; c++)
	{
		bufferShow[index].Char.UnicodeChar = border[Border::Horisontal];
		bufferShow[index++].Attributes = attributeBorder;
	}

	bufferShow[index].Char.UnicodeChar = border[Border::BottomRight];
	bufferShow[index++].Attributes = attributeBorder;


	
	dSuccess = WriteConsoleOutput(console->Descriptor(),
									bufferShow,
									bufferSize,
									bufferPosition,
									&rect);
	isShow = true;
}

void WindowConsole::Hide()
{
	if (!isShow) return;

	COORD bufferSize{ width, height };
	COORD bufferPosition{ 0, 0 };
	SMALL_RECT rect{ column, row, column + width, row + height };

	bool dSuccess = WriteConsoleOutput(console->Descriptor(),
										bufferSave,
										bufferSize,
										bufferPosition,
										&rect);
	isShow = false;
}
