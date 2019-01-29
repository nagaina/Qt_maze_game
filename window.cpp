#include "window.hpp"
#include <iostream>

#include "game.hpp"

#include <QEvent>
#include <QIcon>
#include <QList>
#include <QMenuBar>
#include <QString>
#include <QToolBar>
#include <QPushButton>
#include <QPalette>

Window::Window(QWidget* parent, Qt::WindowFlags wf)
        : QMainWindow(parent, wf)
{
        m_frame = new QFrame(this);
        QPalette p;
        p.setColor(QPalette::Background, Qt::red);
        m_frame->setPalette(p);
        m_game = new GameWindow(this);
        m_game->setStyleSheet("color : blue");
        setCentralWidget(m_game);
        setMinimumWidth(1000);
        setMinimumHeight(750);
        initToolBar();
        initMenuBar();
        setWindowTitle(tr("MAZE"));
        make_connections();
}

void Window::initMenuBar()
{
        QMenu* game_menu = menuBar()->addMenu("Game");
        game_menu->addAction(tr("New Game"), m_game, SLOT(NewGame()), tr("Ctrl+N"));
        game_menu->addAction(tr("Menu"), m_game, SLOT(showMenu()), tr("Ctrl+T"));
        game_menu->addAction(tr("Quit"), this, SLOT(close()), tr("Ctrl+C"));
}

void Window::initToolBar()
{
        QToolBar* game_toolBar = addToolBar(tr("Game"));
        game_toolBar->addAction(tr("New Game"), m_game, SLOT(NewGame()));
        game_toolBar->addAction(tr("Menu"), m_game, SLOT(showMenu()));
        game_toolBar->addAction(tr("Quit"), this, SLOT(close()));
}

void Window::make_connections()
{
        connect(m_game, SIGNAL(Quit()), this, SLOT(close()));
}

