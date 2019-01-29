#ifndef _window_hpp_
#define _window_hpp_

#include <QMainWindow>
#include <QHBoxLayout>
#include <QFrame>

class GameWindow;
class QPushButton;
class Menu;

class Window : public QMainWindow
{
        Q_OBJECT
public:
         Window(QWidget* parent = 0, Qt::WindowFlags wf = 0);

         void make_connections();

private:
         void initMenuBar();
         void initToolBar();

         GameWindow* m_game;
         QFrame* m_frame;
};

#endif
