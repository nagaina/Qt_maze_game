#include "window.hpp"

#include <QApplication>

int main(int argc, char** argv)
{
        QApplication app(argc, argv);
        app.setApplicationName("Maze");

        QMainWindow* window =  new Window;
        window->setStyleSheet("QMainWindow {background : blue, qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,   stop:0 rgba(60, 186, 162, 255), stop:1 rgba(100, 211, 162, 255)); border-color : blue}");
        window->show();
        return app.exec();
}
