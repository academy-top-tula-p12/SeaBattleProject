#include "Field.h"

Field::Field()
{
	for (int r = 0; r < size; r++)
	{
		std::vector<Cell> line;
		for (int c = 0; c < size; c++)
			line.push_back(Cell(r, c));
		cells.push_back(line);
	}
}

void Field::SetCellType(Point point, CellType type)
{
	cells[point.row][point.column].Type() = type;
}

void Field::SetCellShot(Point point)
{
	cells[point.row][point.column].IsShot() = true;
}

Cell Field::GetCell(int row, int column)
{
	return cells[row][column];
}

Cell Field::GetCell(Point point)
{
	return cells[point.row][point.column];
}

void Field::SetShips(std::vector<Ship> flotilla)
{
	for (Ship ship : flotilla)
	{
		int row = ship.Row();
		int column = ship.Column();
		for (int s = 0; s < ship.Size(); s++)
		{
			SetCellType(Point(row, column), CellType::Deck);
			(ship.Direction() == DirectionShip::Horizontal) ? column++ : row++;
		}
	}
}

HitType Field::CheckShot(Point point)
{
	if (cells[point.row][point.column].IsShot())
		return HitType::Beside;
	if (cells[point.row][point.column].Type() == CellType::Water)
		return HitType::Beside;
	if (cells[point.row][point.column].Type() == CellType::Deck)
		return HitType::Reach;
}






