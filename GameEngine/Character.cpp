/*
Auteur: �quipe p-02
Fichier: Character.cpp
Date : 9 f�vrier 2020
Description : Impl�mentation des m�thodes de la classe Character
*/

#include "Character.h"


Character::Character(int positionX, int positionY, QPixmap pixmap) : QGraphicsPixmapItem()
{
	nothingVector.push_back(QPixmap("sprites/sprites/Mario/mario4.png"));

	runningLeftVector.push_back(QPixmap("sprites/sprites/Mario/mario1-temp.png"));
	runningLeftVector.push_back(QPixmap("sprites/sprites/Mario/mario2.png"));

	runningRightVector.push_back(QPixmap("sprites/sprites/Mario/mario6.png"));
	runningRightVector.push_back(QPixmap("sprites/sprites/Mario/mario5.png"));

	jumpingLeftVector.push_back(QPixmap("sprites/sprites/Mario/mario1-temp.png"));

	jumpingRightVector.push_back(QPixmap("sprites/sprites/Mario/mario6.png"));

	climbingVector.push_back(QPixmap("sprites/sprites/Mario/climb/climb3.png"));
	climbingVector.push_back(QPixmap("sprites/sprites/Mario/climb/climb5.png"));

	nothingClimbingVector.push_back(QPixmap("sprites/sprites/Mario/climb/climb3.png"));

	animationIndex = 0;
	animationState = NOTHING;

	setPixmap(pixmap);
	position.x = positionX;
	position.y = positionY;
	setPos(positionX * PIX_WIDTH, (MAX_HEIGHT - 2) * PIX_HEIGHT - 26);
	jumping = false;
	falling = false;
	jumpingState = 0;
	lifePoints = 100;
	lifeCount = 5;
	hammer = nullptr;
	currentVelocity.x = 0;
	currentVelocity.y = 0;
	climbing = false;
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

bool Character::isCollidingWithTile()
{
	for (QGraphicsItem* i : collidingItems()) {
		Tile * item = dynamic_cast<Tile *>(i);
		if (item)
		{
			return true;
		}
	}
	return false;
}

bool Character::isCollidingWithLadder()
{
	for (QGraphicsItem* i : collidingItems()) {
		Ladder * item = dynamic_cast<Ladder *>(i);
		if (item)
		{
			return true;
		}
	}
	return false;
}

void Character::land()
{
	currentVelocity.y = 0;
	int posY = y();
	if (isCollidingWithTile() && posY % (PIX_HEIGHT/2) != 0) replaceOnTopOfObject();
}

void Character::updatePosition()
{
	if (!isCollidingWithLadder()) climbing = false;
	float newXPos = 0, newYPos = 0;
	if (x() + DT * currentVelocity.x > 0 && x() + DT * currentVelocity.x < PIX_WIDTH * (MAX_WIDTH - 1)) newXPos = x() + DT * currentVelocity.x;
	else newXPos = x();
	newYPos = y() + DT * currentVelocity.y;
	setPos(newXPos, newYPos);

	// verifier si il y a une platefrome sous mario, si oui ne pas tomber
	if (isCollidingWithTile())
	{
		if (currentVelocity.y > 0) land();
		else if (!climbing) hitHead();
	}
	else if (!climbing)
	{
		currentVelocity.y = currentVelocity.y + DT * G;
	}

	// updater l'animation du personnage

	updateAnimationState();

	switch (animationState)
	{
	case NOTHING:
		animate(nothingVector);
		break;
	case RUNNING_L:
		animate(runningLeftVector);
		break;
	case RUNNING_R:
		animate(runningRightVector);
		break;
	case JUMPING_L:
		animate(jumpingLeftVector);
		break;
	case JUMPING_R:
		animate(jumpingRightVector);
		break;
	case CLIMBING:
		animate(climbingVector);
		break;
	case NOTHING_CLIMBING:
		animate(nothingClimbingVector);
	default:
		break;

	}
}

bool Character::forward()
{
	if (!climbing) currentVelocity.x = RUNSPEED;
	return true;
}

bool Character::backward()
{
	if (!climbing) currentVelocity.x = -1 * RUNSPEED;
	return true;
}

void Character::climbUp()
{
	if (isCollidingWithLadder())
	{
		currentVelocity.y = -1 * CLIMBSPEED;
		climbing = true;
		if (isCollidingWithTile()) replaceOnTopOfObject();
	}
}

void Character::climbDown()
{
	if (isCollidingWithLadder())
	{
		currentVelocity.y = CLIMBSPEED;
		climbing = true;
		if (isCollidingWithTile()) climbing = false;
	}
}

void Character::stopClimbing()
{
	currentVelocity.y = 0;
}

bool Character::jump()
{
	if (isCollidingWithTile()) currentVelocity.y -= JUMPFORCE;

	return true;
}

void Character::replaceOnTopOfObject()
{
	/*int posY = y();
	int dy = posY % PIX_HEIGHT;

	setPos(x(), posY - dy);*/
	while (isCollidingWithTile()) setPos(x(), y() - 1);
	setPos(x(), y() + 1);
}

void Character::hitHead()
{
	currentVelocity.y = -1 * currentVelocity.y;
}

void Character::stop()
{
	changeAnimationState(NOTHING);
	currentVelocity.x = 0;
}

void Character::changeAnimationState(int newState)
{
	if (animationState != newState)
		animationIndex = 0;
	animationState = newState;
}

void Character::animate(vector<QPixmap> vec)
{
	if (vec.size() <= animationIndex + 1) animationIndex = 0;
	else animationIndex++;

	setPixmap(vec[animationIndex]);
}

void Character::updateAnimationState()
{
	if (climbing && currentVelocity.y != 0)
	{
		changeAnimationState(CLIMBING);
	}
	else if (climbing)
	{
		changeAnimationState(NOTHING_CLIMBING);
	}
	else if (currentVelocity.y != 0)
	{
		if (currentVelocity.x >= 0) changeAnimationState(JUMPING_R);
		else changeAnimationState(JUMPING_L);
	}
	else
	{
		if (currentVelocity.x > 0) changeAnimationState(RUNNING_R);
		else if (currentVelocity.x < 0) changeAnimationState(RUNNING_L);
		else changeAnimationState(NOTHING);
	}
}




