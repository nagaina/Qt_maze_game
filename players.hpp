#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QLayout>
#include <QDialogButtonBox>

class Players : public QDialog
{
        Q_OBJECT
public:
        Players(QWidget* p = 0);

public slots:
        void enter_username();

        void accept() {}
        void reject() {}
private:
        QVBoxLayout* m_layout;
        QLineEdit* m_editor;
        QDialogButtonBox* buttonBox;

        std::map<std::string, int> m_players;
};

#endif
