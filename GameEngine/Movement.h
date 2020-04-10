/*
Auteur: Équipe p-02
Fichier: Movement.h
Date : 9 février 2020
Description : Déclaration de la classe Movement
*/

#pragma once

struct Coordonnees
{
	int x;
	int y;
};

class Movement
{
private:
	Coordonnees position;
	
public:
	Movement();
	virtual ~Movement();
	bool jump();
	Coordonnees getPosition();
	bool forward();
	bool backward();
	bool climb();
	bool hit();
};
