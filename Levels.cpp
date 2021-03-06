/*
Auteur: Equipe p-02
Fichier: Levels.cpp
Date : 9 fevrier 2020
Description : Implementation des methodes de la classe Levels
*/
#include "Levels.h"

/* Initialiser tous les �l�ments se retrouvant dans la fen�tre */
LevelsPage::LevelsPage(QWidget *parent) : QWidget(parent)
{
	mainLayout = new QVBoxLayout();
	level1 = new QPushButton("Level 1");
	level1->setFixedSize(300, 40);
	QObject::connect(level1, SIGNAL(clicked()), this, SLOT(level1Selected()));

	level2 = new QPushButton("Level 2");
	level2->setFixedSize(300, 40);
	QObject::connect(level2, SIGNAL(clicked()), this, SLOT(level2Selected()));
	level3 = new QPushButton("Level 3");
	level3->setFixedSize(300, 40);
	QObject::connect(level3, SIGNAL(clicked()), this, SLOT(level3Selected()));
	level4 = new QPushButton("Level 4");
	level4->setFixedSize(300, 40);
	QObject::connect(level4, SIGNAL(clicked()), this, SLOT(level4Selected()));

	QPixmap bkgnd("Images/Background1.jpg");
	QPalette palette;
	setAutoFillBackground(true);
	palette.setColor(QPalette::Background, Qt::black);
	//palette.setBrush(QPalette::Background, bkgnd);
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
	delete level4;
	delete mainLayout;
}

/* Les 4 prochaines fonctions servent � �mettre un signal avec le bon niveau lorsque le bouton
correspondant au niveau est appuy�*/
void LevelsPage::level1Selected()
{
	emit levelSelected(1);
}
void LevelsPage::level2Selected()
{
	emit levelSelected(2);
}
void LevelsPage::level3Selected()
{
	emit levelSelected(3);
}
void LevelsPage::level4Selected()
{
	emit levelSelected(4);
}