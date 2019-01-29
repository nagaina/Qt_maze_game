#include "game.hpp"
#include <iostream>

#include <QPalette>
#include <QPainter>

#include <QStyleOption>

GameWindow::GameWindow(QWidget* p)
        : QWidget(p)
        , m_continue(false)
{
        m_layout = new QHBoxLayout;
        m_board = new Board(this);
        m_layout->addWidget(m_board);
        m_board->hide();
        m_menu = new Menu(this);
        m_menu->setAutoFillBackground(true);
        m_menu->setStyleSheet("background-color: #2cbaa1; border: 1px solid black; border-radius: 5px;");
        m_win = new WinWindow(this);
        m_win->setAutoFillBackground(true);
        m_win->setStyleSheet("background-color: #2cbaa1; border: 1px solid black; border-radius: 5px;");
        m_win->hide();
        m_score = new Score(this);
        m_layout->addWidget(m_score);
        m_layout->addWidget(m_menu);
        m_layout->addWidget(m_win);
        m_players = new Players(this);
        m_players->hide();
        m_layout->addWidget(m_players);
        setLayout(m_layout);
        make_connections();
}

GameWindow::~GameWindow()
{
        disconnect(m_menu, SIGNAL(new_game()), this, SLOT(NewGame()));
        disconnect(m_menu, SIGNAL(quit_game()), this, SIGNAL(Quit()));
        disconnect(m_menu, SIGNAL(continue_game()), this, SLOT(Continue()));
        disconnect(m_board, SIGNAL(Level_changed()), this, SLOT(level_changed()));
        disconnect(m_board, SIGNAL(Win()), this, SLOT(win()));
        disconnect(m_win, SIGNAL(new_game()), this, SLOT(NewGame()));
        disconnect(m_win, SIGNAL(quit_game()), this, SIGNAL(Quit()));
}

void GameWindow::make_connections()
{
        connect(m_menu, SIGNAL(new_game()), this, SLOT(NewGame()));
        connect(m_menu, SIGNAL(quit_game()), this, SIGNAL(Quit()));
        connect(m_menu, SIGNAL(continue_game()), this, SLOT(Continue()));
        connect(m_board, SIGNAL(Level_changed()), this, SLOT(level_changed()));
        connect(m_board, SIGNAL(Win()), this, SLOT(win()));
        connect(m_win, SIGNAL(new_game()), this, SLOT(NewGame()));
        connect(m_win, SIGNAL(quit_game()), this, SIGNAL(Quit()));
}

void GameWindow::NewGame()
{
        m_continue = false;
        m_menu->hide();
        m_win->hide();
        m_board->show();
        m_board->newGame();
        m_board->setFocus();
}

void GameWindow::level_changed()
{
        m_continue = true;
        m_board->hide();
        m_win->hide();
        m_menu->show();
        m_menu->setFocus();
}

void GameWindow::win()
{
        m_continue = false;
        m_board->hide();
        m_win->show();
        m_win->setFocus();
}

void GameWindow::Continue()
{
        if (!m_continue) return;
        m_menu->hide();
        m_win->hide();
        m_board->show();
        m_board->continueGame();
        m_board->setFocus();
}

void GameWindow::showMenu()
{
        m_board->reset();
        m_board->hide();
        m_win->hide();
        m_menu->show();
        m_menu->setFocus();
}

void GameWindow::show_scores()
{
        m_score->show();
}
