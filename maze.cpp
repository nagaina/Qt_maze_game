#include "maze.hpp"

#include <iostream>
#include <cstdlib>
#include <stack>

namespace {

QPoint randomNeighbor(QVector< QVector<bool> >& visited, const QPoint& cell)
{
	// Find unvisited neighbors
	QPoint neighbors[4];
	int found = 0;
	if (cell.x() > 0) {
		QPoint n(cell.x() - 1, cell.y());
		if (visited.at(n.x()).at(n.y()) == false) {
			neighbors[found] = n;
			found++;
		}
	}
	if (cell.y() > 0) {
		QPoint n(cell.x(), cell.y() - 1);
		if (visited.at(n.x()).at(n.y()) == false) {
			neighbors[found] = n;
			found++;
		}
	}
	if (cell.y() < visited.at(cell.x()).size() - 1) {
		QPoint n(cell.x(), cell.y() + 1);
		if (visited.at(n.x()).at(n.y()) == false) {
			neighbors[found] = n;
			found++;
		}
	}
	if (cell.x() < visited.size() - 1) {
		QPoint n(cell.x() + 1, cell.y());
		if (visited.at(n.x()).at(n.y()) == false) {
			neighbors[found] = n;
			found++;
		}
	}

	// Return random neighbor
	if (found) {
		const QPoint& n = neighbors[rand() % found];
		visited[n.x()][n.y()] = true;
		return n;
	} else {
		return QPoint(-1,-1);
	}
}

}

void Maze::generate()
{
	m_visited = QVector< QVector<bool> >(columns(), QVector<bool>(rows()));

        std::stack<QPoint> cells;
        srand(time(0));
	QPoint current(rand() % m_rows, 0);
        m_start = current;
        m_cells[current.x()][current.y()].removeLeftWall();
        cells.push(current);
	m_visited[current.x()][current.y()] = true;

        while (!cells.empty()) {
                QPoint neighbour = randomNeighbor(m_visited, current);
                if (neighbour.x() != -1){
                        mergeCells(current, neighbour);
                        cells.push(neighbour);
                        current = neighbour;
                } else {
                        current = cells.top();
                        cells.pop();
                }
        }
	m_visited.clear();
}

void Maze::generate(int columns, int rows)
{
	m_columns = columns;
	m_rows = rows;
	m_cells = QVector< QVector<Cell> >(m_columns, QVector<Cell>(m_rows));
	generate();
}

void Maze::mergeCells(const QPoint& cell1, const QPoint& cell2)
{
	if (cell1.y() == cell2.y()) {
		if (cell2.x() >= cell1.x()) {
			m_cells[cell1.x()][cell1.y()].removeBottomWall();
			m_cells[cell2.x()][cell2.y()].removeTopWall();
		} else if (cell2.x() < cell1.x()) {
			m_cells[cell1.x()][cell1.y()].removeTopWall();
			m_cells[cell2.x()][cell2.y()].removeBottomWall();
		}
	} else if (cell1.x() == cell2.x()) {
		if (cell2.y() > cell1.y()) {
			m_cells[cell1.x()][cell1.y()].removeRightWall();
			m_cells[cell2.x()][cell2.y()].removeLeftWall();
		} else if (cell2.y() < cell1.y()) {
			m_cells[cell1.x()][cell1.y()].removeLeftWall();
			m_cells[cell2.x()][cell2.y()].removeRightWall();
		}
                if (cell2.y() == m_columns -1) {
                        m_cells[cell2.x()][cell2.y()].removeRightWall();
                }
	}
}

