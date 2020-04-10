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
	void showGameWindow();

signals:
	void levelSelected();
};
