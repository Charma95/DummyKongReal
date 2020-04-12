/*
Auteur: Equipe p-02
Fichier: main.cpp
Date : 9 fevrier 2020
Description : Implementation du fichier main
*/
#include "MainWindow.h"
#include "GameEngine/Game.h"
#include "GameEngine/XController.h"
#include "GameEngine/timer.h"
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	w.setWindowIcon(QIcon("Images/Icon.png"));
	w.showMaximized();

    return a.exec();
}
