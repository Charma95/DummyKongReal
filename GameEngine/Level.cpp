/*
Auteur: Équipe p-02
Fichier: Level.cpp
Date : 9 février 2020
Description : Implémentation des méthodes de la classe Level
*/

#include "Level.h"

Level::Level(int level)
{
	hammer = new Hammer(10, MAX_HEIGHT - 2);
	index = level;
	complete = false;

	switch (index)
	{
	case 1:
		//fond de la map
		for (int i = 0; i < MAX_HEIGHT; i++)
		{
			for (int j = 0; j < MAX_WIDTH; j++)
			{
				map[i][j] = AIR;
			}
		}

		//planchers
		for (int i = 0; i < MAX_WIDTH; i++)
		{
			map[MAX_HEIGHT - 1][i] = MAP;
			map[MAX_HEIGHT - 4][i] = MAP;
			map[MAX_HEIGHT - 8][i] = MAP;
			map[MAX_HEIGHT - 12][i] = MAP;
		}

		//échelle
		for (int i = MAX_HEIGHT - 2; i >= MAX_HEIGHT - 4; i--)
		{
			map[i][MAX_WIDTH - 4] = LADDER;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}

Level::~Level()
{
	cout << "destructeur de Level\n";
	//delete hammer;
}

unsigned char Level::getDifficulty()
{
	return difficulty;
}

void Level::setDifficulty(unsigned char newDifficulty)
{
	difficulty = newDifficulty;
}

Hammer Level::getHammer() {
	return *hammer;
}

Hammer* Level::getHammerPtr() {
	return hammer;
}

void Level::update()
{
	system("cls");

	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_WIDTH; j++)
		{
			switch (map[i][j])
			{
			case AIR:
				cout << " ";
				break;
			case MAP:
				cout << "#";
				break;
			case LADDER:
				cout << "1";
				break;
			default:
				break;
			}
		}
		cout << endl;
	}
}

int Level::getMap(int i, int j)
{
	return map[i][j];
}

bool Level::isComplete()
{
	return complete;
}

void Level::completeLevel()
{
	complete = true;
}

bool Level::checkAroundPlayer(int x, int y, int check)
{
	if (map[y + 1][x] == check) return true;
	if (map[y - 1][x] == check) return true;
	if (map[y][x + 1] == check) return true;
	if (map[y][x - 1] == check) return true;
	return false;
}
