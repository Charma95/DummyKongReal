#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <qlayout.h>
#include <qpixmap.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qfile.h>
#include <qstring.h>
#include <qmessagebox.h>
#include <qtextstream.h>
#include <qdatetime.h>
#include <qdebug.h>
#include <ostream>
#include <iostream>
#include "Help.h"
#include "Levels.h"
#include "GameEngine/Game.h"
#include <Options.h>
#include "GameWindow.h"
#include <QKeyEvent>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
	QWidget *centralWidget;
	QGridLayout *mainLayout;
	QPushButton *Continue;
	QPushButton *Play;
	QPushButton *Option;
	QPushButton *Help;
	QPushButton *Save;
	QPushButton *Exit;
	LevelsPage *levelsPage;
    std::unique_ptr<HelpPage> helpPage;  
	OptionsPage *optionsPage;
	GamePage *gamePage;
	QMenuBar *menuBar;
	QMenu *fileMenu;
	QMenu *levelsMenu;
	QMenu *viewMenu;
	QAction *optionsAction;
	QAction *saveAction;
	QAction *homeAction;
	QAction *quitAction;
	QAction *level1Action;
	QAction *level2Action;
	QAction *level3Action;
	QAction *fullScreenAction;
	QAction *normalScreenAction;
	QString m_level;
	int level;

	/* Private methods */
	void initWidget();
	void initButton();
	void initLayout();
	void initMenus();
	void initUI();
	void setupUI();
signals:
	void levelSelected(int level);
private slots:
	void showHelpPage();
	void showOptionsPage();
	void showLevelsPage();
	void showHomePage();
	void showGamePage(int level);
	void exitGame();
	void saveLevel(int level);
	void continueLastGame();

};
#endif // MAINWINDOW_H
