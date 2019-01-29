#ifndef MENU_HPP
#define MENU_HPP

#include <QWidget>
#include <QPushButton>
#include <QLayout>

class Menu : public QWidget
{
        Q_OBJECT
public:
        Menu(QWidget*);

        ~Menu();

        void make_connections();
signals:

        void new_game();
        void continue_game();
        void show_score();
        void quit_game();

protected:
        virtual void paintEvent(QPaintEvent*);
private:

        QPushButton* m_new_game;
        QPushButton* m_next_game;
        QPushButton* m_quit_game;
        QPushButton* m_score_game;
        QVBoxLayout* m_layout;
};

#endif
