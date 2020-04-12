/*
Auteur: Equipe p-02
Fichier: Ladder.cpp
Date : 9 fevrier 2020
Description : Implementation des methodes de la classe Ladder
*/

#include "Ladder.h"

Ladder::Ladder() : QGraphicsPixmapItem()
{
	setPixmap(QPixmap("images/Ladder.jpg"));
	lad = 0;
}

Ladder::~Ladder()
{

}