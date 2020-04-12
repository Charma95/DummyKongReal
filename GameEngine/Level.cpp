/*
Auteur: Équipe p-02
Fichier: Level.cpp
Date : 9 février 2020
Description : Implémentation des méthodes de la classe Level
*/

#include "Level.h"

Level::Level(int level)
{
	
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
			if (i > 8) map[MAX_HEIGHT - 5][i] = MAP;
			if (i < MAX_WIDTH - 8) map[MAX_HEIGHT - 10][i] = MAP;
			if (i > 8) map[MAX_HEIGHT - 15][i] = MAP;
		}

		//échelle 1
		for (int i = MAX_HEIGHT - 2; i >= MAX_HEIGHT - 4; i--) map[i][MAX_WIDTH - 8] = LADDER;

		//échelle 2
		for (int i = MAX_HEIGHT - 6; i >= MAX_HEIGHT - 9; i--) map[i][MAX_WIDTH - 20] = LADDER;

		//échelle 3
		for (int i = MAX_HEIGHT - 11; i >= MAX_HEIGHT - 14; i--) map[i][MAX_WIDTH - 10] = LADDER;

		// Pauline
		map[MAX_HEIGHT - 16][MAX_WIDTH - 4] = PAULINE;
		break;
	case 2:
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
			map[MAX_HEIGHT - 10][i] = MAP;
			map[MAX_HEIGHT - 15][i] = MAP;
		}

		//échelle 1
		for (int i = MAX_HEIGHT - 2; i >= MAX_HEIGHT - 9; i--) map[i][MAX_WIDTH - 8] = LADDER;

		//échelle 1
		for (int i = MAX_HEIGHT - 11; i >= MAX_HEIGHT - 14; i--) map[i][MAX_WIDTH - 24] = LADDER;

		// Pauline 
		map[MAX_HEIGHT - 16][MAX_WIDTH - 4] = PAULINE;
		break;
	case 3:
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
			if (i > 10) map[MAX_HEIGHT - 5][i] = MAP;
			if (i > 5) map[MAX_HEIGHT - 10][i] = MAP;
			map[MAX_HEIGHT - 15][i] = MAP;
		}

		//échelle 1
		for (int i = MAX_HEIGHT - 2; i >= MAX_HEIGHT - 4; i--) map[i][MAX_WIDTH - 8] = LADDER;

		//échelle 2
		for (int i = MAX_HEIGHT - 6; i >= MAX_HEIGHT - 9; i--) map[i][MAX_WIDTH - 10] = LADDER;

		//échelle 3
		for (int i = MAX_HEIGHT - 11; i >= MAX_HEIGHT - 14; i--) map[i][MAX_WIDTH - 12] = LADDER;

		// Pauline
		map[MAX_HEIGHT - 16][MAX_WIDTH - 4] = PAULINE;
		break;
	default:
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
			map[MAX_HEIGHT - 5][i] = MAP;
			map[MAX_HEIGHT - 10][i] = MAP;
			map[MAX_HEIGHT - 15][i] = MAP;
		}

		//échelle 1
		for (int i = MAX_HEIGHT - 2; i >= MAX_HEIGHT - 4; i--) map[i][MAX_WIDTH - 8] = LADDER;

		//échelle 2
		for (int i = MAX_HEIGHT - 6; i >= MAX_HEIGHT - 9; i--) map[i][MAX_WIDTH - 20] = LADDER;

		//échelle 3
		for (int i = MAX_HEIGHT - 11; i >= MAX_HEIGHT - 14; i--) map[i][MAX_WIDTH - 12] = LADDER;

		//Pauline 
		map[MAX_HEIGHT - 16][MAX_WIDTH - 4] = PAULINE;
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
