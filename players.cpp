#include "players.hpp"

Players::Players(QWidget* p)
        : QDialog(p)
{
        setWindowTitle(tr("Players"));
        QHBoxLayout* l = new QHBoxLayout;
        m_layout =  new QVBoxLayout;
        m_editor = new QLineEdit(this);
        m_editor->setInputMask("Enter your username");
        m_layout->addWidget(m_editor);
        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
        l->addWidget(buttonBox);
        m_layout->addStretch();
        m_layout->addSpacing(12);
        m_layout->addLayout(l);
        connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
        connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void Players::enter_username()
{
}

