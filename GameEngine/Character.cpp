/*
Auteur: Equipe p-02
Fichier: Character.cpp
Date : 9 fevrier 2020
Description : Implementation des methodes de la classe Character
*/

#include "Character.h"


Character::Character(int positionX, int positionY, QPixmap pixmap) : QGraphicsPixmapItem()
{
	// initialiser les vecteurs servant à créer les animations
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
	setPos(positionX * PIX_WIDTH, (MAX_HEIGHT - 2) * PIX_HEIGHT - 26);
	lifePoints = 100;
	lifeCount = 5;

	currentVelocity.x = 0;
	currentVelocity.y = 0;
	climbing = false;
	std::cout << "Constructeur de character" << std::endl;
	PrintMemoryUsage();
}

Character::~Character()
{

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

/* Cette fonction permet de retirer des points de vie tout en gérant le le fait qu'elle peut être entre 0 et 100*/
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

/* Cette fonction permet de vérifier si le joueur est en contact avec un plancher dans la scène */
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

/* Cette fonction permet de vérifier si le joueur est en contact avec une échelle dans la scène */
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

/* Cette fonction permet de vérifier si le joueur est en contact avec Pauline dans la scène */
bool Character::isCollidingWithPauline()
{
	for (QGraphicsItem* i : collidingItems()) {
		Pauline * item = dynamic_cast<Pauline *>(i);
		if (item)
		{
			return true;
		}
	}
	return false;
}

/* Cette fonction permet au joueur d'aterrir sur un plancher et de se replacer au-dessus
pour éviter de passer au travers*/
void Character::land()
{
	currentVelocity.y = 0;
	int posY = y();
	if (isCollidingWithTile() && posY % (PIX_HEIGHT/2) != 0) replaceOnTopOfObject();
}

/* Cette fonction est appelée à chaque "frame", elle permet de mettre à jour la position du
joueur selon sa vitesse actuelle et plusieurs autres paramètres */
void Character::updatePosition()
{
	// cette partie pour afficher que la partie a été gagnée n'est pas encore tout à fait fonctionnelle
	// Le but est d'afficher un message indiquant que la partie est gagnée lorsque le joueur arrive à toucher à Pauline
	if (isCollidingWithPauline())
	{
		emit finishLevel();
	}

	// changer la position actuelle du joueur
	if (!isCollidingWithLadder()) climbing = false;
	float newXPos = 0, newYPos = 0;
	if (x() + DT * currentVelocity.x > 0 && x() + DT * currentVelocity.x < PIX_WIDTH * (MAX_WIDTH - 1)) newXPos = x() + DT * currentVelocity.x;
	else newXPos = x();
	newYPos = y() + DT * currentVelocity.y;
	setPos(newXPos, newYPos);

	// verifier si il y a une platefrome sous mario, si oui ne pas tomber
	// si la plateforme est au-dessus, le joueur a frappé un plafond
	if (isCollidingWithTile())
	{
		if (currentVelocity.y > 0) land();
		else if (!climbing) hitHead();
	}
	else if (!climbing)
	{
		// Appliquer la gravité seulement si le joueur ne grimpe pas
		currentVelocity.y = currentVelocity.y + DT * G;
	}

	// Mettre à jour l'animation du personnage
	updateAnimationState();

	// Animer le personnage selon son état actuel
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

/* Cette fonction permet au joueur d'avancer en changeant sa vitesse en x*/
bool Character::forward()
{
	if (!climbing) currentVelocity.x = RUNSPEED;
	return true;
}

/* Cette fonction permet au joueur de reculer en changeant sa vitesse en x*/
bool Character::backward()
{
	if (!climbing) currentVelocity.x = -1 * RUNSPEED;
	return true;
}

/* Cette fonction permet au joueur de grimper dans un échelle vers le haut.
Il faut d'abord s'assurer que le joueur est bien dans une échelle*/
void Character::climbUp()
{
	if (isCollidingWithLadder())
	{
		currentVelocity.y = -1 * CLIMBSPEED;
		climbing = true;
		if (isCollidingWithTile()) replaceOnTopOfObject();
	}
}

/* Cette fonction permet au joueur de grimper dans un échelle vers le bas.
Il faut d'abord s'assurer que le joueur est bien dans une échelle*/
void Character::climbDown()
{
	if (isCollidingWithLadder())
	{
		currentVelocity.y = CLIMBSPEED;
		climbing = true;
		if (isCollidingWithTile()) climbing = false;
	}
}

/* Cette fonction permet au joueur de s'arrêter au milieu d'une échelle */
void Character::stopClimbing()
{
	currentVelocity.y = 0;
}

/* Cette fonction permet au joueur de sauter en aplliquant un vitesse en y */
bool Character::jump()
{
	if (isCollidingWithTile()) currentVelocity.y -= JUMPFORCE;

	return true;
}

/* Cette fonction permet de replacer le joueur au-dessus d'un plancher et d'éviter qu'il ne passe à-travers */
void Character::replaceOnTopOfObject()
{
	while (isCollidingWithTile()) setPos(x(), y() - 1);
	setPos(x(), y() + 1);
}

/* Frapper un plafond */
void Character::hitHead()
{
	currentVelocity.y = -1 * currentVelocity.y;
}

/* Arrêter de bouger en x */
void Character::stop()
{
	changeAnimationState(NOTHING);
	currentVelocity.x = 0;
}

/* Cette fonction permet de changer l'état d'animation tout en s'assurant que l'index est remis à zéro si c'est un nouvel état */
void Character::changeAnimationState(int newState)
{
	if (animationState != newState)
		animationIndex = 0;
	animationState = newState;
}

/* Itérer à tracers les différents éléments du vecteur pour animer le personnage */
void Character::animate(vector<QPixmap> vec)
{
	if (vec.size() <= animationIndex + 1) animationIndex = 0;
	else animationIndex++;

	setPixmap(vec[animationIndex]);
}

/* Vérifier dans quel état le personnage se trouve (s'il grimpe, court, saute ou est sur place) */
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




