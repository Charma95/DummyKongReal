#include "Levels.h"

LevelsPage::LevelsPage(QWidget *parent) : QWidget(parent)
{
	mainLayout = new QVBoxLayout();
	level1 = new QPushButton("Level 1");
	level1->setFixedSize(300, 40);
	QObject::connect(level1, SIGNAL(clicked()), this, SLOT(showGameWindow()));
	level2 = new QPushButton("Level 2");
	level2->setFixedSize(300, 40);
	QObject::connect(level2, SIGNAL(clicked()), this, SLOT(showGameWindow()));
	level3 = new QPushButton("Level 3");
	level3->setFixedSize(300, 40);
	QObject::connect(level3, SIGNAL(clicked()), this, SLOT(showGameWindow()));
	level4 = new QPushButton("Level 4");
	level4->setFixedSize(300, 40);
	QObject::connect(level3, SIGNAL(clicked()), this, SLOT(showGameWindow()));

	QPixmap bkgnd("Images/Background1.jpg");
	QPalette palette;
	setAutoFillBackground(true);
	palette.setBrush(QPalette::Background, bkgnd);
	setPalette(palette);

	mainLayout->setAlignment(Qt::AlignCenter);
	mainLayout->setSpacing(30);
	mainLayout->addWidget(level1);
	mainLayout->addWidget(level2);
	mainLayout->addWidget(level3);
	mainLayout->addWidget(level4);
	

	setLayout(mainLayout);
}

LevelsPage::~LevelsPage()
{
	delete level1;
	delete level2;
	delete level3;
	delete mainLayout;
}

void LevelsPage::showGameWindow()
{
	emit levelSelected();
}