#pragma once

#include <qgraphicsview.h>
#include <qmainwindow.h>
#include "GameWindow.h"
#include "GameEngine/timer.h"
#include "GameEngine/XController.h"
#include "GameEngine/Game.h"

#define LEFT 0
#define RIGHT 1

class Event : public QGraphicsView
{
public:
	explicit Event( QGraphicsView *parent = nullptr);
	~Event();

signals:
	void marioJump();
	void hitBarrel();
	void marioRun(int direction);
	void climb();
	void goDown();

private:
	void push_eventController();
	//void push_eventKeyboard(QKeyEvent *event);
};
