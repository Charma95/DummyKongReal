/*
Auteur: Équipe p-02
Fichier: Tool.h
Date : 9 février 2020
Description : Déclaration de la classe Tool
*/

#pragma once

struct Coordonnees
{
	int x;
	int y;
};

class Tool
{
protected:
	Coordonnees position;
public:
	Tool();
	virtual ~Tool();
	Coordonnees getPosition();
	void setPosition(int x, int y);
	bool updatePosition();
};
