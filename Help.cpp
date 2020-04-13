/*
Auteur: Equipe p-02
Fichier: Help.cpp
Date : 9 fevrier 2020
Description : Implementation des methodes de la classe Help
*/

#include "Help.h"

HelpPage::HelpPage(QWidget *parent)
	:QMainWindow(parent)
{
	setupUI();
}

HelpPage::~HelpPage()
{
		delete Message;
		delete helpLayout;
		delete Ok;

		/* Must be the last deleted -------------------------------*/
		delete helpWidget;
}

void HelpPage::setupUI()
{
	createWidget();
	initializeWidget();
}

/* Créer le widget s'appliquant à la fenêtre */
void HelpPage::createWidget()
{
	helpWidget = new QWidget(this);
	/*Setting the background color----------------------------*/
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::black);
	helpWidget->setAutoFillBackground(true);
	helpWidget->setPalette(pal);
	helpLayout = new QGridLayout();
}

/* Initialiser tous les éléments se retrouvant dans la fenêtre */
void HelpPage::initializeWidget()
{
	Message = new QLabel();
	Message->setFixedSize(700, 600);
	QFont f("Arial", 14);
	Message->setFont(f);
	Message->setText("<font color='blue'>Help Menu<br><br>******* Keyboard ********<br><br>A  -  Run to the left<br>D  -  Run to the right<br>W  -  Go up a ladder<br>S  -  Go down a ladder<br>SPACE  -  Jump<br>1  -  Hit with the hammer<br><br> ******** Controller ********<br><br>A  -  Jump<br>X  -  Hit with the hammer<br>LEFT JOYSTICK  -  Run and climb ladders<br></font>");
	Message->setAlignment(Qt::AlignCenter);
	Ok = new QPushButton("Ok");
	Ok->setFixedSize(150, 35);
	QObject::connect(Ok, SIGNAL(clicked()), this, SLOT(closeHelpPage()));

	helpLayout->addWidget(Message, 1, 3, Qt::AlignCenter);
	helpLayout->addWidget(Ok, 5, 3, Qt::AlignCenter);
	helpWidget->setLayout(helpLayout);
	setCentralWidget(helpWidget);
}

/* fermet la fenêtre */
void HelpPage::closeHelpPage() 
{
	this->close();
}