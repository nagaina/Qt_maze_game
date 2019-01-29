#include "win.hpp"
#include "game.hpp"

#include <QPainter>

WinWindow::WinWindow(QWidget* p) : QWidget(p)
{
        QFont f("NEW GAME",12, QFont::Bold);
        m_new_button = new QPushButton("New Game", this);
        m_new_button->setFixedSize(150, 50);
        m_new_button->setFont(f);
        m_new_button->setDefault(true);
        m_quit_button = new QPushButton("Quit", this);
        m_quit_button->setFixedSize(150, 50);
        m_quit_button->setFont(f);
        m_quit_button->setDefault(true);
        m_layout = new QVBoxLayout();
        m_layout->addStretch();
        m_layout->addWidget(m_new_button, 0, Qt::AlignCenter);
        m_layout->addWidget(m_quit_button, 0, Qt::AlignCenter);
        m_layout->addStretch();
        setLayout(m_layout);
        make_connections();
}

void WinWindow::make_connections()
{
        connect(m_new_button, SIGNAL(clicked()), this, SIGNAL(new_game()));
        connect(m_quit_button, SIGNAL(clicked()), this, SIGNAL(quit_game()));
}

WinWindow::~WinWindow()
{
        disconnect(m_new_button, SIGNAL(clicked()), this, SIGNAL(new_game()));
        disconnect(m_quit_button, SIGNAL(clicked()), this, SIGNAL(quit_game()));
}

void WinWindow::paintEvent(QPaintEvent*)
{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QImage img("Win.png");
        painter.drawImage(0, 0, img);
}
