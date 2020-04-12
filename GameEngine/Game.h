/*
Auteur: �quipe p-02
Fichier: Game.h
Date : 9 f�vrier 2020
Description : D�claration de la classe Game
*/

#pragma once
#include "Level.h"
#include "Character.h"
#include "XController.h"

#define RIGHT  1
#define LEFT 2

class Game
{
private:
	Level *level;
	Character *mario;
	Character dummyKong;
	bool isPaused;
	bool done = false;
	XController player;

public:
	Game(int level = 1);
	virtual ~Game();
	bool start();
	bool refresh();
	bool pause();
	Character* getMario();
	void setMario(int setup);
	Character getDummyKong();
	void showLevel();
	Level* getLevel();
};
