/*
Auteur: Équipe p-02
Fichier: Barrel.h
Date : 13 février 2020
Description : Déclaration de la classe Barrel
*/

#pragma once
#include "Tool.h"
#include "Character.h"

class Barrel:public Tool
{	
public:
	Barrel(Coordonnees positionInitiale);
	~Barrel();
	bool bounce();
	void roll(bool direction);
	//bool fall();
};
