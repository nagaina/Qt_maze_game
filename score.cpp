#include "score.hpp"

#include <QDialogButtonBox>
#include <QLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QComboBox>

Score::Score(QWidget* parent)
        : QDialog(parent)
{
	setWindowTitle(tr("Maze Scores"));

	QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Close, Qt::Horizontal, this);
	connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));

	m_sizes = new QComboBox(this);

	QHBoxLayout* section_layout = new QHBoxLayout;
	section_layout->addWidget(new QLabel(tr("<b>Size:</b>"), this));
	section_layout->addWidget(m_sizes, 1);

	m_lists = new QStackedWidget(this);
	connect(m_sizes, SIGNAL(activated(int)), m_lists, SLOT(setCurrentIndex(int)));

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addLayout(section_layout);
	layout->addWidget(m_lists);
	layout->addSpacing(12);
	layout->addWidget(buttons);

//	read();
}


