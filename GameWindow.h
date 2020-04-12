#pragma once

#include <qwidget.h>
#include <qlayout.h>
#include <qlabel.h>
#include "GameEngine/Game.h"
#include "GameEngine/timer.h"
#include <QGraphicsScene>
#include <qgraphicsview.h>
#include <qdebug.h>
#include "Options.h"
#include <QGraphicsPixmapItem>
#include "GameEngine/Character.h"
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsTextItem>


class GamePage : public QGraphicsView
{
	Q_OBJECT
public:
	GamePage(int lvl = 1);
	~GamePage();
	void drawMap();
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void marioRunRight();
	void marioRunLeft();
	void marioJump();
public slots:
	void refresh();

signals:
	void escPressed();

private:
	Game *mainGame;
	timer *t1;
	QTimer *timer1;
	QGraphicsScene *scene;
	QMediaPlayer *themesong;
	int volumeLvl;
	QGraphicsTextItem *lifePointsText;
	QGraphicsTextItem *lifeCountText;
};
