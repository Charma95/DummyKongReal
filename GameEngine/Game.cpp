/*
Auteur: Équipe p-02
Fichier: Game.cpp
Date : 9 février 2020
Description : Implémentation des méthodes de la classe Game
*/

#include "Game.h"

//	DEFINITION OF GAME MODE: (XBOX CONTROLLER OR KEYBOARD)
/*
#define MOVE_LEFT player.getPlayer().LThumbStickX
#define MOVE_RIGHT player.getPlayer().LThumbStickX
#define MOVE_UP player.getPlayer().LThumbStickY
#define MOVE_DOWN player.getPlayer().LThumbStickY
#define JUMP player.getPlayer().BTN_A
*/
#define MOVE_LEFT KeyboardPress('A')
#define MOVE_RIGHT KeyboardPress('D')
#define MOVE_UP KeyboardPress('W')
#define MOVE_DOWN KeyboardPress('S')
#define JUMP KeyboardPress(' ')


int KeyboardPress(char ch) {
	if (GetAsyncKeyState(ch)) {
		if (ch == 'A' || ch == 'S') {
			return -1;
		}
		else {
			return 1;
		}
	}
	return 0;
}


Game::Game(int lvl)
{
	cout << "constructeur de Game\n";
	mario = new Character(1, MAX_HEIGHT - 2, QPixmap("sprites/sprites/Mario/mario4.png"));
	player.getUserInput();
	isPaused = false;
	level = new Level(lvl);
}

Game::~Game()
{
	cout << "destructeur de Game\n";
	delete level;
}

bool Game::refresh()
{
	system("cls");
	player.readController();
	return true;
	}


bool Game::pause()
{
	isPaused = true;
	return true;
}

bool Game::start()
{
	isPaused = false;
	return true;
}

Character* Game::getMario()
{
	return mario;
}

void Game::setMario(int setup)
{
		
}

Character Game::getDummyKong()
{
	return dummyKong;
}

void Game::showLevel()
{


}

Level* Game::getLevel()
{
	return level;
}
