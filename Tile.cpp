/*
Auteur: Equipe p-02
Fichier: Tile.cpp
Date : 9 fevrier 2020
Description : Implementation des methodes de la classe Tile
*/
#include "Tile.h"

Tile::Tile() : QGraphicsPixmapItem()
{
	setPixmap(QPixmap("Images/Floor.jpg"));

}

Tile::~Tile()
{

}


