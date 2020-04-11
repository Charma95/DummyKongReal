#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	helpPage(nullptr),
	optionsPage(nullptr),
	gamePage(nullptr)
{
	setupUI();
}

MainWindow::~MainWindow()
{
	//qDebug() << "Destructor de ton anus" << endl;
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
	delete fullScreenAction;
	delete normalScreenAction;
	delete fileMenu;
	delete levelsMenu;
	delete viewMenu;
	delete menuBar;
	if (mainLayout != nullptr)delete mainLayout;
	if (centralWidget != nullptr)delete centralWidget;
}

void MainWindow::showHelpPage()
{
	helpPage = std::make_unique<HelpPage>(this);
	helpPage->show();
}

void MainWindow::showOptionsPage()
{
	if (optionsPage != nullptr) delete optionsPage;
	optionsPage = new OptionsPage();
	optionsPage->show();
}

void MainWindow::showLevelsPage()
{
//	LevelsPage *levelsPage;
	levelsPage = new LevelsPage(this);
	setCentralWidget(levelsPage);
	QObject::connect(levelsPage, SIGNAL(levelSelected()), this, SLOT(showGamePage()));
	Continue = nullptr;
	Play = nullptr;
	Option = nullptr;
	Help = nullptr;
	Exit = nullptr;
	mainLayout = nullptr;
	centralWidget = nullptr;
}

void MainWindow::showHomePage()
{
	gamePage = nullptr;
	setupUI();
}

void MainWindow::showGamePage()
{
	gamePage = new GamePage();
	QObject::connect(gamePage, SIGNAL(escPressed()), this, SLOT(showHomePage()));
	setCentralWidget(gamePage);
}

/* ***********************************************************
* save level in a .log file stored in the project
*
*
*
*************************************************************/
void MainWindow::saveLevel()
{
	/* Pour fin de tests seulement */
	m_level = "42";
	/*-----------------------------*/
	QString fName = "logs/DunkeyKong_Sauvegarde.log";
	QFile file(fName);

	if (file.open(QIODevice::ReadWrite | QIODevice::Text))
	{
		QTextStream stream(&file);
		stream << m_level << endl;
	}
	file.close();
	
}

void MainWindow::initWidget()
{
	centralWidget = new QWidget(this);
	mainLayout = new QGridLayout();
}
void MainWindow::initButton()
{
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
	QObject::connect(Save, SIGNAL(clicked()), this, SLOT(saveLevel()));
	Exit = new QPushButton("Exit");
	Exit->setFixedSize(200, 40);
	QObject::connect(Exit, SIGNAL(clicked()), this, SLOT(exitGame()));
}
void MainWindow::initLayout()
{
	mainLayout->setHorizontalSpacing(0);
	mainLayout->setVerticalSpacing(0);

	QPixmap bkgnd("Images/Background1.jpg");
	QPalette palette;
	centralWidget->setAutoFillBackground(true);
	palette.setBrush(QPalette::Background, bkgnd);
	centralWidget->setPalette(palette);
}
void MainWindow::initMenus()
{
	menuBar = new QMenuBar();
	fileMenu = new QMenu("File");
	levelsMenu = new QMenu("Levels");
	viewMenu = new QMenu("View");

	optionsAction = new QAction("Options");
	saveAction = new QAction("Save");
	saveAction->setIcon(QIcon("Images/save.png"));
	QObject::connect(saveAction, SIGNAL(triggered()), this, SLOT(saveLevel()));
	homeAction = new QAction("Home");
	QObject::connect(homeAction, SIGNAL(triggered()), this, SLOT(showHomePage())); 
	quitAction = new QAction("Quit");
	level1Action = new QAction("Level 1");
	level2Action = new QAction("Level 2");
	level3Action = new QAction("Level 3");
	fullScreenAction = new QAction("Full screen");
	normalScreenAction = new QAction("Regular screen");

	fileMenu->addAction(optionsAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(homeAction);
	fileMenu->addAction(quitAction);

	levelsMenu->addAction(level1Action);
	levelsMenu->addAction(level2Action);
	levelsMenu->addAction(level3Action);

	viewMenu->addAction(fullScreenAction);
	viewMenu->addAction(normalScreenAction);

	menuBar->addMenu(fileMenu);
	menuBar->addMenu(levelsMenu);
	menuBar->addMenu(viewMenu);

	setMenuBar(menuBar);
}
void MainWindow::initUI()
{
	mainLayout->setAlignment(Qt::AlignCenter);
	mainLayout->setSpacing(30);
	mainLayout->addWidget(Continue, 1, 3, 1, 1);
	mainLayout->addWidget(Play, 2, 3, 1, 1);
	mainLayout->addWidget(Option, 3, 3, 1, 1);
	mainLayout->addWidget(Help, 4, 3, 1, 1);
	mainLayout->addWidget(Exit, 5, 3, 1, 1);

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
	//qDebug() << c_level << endl;
}



void MainWindow::exitGame()
{
	QMessageBox msgBox;
	msgBox.setText("Your progression since your last session");
	msgBox.setInformativeText("Do you want to save your changes?");
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);
	int ret = msgBox.exec();
	switch (ret) {
	case QMessageBox::Save:
		saveLevel();
		break;
	case QMessageBox::Discard:
		this->close();
		break;
	case QMessageBox::Cancel:
		this->close();
		break;
	default:
		qDebug() << "we are in trouble" << endl;
		break;
	}
	this->close();
}

/*void MainWindow::keyPressEvent(QKeyEvent *event) {
	qDebug("allo");
	// move the player left and right
	if (event->key() == Qt::Key_A) {
		qDebug("gauche\n");
		//if (pos().x() > 0)
			//setPos(x() - 100, y());
	}
	else if (event->key() == Qt::Key_D) {
		qDebug("Droite\n");
		//if (pos().x() + 48 < PIX_WIDTH * MAX_WIDTH);
		//setPos(x() + 100, y());
	}
}*/





