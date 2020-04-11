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

class GamePage : public QGraphicsView
{
	Q_OBJECT
public:
	GamePage(QWidget *parent = nullptr);
	~GamePage();
	void drawMap();
	void keyPressEvent(QKeyEvent *event);
	void marioRunRight();
	void marioRunLeft();
	void marioJump();
	void adjustSound();
public slots:
	void refresh();

signals:
	void escPressed();


private:
	Game mainGame;
	timer *t1;
	QTimer *timer1;
	QTimer *fallTimer;
	QGraphicsScene *scene;
	QMediaPlayer *themesong;
	int volumeLvl;
};
