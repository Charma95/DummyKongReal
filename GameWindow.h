/*
@Auteur: Equipe p-02
@Fichier: GameWindow.h
@Date : 9 fevrier 2020
@Brief : Declaration de la classe GameWindow
*/
#pragma once

#include <qwidget.h>
#include <qlayout.h>
#include <qlabel.h>
#include "GameEngine/Game.h"
#include <QGraphicsScene>
#include <qgraphicsview.h>
#include <memory>
#include <qdebug.h>
#include "Options.h"
#include <QGraphicsPixmapItem>
#include <qmessagebox.h>
#include "GameEngine/Character.h"
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsTextItem>
#include "AllocationMetrics.h"


class GamePage : public QGraphicsView
{
	Q_OBJECT
public:
	GamePage(int lvl = 1);
	~GamePage();
	void drawMap();
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

public slots:
	void refresh();
	void finishLevel();

signals:
	void escPressed();

private:
	Game *mainGame;
	QTimer *timer1;
	QGraphicsScene *scene;
	QMediaPlayer *themesong;
	QMediaPlaylist *playlist;
	QGraphicsPixmapItem *pauline;
	Tile *t;
	Ladder *l;
	int volumeLvl;
	QGraphicsTextItem *lifePointsText;
	QGraphicsTextItem *lifeCountText;
};


