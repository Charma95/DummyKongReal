#include "Barrel.h"
#define DROITE 1
#define GAUCHE -1
/*
Auteur: Équipe p-02
Fichier: Barrel.cpp
Date : 13 février 2020
Description : Implémentation des méthodes de la classe Barrel
*/


Barrel::Barrel(Coordonnees positionInitiale)
{
	position.x = positionInitiale.x;
	position.y = positionInitiale.y;
}

Barrel::~Barrel(){}

bool Barrel::bounce()
{
	position.y++;
	position.y++;
	position.y--;
	position.y--;
	position.y++;
	position.y--;

	return true;
}

void Barrel::roll(bool direction)
{
	if (direction == true)
	{
		position.x++;
	}

	else if (direction == false)
	{
		position.x--;
	}
}
/*
bool Barrel::fall()
{
	utilisation de la pseudo-gravité
	return true;
}
*/
