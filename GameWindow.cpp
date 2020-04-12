#include "GameWindow.h"

GamePage::GamePage(QWidget *parent) : QGraphicsView(parent)
{
	// créer la scène et mettre le fond d'écran
	scene = new QGraphicsScene();
	QMediaPlaylist *playlist = new QMediaPlaylist();
	playlist->addMedia(QUrl("song/01 - Donkey Kong Main Theme.mp3"));
	playlist->setPlaybackMode(QMediaPlaylist::Loop);

	themesong = new QMediaPlayer();
	themesong->setPlaylist(playlist);
	themesong->play();
	
	
	scene->setSceneRect(0, 0, PIX_WIDTH * MAX_WIDTH, PIX_HEIGHT * MAX_HEIGHT);
	setBackgroundBrush(QBrush(QImage("Images/Background.jpg")));
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(PIX_WIDTH * MAX_WIDTH, PIX_HEIGHT * MAX_HEIGHT);
	// dessiner la map du jeu et ajouter le joueur
	drawMap();

	setScene(scene);

	timer1 = new QTimer();
	QObject::connect(timer1, SIGNAL(timeout()), this, SLOT(refresh()));
	timer1->start(10);

}

GamePage::~GamePage()
{
	delete scene;
	delete timer1;
}

void GamePage::drawMap()
{
	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_WIDTH; j++)
		{
			Tile *t;
			Ladder *l;
			
			switch (mainGame.getLevel()->getMap(i, j))
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
			default:
				break;
			}
		}
	}
	mainGame.getMario()->setFlag(QGraphicsItem::ItemIsFocusable);
	mainGame.getMario()->setFocus();
	setFocusPolicy(Qt::StrongFocus);
	//setFocus();
	scene->addItem(mainGame.getMario());

	//scene->addItem(mario);

}

void GamePage::refresh()
{
	// updater la position de mario
	mainGame.getMario()->updatePosition();
	adjustSound();
}

void GamePage::marioRunRight()
{
	mainGame.setMario(RIGHT);
	mainGame.getMario()->setPos(mainGame.getMario()->x() + 20, mainGame.getMario()->y());
}

void GamePage::marioRunLeft()
{
	mainGame.setMario(LEFT);
	mainGame.getMario()->setPos(mainGame.getMario()->x() - 20, mainGame.getMario()->y());
}

void GamePage::marioJump()
{
	//mainGame.setMario(HIGH);
	mainGame.getMario()->setPos(mainGame.getMario()->x(), mainGame.getMario()->y() + 5);
}
void GamePage::adjustSound()
{
	OptionsPage option;
	volumeLvl = option.volume;
	themesong->setVolume(volumeLvl);
}

void GamePage::keyPressEvent(QKeyEvent *event) 
{
	// move the player left and right
	if (event->key() == Qt::Key_A)
	{
		if (mainGame.getMario()->pos().x() > 0)
			mainGame.getMario()->backward();
	}
	else if (event->key() == Qt::Key_D) 
	{
		if (mainGame.getMario()->pos().x() + 48 < PIX_WIDTH * MAX_WIDTH)
			mainGame.getMario()->forward();
	}
	else if (event->key() == Qt::Key_Escape)
	{
		emit escPressed();
	}
	else if (event->key() == Qt::Key_Space)
	{
		mainGame.getMario()->jump();
	}
	else if (event->key() == Qt::Key_W)
	{
		mainGame.getMario()->climbUp();
	}
	else if (event->key() == Qt::Key_S)
	{
		mainGame.getMario()->climbDown();
	}
}

void GamePage::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_A || event->key() == Qt::Key_D)
	{
		mainGame.getMario()->stop();
	}
	else if (event->key() == Qt::Key_W || event->key() == Qt::Key_S)
	{
		mainGame.getMario()->stopClimbing();
	}
}
