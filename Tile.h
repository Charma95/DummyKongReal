/*
@Auteur: Equipe p-02
@Fichier: Tile.h
@Date : 9 fevrier 2020
@Brief : Declaration de la classe Tile
*/
#pragma once

#define WALKABLE 1
#define UNWALKABLE 2

#include <QGraphicsPixmapItem>

class Tile : public QGraphicsPixmapItem
{
public:
	Tile();
	~Tile();
private:
};
