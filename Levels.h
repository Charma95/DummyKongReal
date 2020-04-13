/*
@Auteur: Equipe p-02
@Fichier: Levels.h
@Date : 9 fevrier 2020
@Brief : Declaration de la classe Levels
*/
#pragma once

#include <qwidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qstring.h>


class LevelsPage : public QWidget
{
	Q_OBJECT
public:
	explicit LevelsPage(QWidget *parent = nullptr);
	~LevelsPage();
private:
	QVBoxLayout *mainLayout;
	QPushButton *level1;
	QPushButton *level2;
	QPushButton *level3;
	QPushButton *level4;

public slots:
	void level1Selected();
	void level2Selected();
	void level3Selected();
	void level4Selected();

signals:
	void levelSelected(int level);
};
