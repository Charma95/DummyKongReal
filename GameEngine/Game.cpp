/*
Auteur: �quipe p-02
Fichier: Game.cpp
Date : 9 f�vrier 2020
Description : Impl�mentation des m�thodes de la classe Game
*/

#include "Game.h"


Game::Game(int lvl)
{
	cout << "constructeur de Game\n";
	mario = new Character(1, MAX_HEIGHT - 2, QPixmap("sprites/sprites/Mario/mario4.png"));
	isPaused = false;
	level = new Level(lvl);
}

Game::~Game()
{
	delete level;
}

/* Mettre le jeu en pause */
bool Game::pause()
{
	isPaused = true;
	return true;
}

/* Mettre le jeu en marche */
bool Game::start()
{
	isPaused = false;
	return true;
}

Character* Game::getMario()
{
	return mario;
}

Level* Game::getLevel()
{
	return level;
}
