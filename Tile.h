#pragma once

#define WALKABLE 1
#define UNWALKABLE 2

#include <QGraphicsPixmapItem>

class Tile : public QGraphicsPixmapItem
{
public:
	Tile();
	~Tile();
	int getState();
	void setState(int newState);
private:
	int state;
};
