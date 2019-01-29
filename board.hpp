#ifndef _board_hpp_
#define _board_hpp_

#include <QWidget>

class QLabel;
class QLayout;
class QMainWindow;
class QPushButton;
class Maze;
class Player;
class Level_interface;

class Board : public QWidget
{
        Q_OBJECT
public:
        Board(QWidget*);
        ~Board();

        void continueGame();
        void reset();

        void changeState(Level_interface*);

signals:
        void Level_changed();
        void Win();

public slots:
        void newGame();

protected:

	virtual void keyPressEvent(QKeyEvent* event);
	virtual void paintEvent(QPaintEvent*);

private:
        void loadSettings();
	void generate();
	void renderMaze();
        void renderWin();
        void go_to_next_level();
        bool check_in_bounding_box();

	int m_total_targets;
	Maze* m_maze;
	QPoint m_start;

        Player* m_player;
	unsigned int m_up;
	unsigned int m_down;
	unsigned int m_left;
	unsigned int m_right;

        Level_interface* m_level;
        int level_count;
};

#endif
