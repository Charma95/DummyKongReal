/*
@Auteur: Equipe p-02
@Fichier: Help.h
@Date : 9 fevrier 2020
@Brief : Declaration de la classe Help
*/
#pragma once

#include <QMainWindow>
#include <qlayout.h>
#include <qpixmap.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qcolor.h>


class HelpPage : public QMainWindow
{
	Q_OBJECT
public:
	explicit HelpPage(QWidget *parent = nullptr);
    ~HelpPage();
private slots:
	void closeHelpPage();
private:
	/*Variables ----------------------------------------------------------*/
#pragma region variables
	QLabel *Message;
	QWidget *helpWidget;
	QGridLayout *helpLayout;
	QColor *color;
	QPushButton *Ok;
#pragma endregion variables
	/*Methods ------------------------------------------------------------*/
#pragma region methods
	void setupUI();
	void createWidget();
	void initializeWidget();

#pragma endregion methods

};