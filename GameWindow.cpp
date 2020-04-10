#include "GameWindow.h"

GamePage::GamePage(QWidget *parent) : QGraphicsView(parent)
{
	// créer la scène et mettre le fond d'écran
	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, PIX_WIDTH * MAX_WIDTH, PIX_HEIGHT * MAX_HEIGHT);
	setBackgroundBrush(QBrush(QImage("Images/Background.jpg")));
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(PIX_WIDTH * MAX_WIDTH, PIX_HEIGHT * MAX_HEIGHT);
	// dessiner la map du jeu et ajouter le joueur
	drawMap();

	setScene(scene);

	t1 = new timer([&]() {

		refresh();
	}, 100);

}

GamePage::~GamePage()
{
	cout << "destructeur de gamePage\n";
	delete scene;
	delete t1;
}

void GamePage::drawMap()
{
	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_WIDTH; j++)
		{
			QGraphicsPixmapItem *tile = new QGraphicsPixmapItem();
			switch (mainGame.getLevel()->getMap(i, j))
			{
			case MAP:
				tile->setPixmap(QPixmap("Images/Floor.jpg"));
				break;
			case LADDER:
				tile->setPixmap(QPixmap("Images/Ladder.jpg"));
				break;
			default:
				break;
			}
			tile->setPos(PIX_WIDTH * j, PIX_HEIGHT * i);
			scene->addItem(tile);
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
	mainGame.refresh();
}

void GamePage::marioRunRight()
{
	mainGame.setMario(RIGHT);
	mainGame.getMario()->setPos(mainGame.getMario()->x() + 10, mainGame.getMario()->y());
}

void GamePage::marioRunLeft()
{
	mainGame.setMario(LEFT);
	mainGame.getMario()->setPos(mainGame.getMario()->x() - 10, mainGame.getMario()->y());
}

void GamePage::marioJump()
{
	//mainGame.setMario(HIGH);
	mainGame.getMario()->setPos(mainGame.getMario()->x() - 10, mainGame.getMario()->y() + 5);
}

void GamePage::keyPressEvent(QKeyEvent *event) 
{
	qDebug("allo");
	// move the player left and right
	if (event->key() == Qt::Key_A)
	{
		qDebug("gauche\n");
		if (mainGame.getMario()->pos().x() > 0)
			marioRunLeft();
	}
	else if (event->key() == Qt::Key_D) 
	{
		qDebug("Droite\n");
		if (mainGame.getMario()->pos().x() + 48 < PIX_WIDTH * MAX_WIDTH);
		marioRunRight();
	}
	else if (event->key() == Qt::Key_Escape)
	{
		emit escPressed();
	}
	else if (event->key() == Qt::Key_Space)
	{
		marioJump();
	}
}