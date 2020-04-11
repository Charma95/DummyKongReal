#pragma once

//#include "MainWindow.h"
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
	//void showGameWindow(int level);
	void level1Selected();
	void level2Selected();
	void level3Selected();
	void level4Selected();

signals:
	void levelSelected(int level);
};
