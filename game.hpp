#ifndef GAME_HPP
#define GAME_HPP

#include <QWidget>
#include <QLayout>
#include "board.hpp"
#include "menu.hpp"
#include "win.hpp"
#include "score.hpp"
#include "players.hpp"

class GameWindow : public QWidget
{
        Q_OBJECT
public:
        GameWindow(QWidget*);

        ~GameWindow();

        void make_connections();
signals:
        void Quit();

public slots:
        void NewGame();
        void level_changed();
        void Continue();

        void showMenu();
        void win();
        void show_scores();

private:
        Board* m_board;
        Menu* m_menu;
        WinWindow* m_win;
        QLayout* m_layout;

        Score* m_score;
        Players* m_players;

        bool m_continue;
};

#endif
