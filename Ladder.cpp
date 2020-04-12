#include "Ladder.h"

Ladder::Ladder() : QGraphicsPixmapItem()
{
	setPixmap(QPixmap("images/Ladder.jpg"));
	lad = 0;
}

Ladder::~Ladder()
{

}