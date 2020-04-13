/*
Auteur: Equipe p-02
Fichier: Character.h
Date : 9 fevrier 2020
Description : Declaration de la classe Character
*/

#pragma once
#include <string>
#include "Level.h"

#include <QGraphicsPixmapItem>
#include <qmessagebox.h>
#include <QKeyEvent>
#include "Tile.h"
#include "Ladder.h"
#include "Pauline.h"

#define JUMPFORCE 500
#define RUNSPEED 300
#define CLIMBSPEED 150
#define G 1000
#define DT 0.01
#define PIX_WIDTH 50
#define PIX_HEIGHT 50

// états des personnages
#define NOTHING 0
#define RUNNING_R 1
#define RUNNING_L 2
#define JUMPING_R 3
#define JUMPING_L 4
#define CLIMBING 5
#define NOTHING_CLIMBING 6

using namespace std;

struct vector2
{
	float x;
	float y;
};

class Character : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
private:
	int animationIndex;
	int animationState;
	int lifePoints;
	int lifeCount;
	string name;
	vector2 currentVelocity;
	vector<QPixmap> nothingVector;
	vector<QPixmap> runningLeftVector;
	vector<QPixmap> runningRightVector;
	vector<QPixmap> jumpingLeftVector;
	vector<QPixmap> jumpingRightVector;
	vector<QPixmap> climbingVector;
	vector<QPixmap> nothingClimbingVector;
	bool climbing;

public:
	Character(int positionX = 1, int positionY = MAX_HEIGHT - 2, QPixmap pixmap = QPixmap(""));
	virtual ~Character();
	int getLifePoints();
	void setLifePoints(int newLifePoints);
	int getLifeCount();
	void setLifeCount(int newLifeCount);
	string getName();
	void setName(string newName);
	void takeDamage(int dmg);
	void gainLifePoints(int lifePts);


	// new code for movement
	bool isCollidingWithTile();
	bool isCollidingWithLadder();
	bool isCollidingWithPauline();
	void land();
	void updatePosition();
	bool forward();
	bool backward();
	void climbUp();
	void climbDown();
	void stopClimbing();
	void stop();
	bool jump();
	void replaceOnTopOfObject();
	void hitHead();
	void changeAnimationState(int newState);
	void animate(vector<QPixmap> vec);
	void updateAnimationState();

signals:
	void finishLevel();
};
