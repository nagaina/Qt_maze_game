#ifndef _maze_hpp_
#define _maze_hpp_

#include "cell.hpp"

#include <QList>
#include <QPoint>
#include <QVector>

class Maze
{
public:
	virtual ~Maze()
		{ }

	int columns() const
		{ return m_columns; }
	int rows() const
		{ return m_rows; }
	const Cell& cell(int column, int row) const
		{ return m_cells.at(column).at(row); }
	Cell& cellMutable(int column, int row)
		{ return m_cells[column][row]; }

	void generate(int columns, int rows);
	//bool load();
	//void save() const;

        QPoint start_point() const {return m_start;}
protected:
	void mergeCells(const QPoint& cell1, const QPoint& cell2);

private:
	void generate();

	int m_columns;
	int m_rows;
        QVector< QVector<bool> > m_visited;
        QVector< QVector<Cell> > m_cells;
        QPoint m_start;
};

#endif
