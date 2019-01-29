#include "menu.hpp"
#include <iostream>

#include <QFont>
#include <QPainter>

Menu::Menu(QWidget* p)
        : QWidget(p)
{
        QFont f("NEW GAME",12, QFont::Bold);
        m_new_game = new QPushButton("New Game", this);
        m_new_game->setFixedSize(150, 50);
        m_new_game->setFont(f);
        m_new_game->setDefault(true);
        m_next_game = new QPushButton("Continue", this);
        m_next_game->setFixedSize(150, 50);
        m_next_game->setFont(f);
        m_next_game->setDefault(true);
        //m_score_game = new QPushButton("High Scores", this);
        //m_score_game->setFixedSize(150, 50);
        //m_score_game->setFont(f);
        //m_score_game->setDefault(true);
        m_quit_game = new QPushButton("Quit", this);
        m_quit_game->setFixedSize(150, 50);
        m_quit_game->setFont(f);
        m_quit_game->setDefault(true);
        m_layout = new QVBoxLayout();
        m_layout->addStretch();
        m_layout->addWidget(m_new_game, 0, Qt::AlignCenter);
        m_layout->addWidget(m_next_game, 0, Qt::AlignCenter);
        //m_layout->addWidget(m_score_game, 0, Qt::AlignCenter);
        m_layout->addWidget(m_quit_game, 0, Qt::AlignCenter);
        m_layout->addStretch();
        setLayout(m_layout);
        make_connections();
}

void Menu::make_connections()
{
        connect(m_new_game, SIGNAL(clicked()), this, SIGNAL(new_game()));
        connect(m_next_game, SIGNAL(clicked()), this, SIGNAL(continue_game()));
        //connect(m_score_game, SIGNAL(clicked()), this, SIGNAL(show_score()));
        connect(m_quit_game, SIGNAL(clicked()), this, SIGNAL(quit_game()));
}

Menu::~Menu()
{
        disconnect(m_new_game, SIGNAL(clicked()), this, SIGNAL(new_game()));
        disconnect(m_next_game, SIGNAL(clicked()), this, SIGNAL(continue_game()));
        //disconnect(m_score_game, SIGNAL(clicked()), this, SIGNAL(show_score()));
        disconnect(m_quit_game, SIGNAL(clicked()), this, SIGNAL(quit_game()));
}

void Menu::paintEvent(QPaintEvent*)
{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QImage img("bg1");
        painter.drawImage(0, 0, img);
}

