/*
Auteur: Équipe p-02
Fichier: Tool.cpp
Date : 9 février 2020
Description : Implémentation des méthodes de la classe Tool
*/

#include "Tool.h"

Tool::Tool()
{

}

Tool::~Tool()
{

}

Coordonnees Tool::getPosition()
{
	return position;
}

void Tool::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

bool Tool::updatePosition()
{
	return true;
}
