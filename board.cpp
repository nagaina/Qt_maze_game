#include "board.hpp"
#include "maze.hpp"
#include "player.hpp"
#include "level.hpp"

#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QPushButton>
#include <QStatusBar>
#include <QSettings>
#include <QGraphicsPixmapItem>

#include <iostream>

Board::Board(QWidget* parent)
        : QWidget(parent)
        , m_maze(0)
        , level_count(1)
{
        m_player = new Player();
        m_level = new Level1();
        connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(repaint()));
        newGame();
        loadSettings();
}

Board::~Board()
{
        delete m_maze;
        delete m_player;
}

void Board::newGame()
{
        delete m_level;
        m_level = new Level1();
        level_count = 1;
        m_player->m_player_angle = 90;
        generate();
        m_player->m_player.ry() = m_start.x() * m_level->get_delta_column() + 5;
        update();
}

void Board::generate()
{
        int columns = m_level->get_column();
        int rows = columns;

        // Create new maze
        delete m_maze;
        m_maze = new Maze;
        m_maze->generate(columns, rows);
        m_start = m_maze->start_point();
}

void Board::paintEvent(QPaintEvent* )
{
        renderMaze();
}

void Board::renderMaze()
{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 2));
        int r = 5, c = 5;
        for (int i = 0; i < m_level->get_column(); ++i ) {
              for (int j = 0; j < m_level->get_row(); ++j) {
                        const Cell& cell = m_maze->cell(i,j);
                        if (cell.topWall()) {
                                painter.drawLine(r,c, r + m_level->get_delta_row(), c);
                        }
                        if (cell.leftWall()) {
                                painter.drawLine(r,c,r, c + m_level->get_delta_column());
                        }
                        if (j == m_level->get_row() -1 && cell.rightWall())
                        {
                                painter.drawLine(r + m_level->get_delta_row(),c,r + m_level->get_delta_row() , c + m_level->get_delta_column());
                        }
                        if (i == m_level->get_column() - 1) {
                               painter.drawLine(r,c + m_level->get_delta_column(),r+m_level->get_delta_row(),c + m_level->get_delta_column());
                        }
                        r+=m_level->get_delta_row();
              }
              r = 5 ;//m_level->get_delta_row();
              c += m_level->get_delta_column();
        }
        QRect gl_rect (5,5,970,c-5);
        painter.drawRect(gl_rect);
        QImage image("mouse.png");
        m_player->setRect(m_player->m_player_angle);
        QImage im("cheese .png");
        painter.drawImage(910, 400, im);

        QTransform rot;
        rot.rotate(m_player->m_player_angle);
        image = image.transformed(rot);
        painter.drawImage(m_player->m_player,image);

}

/*
void Board::keyPressEvent(QKeyEvent* key)
{
        if (key->key() == Qt::Key_Back) {
                key->ignore();
        }
        QPixmap a = QPixmap::grabWidget(this);
        QImage img = a.toImage();
        QRgb color =img.pixel(m_player->m_player.x(), m_player->m_player.y());
        img.pixel(950, 400);
        QColor c;
        c.setRgb(color);
        unsigned int keypress = key->key();
        QRect rect(910,400, 50, 50);
        if (keypress == m_left) {
                m_player->m_player_angle = 270;
                color = img.pixel(m_player->m_player.x()-1, m_player->m_player.y() + 25-1);
                c.setRgb(color);
                if (c.black() != 255) {
                        int i = 0;
                        while (i < 10 && c.black() != 255) {
                                --m_player->m_player.rx();
                                color = img.pixel(m_player->m_player.x()-1, m_player->m_player.y() + 25-1);
                                c.setRgb(color);
                                ++i;
                        }
                }
                if (rect.contains(m_player->m_player.x() + 46, m_player->m_player.y() + 26)) {
                        go_to_next_level();
                }
        } else if (keypress == m_right) {
                m_player->m_player_angle = 90;
                color = img.pixel(m_player->m_player.x()+45 +1, m_player->m_player.y()+ 25 +1);
                c.setRgb(color);
                if (c.black() != 255) {
                        int i = 0;
                        while (i < 10 && c.black() != 255) {
                                ++m_player->m_player.rx();
                                color = img.pixel(m_player->m_player.x()+45 +1, m_player->m_player.y()+ 25 +1);
                                c.setRgb(color);
                                ++i;
                        }
                }
                if (rect.contains(m_player->m_player.x() + 46, m_player->m_player.y() + 26)) {
                        go_to_next_level();
                }
        } else if (keypress == m_up) {
                m_player->m_player_angle = 360;
                color = img.pixel(m_player->m_player.x() +25 -1, m_player->m_player.y()-1);
                c.setRgb(color);
                if (c.black() != 255) {
                        int i = 0;
                        while (i < 10 && c.black() != 255) {
                                --m_player->m_player.ry();
                                color = img.pixel(m_player->m_player.x() +25 -1, m_player->m_player.y()-1);
                                c.setRgb(color);
                                ++i;
                        }
                }
                if (rect.contains(m_player->m_player.x() + 24, m_player->m_player.y() + -1)) {
                        go_to_next_level();
                }
        } else if (keypress == m_down) {
                m_player->m_player_angle = 180;
                color = img.pixel(m_player->m_player.x()+ 25 +1, m_player->m_player.y()+45+1);
                c.setRgb(color);
                if (c.black() != 255) {
                        int i = 0;
                        while (i < 10 && c.black() != 255) {
                                ++m_player->m_player.ry();
                                color = img.pixel(m_player->m_player.x()+ 25 +1, m_player->m_player.y()+45+1);
                                c.setRgb(color);
                                ++i;
                        }
                }
                if (rect.contains(m_player->m_player.x() + 26, m_player->m_player.y() + 46)) {
                        go_to_next_level();
                }
        } else {
                return;
        }

        update();
}
*/

