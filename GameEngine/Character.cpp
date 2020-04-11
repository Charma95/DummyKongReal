/*
Auteur: �quipe p-02
Fichier: Character.cpp
Date : 9 f�vrier 2020
Description : Impl�mentation des m�thodes de la classe Character
*/

#include "Character.h"


Character::Character(int positionX, int positionY, QPixmap pixmap) : QGraphicsPixmapItem()
{
	setPixmap(pixmap);
	position.x = positionX;
	position.y = positionY;
	setPos(positionX * PIX_WIDTH, 1 * PIX_HEIGHT - 26);
	jumping = false;
	falling = false;
	jumpingState = 0;
	lifePoints = 100;
	lifeCount = 5;
	hammer = nullptr;
	currentVelocity.x = 0;
	currentVelocity.y = 0;
}

Character::Character(const Character &character2)
{
	hammer = character2.hammer;
}


Character::~Character()
{
	if (hammer != nullptr) delete hammer;
}


int Character::getLifePoints()
{
	return lifePoints;
}

void Character::setLifePoints(int newLifePoints)
{
	lifePoints = newLifePoints;
}

int Character::getLifeCount()
{
	return lifeCount;
}

void Character::setLifeCount(int newLifeCount)
{
	lifeCount = newLifeCount;
}

string Character::getName()
{
	return name;
}

void Character::setName(string newName)
{
	name = newName;
}

Coordonnees Character::getPosition()
{
	return position;
}



bool Character::climb()
{
	position.y--;
	return true;
}

bool Character::fall()
{
	position.y++;
	return true;
}

bool Character::hit()
{
	return true;
}

bool Character::isJumping()
{
	return jumping;
}

bool Character::isFalling()
{
	return falling;
}

void Character::goUp()
{
	position.y--;
}

void Character::goDown()
{
	position.y++;
}

int Character::getJumpingState()
{
	return jumpingState;
}

void Character::setJumpingState(int jmp)
{
	jumpingState = jmp;
}


void Character::takeDamage(int dmg)
{
	lifePoints -= dmg;
	if (lifePoints < 0) lifePoints = 0;
	if (lifePoints == 0 && lifeCount > 0)
	{
		lifeCount--;
		lifePoints = 100;
	}
}

void Character::gainLifePoints(int lifePts)
{
	if (lifePoints + lifePts <= 100) lifePoints += lifePts;
}

void Character::attachHammer(Hammer *gameHammer) {
	gameHammer->attach();
	hammer = gameHammer;
}

bool Character::isColliding()
{
	if (collidingItems().length() != 0) return true;
	else return false;
}

void Character::land()
{
	currentVelocity.y = 0;
	int posY = y();
	if (isColliding() && posY % (PIX_HEIGHT/2) != 0) replaceOnTopOfObject();
}

void Character::updatePosition()
{
	//cout << "pos x : " << x() << " pos y : " << y() << endl;
	setPos(x() + DT * currentVelocity.x, y() + DT * currentVelocity.y);
	if (!isColliding()) currentVelocity.y = currentVelocity.y + DT * G;
	//else replaceOnTopOfObject();
}

bool Character::forward()
{
	currentVelocity.x = RUNSPEED;
	if (currentVelocity.x > RUNSPEED) currentVelocity.x = RUNSPEED;
	return true;
}

bool Character::backward()
{
	currentVelocity.x = -1 * RUNSPEED;
	if (currentVelocity.x < -1 * RUNSPEED) currentVelocity.x = -1 * RUNSPEED;
	return true;
}

bool Character::jump()
{
	currentVelocity.y -= JUMPFORCE;

	return true;
}

void Character::replaceOnTopOfObject()
{
	int posY = y();
	int dy = posY % PIX_HEIGHT;

	setPos(x(), posY - dy);
}


