/*
Auteur: Equipe p-02
Fichier: Game.h
Date : 9 fevrier 2020
Description : Declaration de la classe Game
*/

#pragma once
#include "Level.h"
#include "Character.h"

#define RIGHT  1
#define LEFT 2

class Game
{
private:
	Level *level;
	Character *mario;
	bool isPaused;
	bool done = false;

public:
	Game(int level = 1);
	virtual ~Game();
	bool start();
	bool pause();
	Character* getMario();
	Level* getLevel();
};
