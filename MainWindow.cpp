/*
Auteur: Equipe p-02
Fichier: MainWindow.cpp
Date : 9 fevrier 2020
Description : Implementation des methodes de la classe MainWindow
*/
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	helpPage(nullptr),
	optionsPage(nullptr),
	gamePage(nullptr),
	level(1)
{
	setupUI();
	std::cout << "Constructeur de mainWindow" << std::endl;
	PrintMemoryUsage();
}

MainWindow::~MainWindow()
{ 
	if (logo != nullptr) delete logo;
	if(Continue != nullptr) delete Continue;
	if(Play != nullptr)delete Play;
	if (Option != nullptr)delete Option;
	if (Help != nullptr)delete Help;
	if (Exit != nullptr)delete Exit;
	if (optionsPage != nullptr) delete optionsPage;
	if (gamePage != nullptr) delete gamePage;
	delete optionsAction;
	delete saveAction;
	delete homeAction;
	delete quitAction;
	delete level1Action;
	delete level2Action;
	delete level3Action;
	delete level4Action;
	delete fullScreenAction;
	delete normalScreenAction;
	delete fileMenu;
	delete levelsMenu;
	delete menuBar;
	if (mainLayout != nullptr)delete mainLayout;
	if (centralWidget != nullptr)delete centralWidget;
	std::cout << "Destructeur de mainWindow" << std::endl;
	PrintMemoryUsage();
}

/* Afficher la page d'aide */
void MainWindow::showHelpPage()
{
	helpPage = std::make_unique<HelpPage>(this);
	helpPage->show();
}

/* Afficher la page d'options */
void MainWindow::showOptionsPage()
{
	if (optionsPage != nullptr) delete optionsPage;
	optionsPage = new OptionsPage();
	optionsPage->show();
}

/* Afficher la page permettant de choisir le niveau */
void MainWindow::showLevelsPage()
{
	levelsPage = new LevelsPage(this);
	setCentralWidget(levelsPage);
	QObject::connect(levelsPage, SIGNAL(levelSelected(int)), this, SLOT(showGamePage(int)));
	QObject::connect(levelsPage, SIGNAL(levelSelected(int)), this, SLOT(saveLevel(int)));
	Continue = nullptr;
	Play = nullptr;
	Option = nullptr;
	Help = nullptr;
	Exit = nullptr;
	mainLayout = nullptr;
	centralWidget = nullptr;
}

/* Afficher la page d'accueil */
void MainWindow::showHomePage()
{
	gamePage = nullptr;
	setupUI();
}

/* Afficher la page de jeu */
void MainWindow::showGamePage(int level)
{
	gamePage = new GamePage(level);
	QObject::connect(gamePage, SIGNAL(escPressed()), this, SLOT(showHomePage()));
	setCentralWidget(gamePage);
}

void MainWindow::switchOnLevel()
{
	switch (level)
	{
	case 1:
		saveLevel(1);
		break;
	case 2:
		saveLevel(2);
		break;
	case 3:
		saveLevel(3);
		break;
	case 4:
		saveLevel(4);
		break;
	default:
		break;
	}
}

/* Sauvegarder le niveau dans unn fichier .txt */
void MainWindow::saveLevel(int level)
{
	QString s = QString::number(level);
	m_level = s;
	QString fName = "logs/DunkeyKong_Sauvegarde.log";
	QFile file(fName);

	if (file.open(QIODevice::ReadWrite | QIODevice::Text))
	{
		QTextStream stream(&file);
		stream << m_level << endl;
	}
	file.close();

	QMessageBox msg;
	msg.setText("Saved successfully!");
	msg.setIconPixmap(QPixmap("Images/win.png"));
	msg.setWindowIcon(QIcon("Images/Icon.png"));
	msg.setStandardButtons(QMessageBox::Ok);
	msg.setDefaultButton(QMessageBox::Ok);
	msg.exec();
}

/* Initialiser le widget central */
void MainWindow::initWidget()
{
	centralWidget = new QWidget(this);
	mainLayout = new QGridLayout();
}

/* Initialiser les boutons */
void MainWindow::initButton()
{
	logo = new QLabel();
	logo->setPixmap(QPixmap("Images/bkgnd.png"));
	//logo->setFixedSize(1200, 500);
	Continue = new QPushButton("Continue");
	Continue->setFixedSize(200, 40);
	QObject::connect(Continue, SIGNAL(clicked()), this, SLOT(continueLastGame()));
	Play = new QPushButton("Play");
	Play->setFixedSize(200, 40);
	QObject::connect(Play, SIGNAL(clicked()), this, SLOT(showLevelsPage()));
	Option = new QPushButton("Options");
	Option->setFixedSize(200, 40);
	QObject::connect(Option, SIGNAL(clicked()), this, SLOT(showOptionsPage()));
	Help = new QPushButton("Help");
	Help->setFixedSize(200, 40);
	QObject::connect(Help, SIGNAL(clicked()), this, SLOT(showHelpPage()));
	Save = new QPushButton("Save");
	Save->setFixedSize(200, 40);
	Exit = new QPushButton("Exit");
	Exit->setFixedSize(200, 40);
	QObject::connect(Exit, SIGNAL(clicked()), this, SLOT(exitGame()));
	QObject::connect(this, SIGNAL(levelSelected(int)), this, SLOT(showGamePage(int)));
}

