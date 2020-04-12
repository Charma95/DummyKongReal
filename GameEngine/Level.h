/*
Auteur: Équipe p-02
Fichier: Level.h
Date : 9 février 2020
Description : Déclaration de la classe Level
*/

#pragma once

#include <iostream>


using namespace std;

#define MAX_WIDTH 35
#define MAX_HEIGHT 20
#define AIR 0
#define MAP 1
#define LADDER 2
#define PAULINE 3
#define HAMMER 4

class Level
{
private:
	unsigned char difficulty;
	int map[MAX_HEIGHT][MAX_WIDTH] = { 0 };
	int index;
	bool complete;


public:
	Level(int level = 1);
	virtual ~Level();

	unsigned char getDifficulty();
	int getMap(int i, int j);

	void setDifficulty(unsigned char newDifficulty);

	void update();
	bool isComplete();
	void completeLevel();
	bool checkAroundPlayer(int x, int y, int check);
};
