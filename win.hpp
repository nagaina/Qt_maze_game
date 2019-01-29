#ifndef WIN_HPP
#define WIN_HPP

#include <QWidget>
#include <QPushButton>
#include <QLayout>

class WinWindow : public QWidget
{
        Q_OBJECT
public:
        WinWindow(QWidget*);

        ~WinWindow();

public:
        void make_connections();

signals:

        void new_game();
        void quit_game();

protected:
        virtual void  paintEvent(QPaintEvent*);

private:
        QPushButton* m_new_button;
        QPushButton* m_quit_button;
        QVBoxLayout* m_layout;
};

#endif
