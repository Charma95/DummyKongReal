/*
Auteur: �quipe p-02
Fichier: Level.h
Date : 11 mars 2020
Description : D�claration de la classe Hammer
*/

#pragma once

#include "Tool.h"

class Hammer : public Tool {
public:
	Hammer(int x, int y);
	~Hammer();

	bool isAttached();
	void attach();
	bool breakBarrel();


private:
	bool attached;
};