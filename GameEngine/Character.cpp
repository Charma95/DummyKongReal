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
	setPos(positionX * PIX_WIDTH, positionY * PIX_HEIGHT - 26);
	jumping = false;
	falling = false;
	jumpingState = 0;
	lifePoints = 100;
	lifeCount = 5;
	hammer = nullptr;
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

bool Character::jump()
{
	jumpingState++;
	position.y--;
	if (jumpingState == 3)
	{
		jumpingState = 0;
	}
	//else jump();

	return true;
}

Coordonnees Character::getPosition()
{
	return position;
}

bool Character::forward()
{
	position.x++;
	setPos(getPosition().x + 10, getPosition().y);
	return true;
}

bool Character::backward()
{
	position.x--;
	setPos(getPosition().x - 10, getPosition().y);
	return true;
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