bool Board::check_in_bounding_box()
{
        QPixmap a = QPixmap::grabWidget(this);
        QImage img = a.toImage();
        QRgb color = img.pixel(m_player->m_player.x(), m_player->m_player.y());
        QColor c;
        c.setRgb(color);
        int i = m_player->bounding_rect.x() / m_level->get_delta_column();
        int j = m_player->bounding_rect.y() / m_level->get_delta_row();
        i = i * m_level->get_delta_column() + 5;
        j = j * m_level->get_delta_row() + 5;
        for (int i_ = i; i_ < i + m_level->get_delta_column(); ++i_) {
                if (m_player->bounding_rect.contains(i_, j)) {
                        color = img.pixel(i_, j);
                        c.setRgb(color);
                        if (c.black() == 255) {
                                return true;
                        }
                }
        }
        i = i + m_level->get_delta_column();
        for (int j_= j; j_ < j + m_level->get_delta_row(); ++j_) {
                if (m_player->bounding_rect.contains(i, j_)) {
                        color = img.pixel(i, j_);
                        c.setRgb(color);
                        if (c.black() == 255) {
                                return true;
                        }
                }
        }
        i -= m_level->get_delta_column();
        for (int j_= j; j_ < j + m_level->get_delta_row(); ++j_) {
                if (m_player->bounding_rect.contains(i, j_)) {
                        color = img.pixel(i, j_);
                        c.setRgb(color);
                        if (c.black() == 255) {
                                return true;
                        }
                }
        }
        j = j + m_level->get_delta_row();
        for (int i_ = i; i_ < i + m_level->get_delta_column(); ++i_) {
                if (m_player->bounding_rect.contains(i_, j)) {
                        color = img.pixel(i_, j);
                        c.setRgb(color);
                        if (c.black() == 255) {
                                return true;
                        }
                }
        }
        return false;
}

void Board::keyPressEvent(QKeyEvent* key)
{
        if (key->key() ==  Qt::Key_Back) {
                key->ignore();
        }
        QRect rect(910,400, 50, 50);

        unsigned int keypress = key->key();
        if (keypress == m_left) {
                m_player->m_player_angle = 270;
                int i = 0;
                while (i < 7) {
                        if (check_in_bounding_box()) {
                        break;
                        }
                        ++i;
                        --m_player->m_player.rx();
                }
                if (rect.contains(m_player->m_player.x() + 46, m_player->m_player.y() + 26)) {
                        go_to_next_level();
                }
                m_player->setRect(270);
                if (i != 7) {
                        return;
                }
                m_player->m_player_angle = 270;
        } else if (keypress == m_right) {
                m_player->m_player_angle = 90;
                int i = 0;
                while (i < 7) {
                        if (check_in_bounding_box()) {
                        break;
                        }
                        ++i;
                        ++m_player->m_player.rx();
                }
                if (rect.contains(m_player->m_player.x() + 46, m_player->m_player.y() + 26)) {
                        go_to_next_level();
                }
                m_player->setRect(90);
                if (i != 7) {
                        return;
                }
                m_player->m_player_angle = 90;
        } else if (keypress == m_up) {
                m_player->m_player_angle = 360;
                int i = 0;
                while (i < 7) {
                        if (check_in_bounding_box()) {
                        break;
                        }
                        ++i;
                        --m_player->m_player.ry();
                }
                if (rect.contains(m_player->m_player.x() + 46, m_player->m_player.y() + 26)) {
                        go_to_next_level();
                }
                m_player->setRect(360);
                if (i != 7) {
                        return;
                }
                m_player->m_player_angle = 360;
        } else if (keypress == m_down) {
                m_player->m_player_angle = 180;
                int i = 0;
                while (i < 7) {
                        if (check_in_bounding_box()) {
                        break;
                        }
                        ++i;
                        ++m_player->m_player.ry();
                }
                if (rect.contains(m_player->m_player.x() + 46, m_player->m_player.y() + 26)) {
                        go_to_next_level();
                }
                m_player->setRect(180);
                if (i != 7) {
                        return;
                }
                m_player->m_player_angle = 180;
        } else {
                return;
        }
        update();
}

void Board::loadSettings()
{
        QSettings s;
        m_up = s.value("Up", Qt::Key_Up).toUInt();
        m_down = s.value("Up", Qt::Key_Down).toUInt();
        m_left = s.value("Up", Qt::Key_Left).toUInt();
        m_right = s.value("Up", Qt::Key_Right).toUInt();

        update();
}

void Board::go_to_next_level()
{
        m_player->m_player.rx() = 0;
        m_player->m_player.ry() = 0;
        m_level->changeState(this);

        if (level_count == 3) {
                emit Win();
        } else {
                ++level_count;
                emit Level_changed();
        }
}

void Board::continueGame()
{
        m_player->m_player_angle = 90;
        generate();
        m_player->m_player.ry() = m_start.x() * m_level->get_delta_column() + 5;
        update();
}

void Board::reset()
{
        m_player->m_player_angle = 180;
        QPoint t(0, 10);
        m_start = t;
        m_player->m_player = t;
        update();
}

void Board::changeState(Level_interface* i)
{
        delete m_level;
        m_level = i;
}
