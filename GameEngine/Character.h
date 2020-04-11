/*
Auteur: �quipe p-02
Fichier: Character.h
Date : 9 f�vrier 2020
Description : D�claration de la classe Character
*/

#pragma once
#include <string>
#include "Level.h"
#include "timer.h"
#include "Hammer.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

#define JUMPFORCE 500
#define RUNSPEED 300
#define G 1000
#define DT 0.01
#define PIX_WIDTH 50
#define PIX_HEIGHT 50

using namespace std;

struct vector2
{
	float x;
	float y;
};

class Character : public QGraphicsPixmapItem
{
private:
	int lifePoints;
	int lifeCount;
	string name;
	Coordonnees position;
	bool jumping;
	bool falling;
	int jumpingState;
	Hammer *hammer;
	vector2 currentVelocity;

public:
	Character(int positionX = 1, int positionY = MAX_HEIGHT - 2, QPixmap pixmap = QPixmap(""));
	Character(const Character &character2);
	virtual ~Character();
	int getLifePoints();
	void setLifePoints(int newLifePoints);
	int getLifeCount();
	void setLifeCount(int newLifeCount);
	string getName();
	void setName(string newName);
	Coordonnees getPosition();
	bool climb();
	bool hit();
	void goUp();
	void goDown();

	bool fall();
	bool isFalling();
	bool isJumping();
	int getJumpingState();
	void setJumpingState(int jmp);

	void takeDamage(int dmg);
	void gainLifePoints(int lifePts);
	void attachHammer(Hammer *gameHammer);

	// new code for movement
	bool isColliding();
	void land();
	void updatePosition();
	bool forward();
	bool backward();
	bool jump();
	void replaceOnTopOfObject();
	void hitHead();
};
