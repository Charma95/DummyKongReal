#include "Tile.h"

Tile::Tile()
{

}

Tile::~Tile()
{

}

int Tile::getState()
{
	return state;
}

void Tile::setState(int newState)
{
	state = newState;
}