/* Initialiser le layout */
void MainWindow::initLayout()
{
	mainLayout->setHorizontalSpacing(0);
	mainLayout->setVerticalSpacing(0);

	QPixmap bkgnd("Images/side.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
	QPalette palette;
	palette.setColor(QPalette::Background, Qt::black);
	centralWidget->setAutoFillBackground(true);
	centralWidget->setPalette(palette);
}

/* Initialiser les menus */
void MainWindow::initMenus()
{
	menuBar = new QMenuBar();
	fileMenu = new QMenu("File");
	levelsMenu = new QMenu("Levels");
	//viewMenu = new QMenu("View");

	optionsAction = new QAction("Options");
	optionsAction->setIcon(QIcon("Images/options.png"));
	QObject::connect(optionsAction, SIGNAL(triggered()), this, SLOT(showOptionsPage()));
	saveAction = new QAction("Save");
	saveAction->setIcon(QIcon("Images/save.png"));
	QObject::connect(saveAction, SIGNAL(triggered()), this, SLOT(switchOnLevel()));
	homeAction = new QAction("Home");
	homeAction->setIcon(QIcon("Images/house.png"));
	QObject::connect(homeAction, SIGNAL(triggered()), this, SLOT(showHomePage())); 
	quitAction = new QAction("Exit");
	quitAction->setIcon(QIcon("Images/cross.png"));
	QObject::connect(quitAction, SIGNAL(triggered()), this, SLOT(exitGame()));
	level1Action = new QAction("Level 1");
	QObject::connect(level1Action, SIGNAL(triggered()), this, SLOT(level1Selected()));
	level2Action = new QAction("Level 2");
	QObject::connect(level2Action, SIGNAL(triggered()), this, SLOT(level2Selected()));
	level3Action = new QAction("Level 3");
	QObject::connect(level3Action, SIGNAL(triggered()), this, SLOT(level3Selected()));
	level4Action = new QAction("Level 4");
	QObject::connect(level4Action, SIGNAL(triggered()), this, SLOT(level4Selected()));
	fullScreenAction = new QAction("Full screen");
	normalScreenAction = new QAction("Regular screen");

	fileMenu->addAction(optionsAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(homeAction);
	fileMenu->addAction(quitAction);

	levelsMenu->addAction(level1Action);
	levelsMenu->addAction(level2Action);
	levelsMenu->addAction(level3Action);
	levelsMenu->addAction(level4Action);

	menuBar->addMenu(fileMenu);
	menuBar->addMenu(levelsMenu);

	setMenuBar(menuBar);
}

/* Initialiser l'inteface graphique */
void MainWindow::initUI()
{
	mainLayout->setAlignment(Qt::AlignCenter);
	mainLayout->setSpacing(10);
	mainLayout->addWidget(logo, 1, 3, 1, 1, Qt::AlignCenter);
	mainLayout->addWidget(Continue, 2, 3, 1, 1, Qt::AlignCenter);
	mainLayout->addWidget(Play, 3, 3, 1, 1, Qt::AlignCenter);
	mainLayout->addWidget(Option, 4, 3, 1, 1, Qt::AlignCenter);
	mainLayout->addWidget(Help, 5, 3, 1, 1, Qt::AlignCenter);
	mainLayout->addWidget(Exit, 6, 3, 1, 1, Qt::AlignCenter);

	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);
}

void MainWindow::setupUI()
{
	initWidget();
	initMenus();
	initLayout();
	initButton();
	initUI();
}

/* Lire le fichier de sauvegarde et continuer la dernière partie */
void MainWindow::continueLastGame()
{
	QString fName = "logs/DunkeyKong_Sauvegarde.log";
	QString c_level;
	QFile file(fName);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		c_level = file.readAll();
	}
	file.close();
	/* Add line to put the player to the right level*/
	 int iLevel = c_level.toInt();
	 emit levelSelected(iLevel);
}



void MainWindow::exitGame()
{
	QMessageBox msgBox;
	msgBox.setText("Save your progression");
	msgBox.setInformativeText("Do you want to save your changes?");
	msgBox.setWindowIcon(QIcon("Images/Icon.png"));
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);
	int ret = msgBox.exec();
	switch (ret) 
	{
	case QMessageBox::Save:
		saveLevel(level);
		break;
	case QMessageBox::Discard:
		this->close();
		break;
	case QMessageBox::Cancel:
		msgBox.close();
		break;
	default:
		break;
	}
}

void MainWindow::level1Selected()
{
	level = 1;
	emit levelSelected(1);
}

void MainWindow::level2Selected()
{
	level = 2;
	emit levelSelected(2);
}

void MainWindow::level3Selected()
{
	level = 3;
	emit levelSelected(3);
}

void MainWindow::level4Selected()
{
	level = 4;
	emit levelSelected(4);
}









