/*
@Brief: Implementation de la classe GameWindow
@Author: Equipe P-02
@File: GameWindow.cpp
@Date: 2020-04-12
*/
#include "GameWindow.h"

GamePage::GamePage(int lvl) : QGraphicsView()
{
	mainGame = new Game(lvl);
	QObject::connect(mainGame->getMario(), SIGNAL(finishLevel()), this, SLOT(finishLevel()));
	// initialiser la musique et l'appliquer à la page actuelle
	QMediaPlaylist *playlist = new QMediaPlaylist();
	playlist->addMedia(QUrl("song/01 - Donkey Kong Main Theme.mp3"));
	playlist->setPlaybackMode(QMediaPlaylist::Loop);
	themesong = new QMediaPlayer();
	themesong->setPlaylist(playlist);
	themesong->play();
	pauline = new Pauline();
	
	//initialiser la scène et et les éléments qui sont dedans
	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, PIX_WIDTH * MAX_WIDTH, PIX_HEIGHT * MAX_HEIGHT);
	setBackgroundBrush(QBrush(QImage("Images/Background.jpg")));
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(PIX_WIDTH * MAX_WIDTH, PIX_HEIGHT * MAX_HEIGHT);
	// dessiner la map du jeu et ajouter le joueur
	drawMap();

	// ajouter le texte et les points de vie � la scene
	QFont font;
	font.setPointSize(20);
	font.setBold(true);
	lifePointsText = new QGraphicsTextItem();
	lifePointsText->setFont(font);
	lifePointsText->setDefaultTextColor(Qt::blue);
	lifePointsText->setPlainText("Life Points : 100");
	lifePointsText->setPos(0, 0);
	lifeCountText = new QGraphicsTextItem();
	lifeCountText->setFont(font);
	lifeCountText->setDefaultTextColor(Qt::blue);
	lifeCountText->setPlainText("Life Count : 5");
	lifeCountText->setPos(PIX_WIDTH * (MAX_WIDTH - 6), 0);

	scene->addItem(lifePointsText);
	scene->addItem(lifeCountText);

	setScene(scene);

	// Initialiser le timer servant à changer les différents "frames"
	timer1 = new QTimer();
	QObject::connect(timer1, SIGNAL(timeout()), this, SLOT(refresh()));
	timer1->start(10);

	// Afficher un message indiquant qu'il faut cliquer dans l'écran avant de pouvoir jouer
	QMessageBox startMessage;
	startMessage.setText("Please click on the window to play");
	startMessage.setInformativeText("Have fun!");
	startMessage.setWindowIcon(QIcon("Images/Icon.png"));
	startMessage.setIconPixmap(QPixmap("Images/Icon.png"));
	startMessage.setStandardButtons(QMessageBox::Ok);
	startMessage.setDefaultButton(QMessageBox::Ok);
	int ret = startMessage.exec();
}

GamePage::~GamePage()
{
	delete pauline;
	delete scene;
	delete timer1;
	delete themesong;
}

/* Cette fonction permet d'itérer à travers un matrice représentant un niveau et ajouter 
tous les éléments à la scène*/
void GamePage::drawMap()
{
	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_WIDTH; j++)
		{
			Tile *t;
			Ladder *l;
			
			switch (mainGame->getLevel()->getMap(i, j))
			{
			case MAP:
				t = new Tile();
				t->setPos(PIX_WIDTH * j, PIX_HEIGHT * i);
				t->setVisible(true);
				scene->addItem(t);
				break;
			case LADDER:
				l = new Ladder();
				l->setPos(PIX_WIDTH * j, PIX_HEIGHT * i);
				scene->addItem(l);
				break;
			case PAULINE:
				pauline->setPos(PIX_WIDTH * j, (PIX_HEIGHT * i)-38);
				scene->addItem(pauline);
				break;
			default:
				break;
			}
		}
	}
	mainGame->getMario()->setFlag(QGraphicsItem::ItemIsFocusable);
	mainGame->getMario()->setFocus();
	setFocusPolicy(Qt::StrongFocus);
	scene->addItem(mainGame->getMario());

}

/* Cette fonction permet de rafraîchir la scène et les éléments s'y retrouvant */
void GamePage::refresh()
{
	// updater la position de mario
	mainGame->getMario()->updatePosition();

}

void GamePage::finishLevel()
{
	timer1->stop();
	QMessageBox win;
	win.setText("You Win!!");
	win.setIconPixmap(QPixmap("Images/win.png"));
	win.setWindowIcon(QIcon("Images/Icon.png"));
	win.setStandardButtons(QMessageBox::Ok);
	win.setDefaultButton(QMessageBox::Ok);
	int ret = win.exec();
	emit escPressed();
}

/* Détecter lorsqu'une touche est appuyée */
void GamePage::keyPressEvent(QKeyEvent *event) 
{
	if (event->key() == Qt::Key_A)
	{
		if (mainGame->getMario()->pos().x() > 0)
			mainGame->getMario()->backward();
	}
	else if (event->key() == Qt::Key_D) 
	{
		if (mainGame->getMario()->pos().x() + 48 < PIX_WIDTH * MAX_WIDTH)
			mainGame->getMario()->forward();
	}
	else if (event->key() == Qt::Key_Escape)
	{
		emit escPressed();
	}
	else if (event->key() == Qt::Key_Space)
	{
		mainGame->getMario()->jump();
	}
	else if (event->key() == Qt::Key_W)
	{
		mainGame->getMario()->climbUp();
	}
	else if (event->key() == Qt::Key_S)
	{
		mainGame->getMario()->climbDown();
	}
}

/* Détecter lorsqu'une touche est relâchée */
void GamePage::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_A || event->key() == Qt::Key_D)
	{
		mainGame->getMario()->stop();
	}
	else if (event->key() == Qt::Key_W || event->key() == Qt::Key_S)
	{
		mainGame->getMario()->stopClimbing();
	}
}
