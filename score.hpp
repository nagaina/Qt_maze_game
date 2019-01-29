#ifndef SCORE_HPP
#define SCORE_HPP

#include <QDialog>

class QComboBox;
class QStackedWidget;

class Score : public QDialog
{
        Q_OBJECT
public:
        Score(QWidget* p = 0);

public slots:
//        void add_score();

private:
  //      void read();
        QComboBox* m_sizes;
        QStackedWidget* m_lists;
};

#endif
